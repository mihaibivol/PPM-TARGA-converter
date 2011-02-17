#include"image.h"

Image *ImageAloc(int width, int height){
    Image *image;
    image = (Image*)malloc(sizeof(Image));

    int i, j;

    image->pixels = (RGB**)calloc(height, sizeof(RGB*));
    for(i = 0; i < height; i++)
        image->pixels[i] = (RGB*)calloc(width, sizeof(RGB));

    if(!image)
        return NULL;

    image->width = width;
    image->height = height;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            image->pixels[i][j].R = 0;
            image->pixels[i][j].G = 0;
            image->pixels[i][j].B = 0;
        }
    }

    return image;
}

void ImageDestroy(Image **image){
    free((*image)->pixels);
    free(*image);
    *image = NULL;
}
