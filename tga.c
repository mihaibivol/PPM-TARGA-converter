#include"tga.h"

/*check if the TGA file is supported*/
int CheckTGA(char *filename){
    FILE *TGAfile;
    TGAfile = fopen(filename, "r");
    if(!TGAfile)
        return ERRORTGA;

    int value;
    /*escape the image identification filed size*/

    fseek(TGAfile, 1, SEEK_CUR);
    /*check if color map included
    this shouldn't be included since it's an unmapped image type
        if included return error*/
    value = 0;
    fread(&value, 1, 1, TGAfile);
    if(value){
        fclose(TGAfile);
        return ERRORTGA;
    }

    /*check the image color type
    if not type 2, return error*/
    value = 0;
    fread(&value, 1, 1, TGAfile);
    if(value != 2){
        fclose(TGAfile);
        return ERRORTGA;
    }

    /*escape:
        color map specification
        origin of image
        image width and height*/

    fseek(TGAfile, 16, SEEK_SET);

    /*check if Targa 24, if not return error*/
    value = 0;
    fread(&value, 1, 1, TGAfile);
    if(value != 24){
        fclose(TGAfile);
        return ERRORTGA;
    }

    /*check the image descriptor byte
    for tga type 2, Targa24 this byte can have the values:
        0   -   origin in lower left-hand corner
        32  -   origin in upper left-hand corner*/
    fread(&value, 1, 1, TGAfile);
    if(value == 0){
        fclose(TGAfile);
        return TGA2LL;
    }
    if(value == 32){
        fclose(TGAfile);
        return TGA2UL;
    }
    fclose(TGAfile);
    return value;
}

/*loads tga image type 2 with origin in lower left corner*/
Image* LoadTGA2LL(char *filename){
    FILE *TGAfile;
    TGAfile = fopen(filename,"r");

    if(!TGAfile)
        return NULL;

    /*read the identification field size*/
    int idSize = 0;
    fread(&idSize, 1, 1, TGAfile);

    /*seek to the width field*/
    fseek(TGAfile, 12, SEEK_SET);

    /*read the image width and height*/
    int width = 0, height = 0;
    fread(&width, 1, 2, TGAfile);
    fread(&height, 1, 2, TGAfile);

    /*seek to the color map data*/
    fseek(TGAfile, 18 + idSize, SEEK_SET);

    /*create image object*/
    Image *image = ImageAloc(width, height);

    if(!image){
        fclose(TGAfile);
        return NULL;
    }

    /*read the image data*/
    int i, j;
    for(i = height - 1; i > 0; i--){
        for(j = 0; j < width; j++){
            image->pixels[i][j].R = 0;
            image->pixels[i][j].G = 0;
            image->pixels[i][j].B = 0;
            fread(&image->pixels[i][j].B, 1, 1, TGAfile);
            fread(&image->pixels[i][j].G, 1, 1, TGAfile);
            fread(&image->pixels[i][j].R, 1, 1, TGAfile);
        }
    }

    fclose(TGAfile);

    return image;
}

/*loads tga image type 2 with origin in upper left corner*/
Image* LoadTGA2UL(char *filename){
    FILE *TGAfile;
    TGAfile = fopen(filename,"r");

    if(!TGAfile)
        return NULL;

    /*read the identification field size*/
    int idSize = 0;
    fread(&idSize, 1, 1, TGAfile);

    /*seek to the width field*/
    fseek(TGAfile, 12, SEEK_SET);

    /*read the image width and height*/
    int width = 0, height = 0;
    fread(&width, 1, 2, TGAfile);
    fread(&height, 1, 2, TGAfile);

    /*seek to the color map data*/
    fseek(TGAfile, 18 + idSize, SEEK_SET);

    /*create image object*/
    Image *image = ImageAloc(width, height);

    if(!image){
        fclose(TGAfile);
        return NULL;
    }

    /*read the image data*/
    int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            image->pixels[i][j].R = 0;
            image->pixels[i][j].G = 0;
            image->pixels[i][j].B = 0;
            fread(&image->pixels[i][j].B, 1, 1, TGAfile);
            fread(&image->pixels[i][j].G, 1, 1, TGAfile);
            fread(&image->pixels[i][j].R, 1, 1, TGAfile);
        }
    }

    fclose(TGAfile);

    return image;
}

/*dumps to TGA*/
void DumpToTGA(char *filename, Image image){
    FILE *TGAfile;
    TGAfile = fopen(filename,"w");

    int width, height, i, j;
    width = image.width;
    height = image.height;

    /*write 18 bytes of 0's*/
    int value = 0;
    for(i = 0; i < 18; i++)
        fwrite(&value, 1, 1, TGAfile);

    /*write in the image type field*/
    value = 2;
    fseek(TGAfile, 2, SEEK_SET);
    fwrite(&value, 1, 1, TGAfile);

    /*write width and height*/
    fseek(TGAfile, 12, SEEK_SET);
    fwrite(&width, 1, 2, TGAfile);
    fwrite(&height, 1, 2, TGAfile);

    /*write 24*/
    value = 24;
    fwrite(&value, 1, 1, TGAfile);
    fseek(TGAfile, 18, SEEK_SET);

    /*write color map*/
    for(i = image.height - 1; i > 0; i--){
        for(j = 0; j < image.width; j++){
            fwrite(&image.pixels[i][j].B, 1, 1, TGAfile);
            fwrite(&image.pixels[i][j].G, 1, 1, TGAfile);
            fwrite(&image.pixels[i][j].R, 1, 1, TGAfile);
        }
    }

    fclose(TGAfile);
}
