#include <stdio.h>
#include "readwrite.c"
int main() {
    FILE *file = fopen("/home/vladlensky/CLionProjects/Lab5/src/Graphics_duck.bmp", "r+");
    FILE *file1 = fopen("/home/vladlensky/CLionProjects/Lab5/src/to.bmp", "r+");
    if (file == NULL)
        printf("File does not exist!");
    else {
        image_t *image = malloc(sizeof(image_t));
        image->width = 1;
        printf("%d",from_bmp(file, image));
        /*rotate(image);*/
        write_image(file1,image);
        return 0;
    }
}