#include "emscripten.h"
#include "src/webp/decode.h"

EMSCRIPTEN_KEEPALIVE
int version() {
	return WebPGetDecoderVersion();
}

int result[2];
uint32_t decode_info[2];
EMSCRIPTEN_KEEPALIVE
uint32_t* decode(uint8_t* img_in, size_t size) {
	int width = 0;
	int height = 0;
	
	result[0] = (int)WebPDecodeRGBA(img_in, size, &width, &height);
	result[1] = width * height * 4;
	
	decode_info[0] = width;
	decode_info[1] = height;
	
	return decode_info;
}

EMSCRIPTEN_KEEPALIVE
void free_result(uint8_t* result) {
	WebPFree(result);
}

EMSCRIPTEN_KEEPALIVE
int get_result_pointer() {
	return result[0];
}

EMSCRIPTEN_KEEPALIVE
int get_result_size() {
	return result[1];
}

//emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS='["_malloc", "_free"]' -I libwebp webp.c libwebp/src/{dec,dsp,demux,enc,mux,utils}/*.c -o webp.js