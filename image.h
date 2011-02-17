/*definition of the image object
currently helds the width, height and the image pixelmap*/

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include<stdlib.h>

#define MAXCOLOR 255

/*
RGB:
R   -   red channel value
G   -   green channel value
B   -   blue channel value
*/
typedef struct RGB{
    short R,G,B;
} RGB;

/*
IMAGE:
local image:
width   -   image width
height  -   image height
pixels  -   array of pixels in RGB*/
typedef struct Image{
    int width, height;
    RGB **pixels;
} Image;

/*create Image Object with given width and height
Arguments:
    int width   -   image width
    int height  -   image height
returns pointer to created Object*/
Image *ImageAloc(int width, int height);

/*destroy Image Object
Arguments:
    Image **image   -   pointer to pointer to Image Object  */
void ImageDestroy(Image **image);


#endif
