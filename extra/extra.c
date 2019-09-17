#include <stdio.h>
#include "emscripten.h"

EM_JS(void, c_to_js, (const char* str), {
	let data = UTF8ToString(str);
	
	alert(data + '-hai');
	alert(data + '-bai');
	
	navigator.geolocation.getCurrentPosition(function(position) {
		console.log(position.coords.latitude);
		console.log(position.coords.longitude);
	});
});

int data[] = { 50, 60 };

EMSCRIPTEN_KEEPALIVE
int* version() {
	return data;
}

EMSCRIPTEN_KEEPALIVE
int main() {
	//c_to_js("Ruwan");
	
	return 0;
}