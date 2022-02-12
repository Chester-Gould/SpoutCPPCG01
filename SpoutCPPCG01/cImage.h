#include <stdint.h>
#include <cstdio>
#include <complex>

//legacy feature of C
#undef __STRICT_ANSI__
#define _USE_MATH_DEFINES 
#include <cmath>
#ifndef M_PI
	#define M_PI (3.14159265358979323846)
#endif

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum cImageType {
	PNG, JPG, BMP, TGA
};

struct cImage {
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	cImage(int w, int h, int channels = 3);
	cImage(const cImage& img);


	cImageType get_file_type(const char* filename);

	cImage& crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch);

};

