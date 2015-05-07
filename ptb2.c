#include <stdio.h>
#include <limits.h>
#include "gen.h"
#include <malloc.h>
#include <assert.h>

char out[90000];
char inp[90000];
Cell aligns[10000];
int naligns=0;

LifeList ptb[10000];
LifeList nb1, nb2, exp, orig;
LifeList tmp;


extern Cell *convolution, *scratch1, *scratch2, *oldAlignments;
void makeWorkSpace(int n);


main(int argc, char *argv[]) {
	int i, nconv, nol;
	int gens, thisgen, nptb;
	int iptb;
	int depth=1;
	int maxgenall=50;
	int mingen=0;
	int maxvanish=0;
	int maxgen1;

	if (argc<3) return 0;

	readCellsColor(&orig, argv[1], 1);
	nptb=readPatList(ptb, argv[2]);
	if (argc>3) sscanf(argv[3], "%d", &maxgenall);
	if (argc>4) sscanf(argv[4], "%d", &depth);
	if (argc>5) sscanf(argv[5], "%d", &mingen);
	if (argc>6) sscanf(argv[6], "%d", &maxvanish);
	if (argc>7) sscanf(argv[7], "%d", &maxgen1); else maxgen1=maxgenall;

	perturbEnum(&orig, ptb, nptb,
	            0, depth, mingen, maxgen1, maxgenall, maxvanish);


}

