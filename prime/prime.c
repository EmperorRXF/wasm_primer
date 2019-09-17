//emcc -O3 -s WASM=1 prime.c -o prime.js

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#define CWD "/working/"
#else
	#define CWD ""
#endif

int isPrime(int n) {
	if (n <= 1)
		return 0;

	int sqrt_n = sqrt(n);
	
    for (int i = 2; i <= sqrt_n; i++)
		if (n % i == 0)
			return 0;

    return 1;
}

int main(int argc, char** argv) {
	#ifdef __EMSCRIPTEN__
	  EM_ASM(
		FS.mkdir('/working');
		FS.mount(NODEFS, { root: '.' }, '/working');
	  );
	#endif
	
	if (argc < 3)
		printf("usage: %s nthPrimeNumber groupBy\n", argv[0]);
	
	int primeCount = 2;
	int maxPrimeCount = atoi(argv[1]);
	int groupBy = atoi(argv[2]);
	int currentPrimeCheck = 3;
	int isPrimeNumber;
	struct timespec start, end;
	double time_spent;
	
	FILE *f = fopen(CWD "output.csv", "w");
	fprintf(f, "%d,%d,%f\n", 1, 2, 0.0f);
	
	while (primeCount <= maxPrimeCount) {
		clock_gettime(CLOCK_REALTIME, &start);
		isPrimeNumber = isPrime(currentPrimeCheck);
		clock_gettime(CLOCK_REALTIME, &end);
		
		if (isPrimeNumber) {
			time_spent += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (1000.0 * 1000.0 * 1000.0);
			
			if (primeCount % groupBy == 0)
				fprintf(f, "%d,%d,%f\n", primeCount, currentPrimeCheck, time_spent);
			
			primeCount++;
		}
		
		currentPrimeCheck += 2;
	}
	
	fclose(f);
	return 0;
}