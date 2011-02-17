#include"convert.h"

void Error(char *message){
    fprintf(stderr, "%s", message);
}

int TGAtoPPM(char *tgaFile, char *ppmFile){

    int type = CheckTGA(tgaFile);

    /*if the tga file isn't supported return error*/
    if(type == ERRORTGA){
        Error("ERROR: the TGA file is corrupted or not supported!\n");
        return ERROR;
    }

    /*load image*/
    Image *image;
    if(type == TGA2LL)
        image = LoadTGA2LL(tgaFile);
    else if(type == TGA2UL)
        image = LoadTGA2UL(tgaFile);

    if(!image){
        Error("ERROR: TGA file could not be loaded");
        return ERROR;
    }

    /*dump image*/
    DumpToPPM(ppmFile, *image);
    ImageDestroy(&image);
    return SUCCESS;
}

int PPMtoTGA(char *ppmFile, char *tgaFile){

    int type = CheckPPM(ppmFile);

    /*if the ppm file isn't supported return error*/
    if(type == ERRORPPM){
        Error("ERROR: the PPM file is corrupted or not supported!\n");
        return ERROR;
    }
    /*load image*/
    Image *image;
    if(type == ASCIIPPM)
        image = LoadPPMAscii(ppmFile);
    else if(type == BINARYPPM)
        image = LoadPPMBinary(ppmFile);

    if(!image){
        Error("ERROR: PPM file could not be loaded");
        return ERROR;
    }

    /*dump image*/
    DumpToTGA(tgaFile, *image);
    ImageDestroy(&image);
    return SUCCESS;
}
