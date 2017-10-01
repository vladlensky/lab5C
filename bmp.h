#include <stdint.h>
typedef struct pixel_t { char b,g,r; } pixel_t;

typedef struct image_t {
    uint32_t width, height;
    pixel_t* data;
} image_t;

typedef struct bmp_header_t{
    uint16_t bfType;
    uint32_t bfileSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header_t;