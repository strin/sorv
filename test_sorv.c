#include "stdio.h"
#include "sorv.h"
#include "math.h"
#include "objcokus.h"

auto uniform_func = [](int s1, int s2) -> double {
	const int n = 10;
	double res = 0;
	if(fmin(s2, n-1) < fmax(s1, 0)) return 0;
	return (fmin(s2, n-1)-fmax(s1, 0)+1)*1.0/n;
};

int sample_rv(Oracle oracle, int C, objcokus& cokus) {
	double u = cokus.random01();
	int i;
	for(i = 0; i <= C; i++) {
		if((*oracle)(0,i) >= u) break;
	}
	return i;
}

int main() {
	/* sorv */
	Oracle uniform = new std::function<double(int, int)>();
	*uniform = uniform_func;
	int n = 5, C = 7;
	double epsilon = 0.1;
	Oracle oracles[n];
	for(int i = 0; i < n; i++) oracles[i] = uniform;
	printf("res = %lf\n", sorv(n, oracles, C, epsilon));
	/* random sampling */
	objcokus cokus;
	cokus.seedMT(time(0));
	int num_iter = 1000000, pos_iter = 0;
	int samples[n];
	for(int it = 0; it < num_iter; it++) {
		int sum = 0;
		for(int i = 0; i < n; i++) {
			sum += sample_rv(oracles[i], C, cokus);
		}
		if(sum <= C) pos_iter++;
	}
	double res_sampling = (double)pos_iter/num_iter;
	printf("res(sampling) = %lf\n", res_sampling);
}