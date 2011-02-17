/*handles PPM input file*/

#ifndef __PPM_H__
#define __PPM_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"image.h"

#define ASCIIPPM 1
#define BINARYPPM 2
#define ERRORPPM -1

/*checks if the file has the magic number of a PPM file
returns:    ASCIIPPM for an ASCII file
            BINARYPPM for an binary file
            ERRORPPM if the file doesn't have the magic number of a PPM file*/
int CheckPPM(char *filename);

/*Returns pointer to Image Object loaded from file
    Returns NULL if the Image Object couldn't be loaded*/

/*loads Ascii PPM*/
Image* LoadPPMAscii(char *filename);

/*loads BinaryPPM*/
Image* LoadPPMBinary(char *filename);

/*dumps Image Object to ASCII PPM*/
void DumpToPPM(char *filename, Image image);

#endif
