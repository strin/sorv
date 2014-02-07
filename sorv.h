#ifndef SORV_FPTAS
#define SORV_FPTAS

#include <functional>
#include "float.h"

// #define floor(x) (int)(x)
// #define ceil(x) ((double)((int)(x)+((x)-(int)(x) > 0)))
#define inf 1.0/0.0

/* Oracle machine, 
 * given two integer s1, s2 on support
 * returns the probabiilty Pr[s1 <= X <= s2]. */
// typedef double (*Oracle)(int, int);
typedef std::function<double(int,int)>* Oracle;

/* the support of oracles should start from 0 */
double sorv(int n, Oracle oracles[], int C, double epsilon);

#endif