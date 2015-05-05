set common=analyze.c analyze.h components.c components.h file.c file.h gen.c gen.h gen2x2.c gencode.h lifelist.c lifelist.h rmo.c rmo.h
gcc -O3 -o ptb2 ptb2.c ptbsearch2.c %common%
gcc -O3 -o survive survive.c %common%

pause