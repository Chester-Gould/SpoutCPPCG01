#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)

#include "cImage.h"


cImage::cImage(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w * h * channels;
	data = new uint8_t[size];
}

cImage::cImage(const cImage& img) : cImage(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}


cImageType cImage::get_file_type(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if (strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if (strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if (strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}


cImage& cImage::crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch) {
	channels = 4;
	size = cw * ch * channels;
	uint8_t* croppedcImage = new uint8_t[size];
	memset(croppedcImage, 0, size);

	for (uint16_t y = 0; y < ch; ++y) {
		if (y + cy >= h) { break; }
		for (uint16_t x = 0; x < cw; ++x) {
			if (x + cx >= w) { break; }
			memcpy(&croppedcImage[(x + y * cw) * channels], &data[(x + cx + (y + cy) * w) * channels], channels);
		}
	}

	w = cw;
	h = ch;


	delete[] data;
	data = croppedcImage;
	croppedcImage = nullptr;

	return *this;
}
