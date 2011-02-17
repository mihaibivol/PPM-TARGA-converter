/*handles conversion from:
    -TGA to PPM
    -PPM to TGA*/
#ifndef __CONVERT_H__
#define __CONVERT_H__

#define ERROR -1
#define SUCCESS 0

#include"ppm.h"
#include"tga.h"
#include"image.h"

void Error(char *message);

int TGAtoPPM(char *tgaFile, char *ppmFile);
int PPMtoTGA(char *tgaFile, char *ppmFile);

#endif
