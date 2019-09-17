#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
	printf("Hello Axinom!\n");
	
	return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
int factorial(int n) {
	if (n == 0)
		return 1;
	else
		return n * factorial(n-1);
}

//emcc hello.c -o hello.html
//emcc hello.c -g -o hello.html
//emcc hello.c -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -O3 -o hello.js