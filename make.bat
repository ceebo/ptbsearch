set common=analyze.c components.c file.c gen.c gen2x2.c lifelist.c rmo.c
gcc -O3 -o ptb2 ptb2.c ptbsearch2.c %common%
gcc -O3 -o survive survive.c %common%

pause