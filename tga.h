/*supports tga type 2 [unmapped RGB images], Targa 24*/

#ifndef __TGA_H__
#define __TGA_H__

#include<stdio.h>
#include<stdlib.h>
#include"image.h"

#define ERRORTGA -1

/*tga image type 2 with origin in upper left corner*/
#define TGA2UL 1
/*tga image type 2 with origin in lower left corner*/
#define TGA2LL 2

/*Check if the TGA file is supported
  Returns the type of the image*/
int CheckTGA(char *filename);

/*
    Returns pointer to Image Object loaded from file
    Returns NULL if the Image Object couldn't be loaded*/
Image* LoadTGA2LL(char *filename);
Image* LoadTGA2UL(char *filename);

/*dumps Image Object to TGA*/
void DumpToTGA(char *filename, Image image);

#endif
