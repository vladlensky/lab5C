#include <stdlib.h>
#include "bmp.h"
typedef enum {
    READ_OK = 0,
    READ_INVALID_SIGNATURE = 1,
    READ_INVALID_BITS = 2,
    READ_INVALID_HEADER = 3,
    READ_INVALID_OFFSET = 4,
    READ_CORRUPTED = 5
} read_error_code_t;

typedef enum {
    WRITE_OK = 0,
    WRITE_ERROR = 1
} write_error_code_t;

read_error_code_t read_header(FILE* const file, bmp_header_t* const header) {
    if (fread(header, 1, sizeof(bmp_header_t), file) != sizeof(bmp_header_t))
        return READ_INVALID_HEADER;
    if (header->bfType != 0x4D42)
        return READ_INVALID_SIGNATURE;
    if (header->bOffBits < 54)
        return READ_INVALID_OFFSET;
    return READ_OK;
}


read_error_code_t read_pixels(FILE* const file, const uint32_t offset,
                                           pixel_t* const data,
                                           const uint32_t width,
                                           const uint32_t height) {
    size_t row;
    size_t trash_size = width*3 % 4 == 0 ? 0 : 4 - (width*3 % 4);
    fseek(file, offset, SEEK_SET);
    for (row = 0; row < height; row++) {

        if (fread(data + row*width, 3, width, file) != width) {
            return READ_CORRUPTED;
        }
        fseek(file, trash_size, SEEK_CUR);
    }
    return READ_OK;
}

read_error_code_t from_bmp(FILE* const file,image_t* read){
    read_error_code_t error_code = 0;
    bmp_header_t* header = malloc(sizeof(bmp_header_t));
    error_code = read_header(file,header);
    if(error_code) {
        return error_code;
    }
    read = malloc(sizeof(image_t));
    read->height = header->biHeight;
    read->width = header->biWidth;
    error_code = read_pixels(file,header->bOffBits, read->data,read->width,read->height);
    return error_code;
}

void rotate(image_t* const image) {
    size_t i, j;
    size_t w = image->width;
    size_t h = image->height;
    pixel_t* rotated = malloc(sizeof(pixel_t)*w*h);
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            *(rotated + i*h + j) = *(image->data + (h - j - 1)*w + i);
        }
    }
    image->width  = h;
    image->height = w;
    free(image->data);
    image->data = rotated;
}

