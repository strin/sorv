#include "sorv.h"
#include "stdio.h"
#include "math.h"

double sorv(int n, Oracle oracles[], int C, double epsilon) {
	if(n == 0) return -1;
	double Q = 1+epsilon/n;
	/* compute \Delta */
	double delta = 1;
	for(int i = 0; i < n; i++) 
		delta *= (*oracles[i])(0,0);
	int s = ceil(log(1/delta)/log(Q));
	double *T[n];
	for(int i = 0; i < n; i++) T[i] = new double[s+2];
	/* compute base case T(1, j) */
	for(int j = 0; j <= s; j++) {
		int left = 0, right = C, mid;
		double target = pow(Q, -j);
		while((mid = (left+right)/2) != right) {
			if((*oracles[0])(0, mid) < target) {
				left = mid+1;
			}else{
				right = mid;
			}
		}
		if((*oracles[0])(0,left) < target) {
			T[0][j] = inf;
		}else
			T[0][j] = left;
		// printf("T[0][%d] = %lf\n", j, T[0][j]);	
	}
	/* dynamic programming to compute T(i,j) */
	for(int i = 1; i < n; i++) {
		T[i-1][s+1] = 0;
		for(int j = 0; j <= s; j++) {
			int left = 0, right = C, mid;
			double z = 0;
			while(true) {
				mid = (left+right)/2;
				z = 0;
				if(!isinf(T[i-1][0])) {
					z += (*oracles[i])(0, mid-T[i-1][0]);
				}
				for(int m = 1; m <= s+1; m++) {
					if(isinf(T[i-1][m-1]) && !isinf(T[i-1][m])) {
						z += (*oracles[i])(0, mid-T[i-1][m])*pow(Q,j-m);
					}else if(!isinf(T[i-1][m-1]) && !isinf(T[i-1][m])) {
						z += (*oracles[i])(mid-T[i-1][m-1]+1, mid-T[i-1][m])*pow(Q,j-m);
					}
				}
				if(left == right) {
					if(z < 1) T[i][j] = inf;
					else T[i][j] = mid;
					break;
				}
				if(z >= 1) {
					right = mid;
				}else{
					left = mid+1;
				}
			}
			// printf("T[%d][%d] = %lf z = %lf\n", i, j, T[i][j], z);
		}
	}
	/* compute answer */
	int j;
	for(j = s; j >= 0; j--) {
		if(T[n-1][j] > C) break;
	}
	double res = pow(Q, -j);
	/* clean */
	for(int i = 0; i < n; i++) delete[] T[i];
	return res;
}

