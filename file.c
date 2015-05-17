/* All code copyright Paul Callahan 1996  (callahan@inf.ethz.ch) */

#include <stdio.h>
#include <limits.h>
#include "gen.h"
#include <string.h>

extern int spreadColor[];

static char s[8192];

void readCellsColorRLE(LifeList *cells, char *patname, int color) {

    FILE *patfile;
    int i, k, x = 0, y = 0, reps = 0, n = 0;
 
    if (!(patfile=fopen(patname, "r"))) {
        cells->ncells= 0;
        return;
    }
    
    n=cells->ncells;
    
    while (fgets(s, 8191, patfile)) {
        int patlen = strspn(s, "0123456789bo.ABCDE$");
        for (i=0; i < patlen; i++) {  
            if ('0' <= s[i] && s[i] <= '9') {
                reps = 10 * reps + (int)(s[i] - '0');
            } else {
                
                if (reps == 0) reps = 1;
                
                if (s[i] == '$') {
                    x = 0;
                    y += reps;
                } else {
                    
                    int value = 0;
                    if (s[i] == 'o' || s[i] == 'A')
                        value = color;
                    else if (s[i] == 'C')
                        value = (int) 'a';
                    else if (s[i] == 'E')
                        value = (int) 'b';
                    
                    if (value == 0) {
                        x += reps;
                    } else {
                        while (reps-- > 0) {
                            resizeIfNeeded(cells, n+1);
                            cells->cellList[n].position = pack(x++, y);
                            cells->cellList[n++].value = value;
                        }
                    }
                }
                
                reps = 0;
            }
        }
    }
    
    cells->ncells=n;
    resizeIfNeeded(cells, n+1);
    
    fclose(patfile);
    
}

void readCellsColor(LifeList *cells, char *patname, int color) {
int n,pos,x,y,col;
FILE *patfile;
int curx, cury, lastx;
int spacex, spacey; 
 
   char *last_dot = strrchr(patname, '.');
   if (last_dot && !strcmp(last_dot, ".rle")) {
       readCellsColorRLE(cells, patname, color);
       return;
   }
       

   curx=0;
   cury=0;
 
   spacex=0;
   spacey=0;

  if (!(patfile=fopen(patname, "r"))) {
      cells->ncells= 0;
      return;
  }

  n=cells->ncells;

  while (fgets(s, 8191, patfile)) {
    int patlen;

    patlen=strspn(s, ".*abcdefghijklmnopqrstuvwyxz!");
    if (patlen>1 && s[patlen-1]=='!') {
       curx=spacex; cury=spacey;
       lastx=0;
       for (x=0; x<patlen; x++) {  
          if (s[x]=='*' || (s[x]>='a' && s[x]<='z')) {
              pos=pack(curx+x-lastx, cury);
              resizeIfNeeded(cells, n+1);
              cells->cellList[n].position=pos;
              cells->cellList[n++].value= 
                   (s[x]=='*') ? color : (int)s[x];
          } else if (s[x]=='!') {
              lastx=x+1; 
               cury++;
          }
       } 
       spacex+=SPACE;
       if (spacex>=MAXCOL) {
           spacex=0;
           spacey+=SPACE;
       }
    } else if (s[0]=='#') { 
        if (sscanf(s+2, "%d%d", &x, &y)==2) {
           curx=x;
           cury=y;
        }
    } else if (strspn(s,".*abcdefghijklmnopqrstuvwxyz")>0) {
       for (x=0; s[x]!='\0'; x++) {  
          if (s[x]=='*' || (s[x]>='a' && s[x]<='z')) {
              pos=pack(curx+x, cury);
              resizeIfNeeded(cells, n+1);

              cells->cellList[n].position=pos;
              cells->cellList[n++].value= 
                   (s[x]=='*') ? color : (int)s[x];
          }
       }
       cury++;
    } else {
       col= -1;

       if (sscanf(s, "%d%d%d",&x, &y, &col)>=2) {;
          pos=pack(x,y);
   
          resizeIfNeeded(cells, n+1);
   
          cells->cellList[n].position=pos;
          if (col == -1) 
             cells->cellList[n++].value= color;
          else cells->cellList[n++].value= spreadColor[col];
       }
    }

  }

  cells->ncells=n;
  resizeIfNeeded(cells, n+1);

  makeRowMajor(cells);

  fclose(patfile);
  
}

void outPatLine(char *patname, int k) {
int i;
static char s[1000];
FILE *patfile;

  if (!(patfile=fopen(patname, "r"))) {
      return;
  }

  i=1;

  while(fgets(s, 999, patfile)) {
      if (i==k) {
         printf("%s", s);
         break;
      }
      i++;
  }

  fclose(patfile);
}

int iswhitespace(char *s) {
    while(*s)
        if (!isspace(*s++))
            return 0;
    return 1;
}

int readPatList(LifeList *pat, char *patname) {
int i=0;
FILE *patfile;
char header[256];
int patcount=0;
 
  header[0] = '\0';

  if ( (patfile=fopen(patname, "r")) != NULL) {
  
    while (fgets(s, 8191, patfile)) {

        if (iswhitespace(s))
            continue;

        if (s[0] == '#') {
            if (s[1] == '#') {
                if (patcount && header[0]) {
                    fprintf(stderr, "%s x %d\n", header, patcount);
                    patcount = 0;
                }
                strcpy(header, s);
                header[strcspn(header, "\r\n")] = '\0';
            }
        } else {
            initLifeList(pat+i); 
            getpat(s, pat+i);
            i++;
            patcount++;
        }
    }
    
    if (patcount && header[0])
        fprintf(stderr, "%s x %d\n", header, patcount);

    fprintf(stderr, "Total catalysts %d\n", i);

    fclose(patfile);   
  }

  return i;
}
