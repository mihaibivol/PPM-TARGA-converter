#include"ppm.h"

int CheckPPM(char *filename){
    /*open PPM file*/

    FILE *PPMfile;
    PPMfile = fopen(filename, "r");
    if(!PPMfile)
        return ERRORPPM;

    char magic[3];

    /*read the magic number of the file (first two bytes)*/
    fread(magic, 1, 2, PPMfile);
    magic[2] = '\0';
    fclose(PPMfile);
    /*check if the file is an ASCII portable pixmap*/

    if(!strcmp(magic, "P3"))
        return ASCIIPPM;
    /*check if the file is an BINARY portable pixmap*/
    if(!strcmp(magic, "P6"))
        return BINARYPPM;

    return ERRORPPM;
}

void escapeWhitespace(FILE *file){
    char chr;
    char separators[] = " \n\t";
    do{
        fscanf(file, "%c", &chr);
        if(chr == '#'){
            do{
                fscanf(file, "%c", &chr);
            }while (chr!='\n');
        }
    }while(strchr(separators, chr));
    fseek(file, -sizeof(char), SEEK_CUR);
}

Image* LoadPPMAscii(char *filename){

    FILE *PPMfile;
    PPMfile = fopen(filename, "r");
    if(!PPMfile)
        return NULL;

    int width, height, maxcolors;

    /*escape magic number*/
    fseek(PPMfile, 2, SEEK_CUR);
    /*escape commented lines and whitespaces*/
    escapeWhitespace(PPMfile);

    /*read width height and number of colours*/
    fscanf(PPMfile, "%d%d%d", &width, &height, &maxcolors);
    if(maxcolors > MAXCOLOR){
        return NULL;
    }

    Image *image = ImageAloc(width, height);

    if(!image){
        fclose(PPMfile);
        return NULL;
    }

    int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            fscanf(PPMfile, "%hd%hd%hd",
                &image->pixels[i][j].R,
                &image->pixels[i][j].G,
                &image->pixels[i][j].B);
        }
    }


    fclose(PPMfile);
    return image;
}

Image* LoadPPMBinary(char *filename){

    FILE *PPMfile;
    PPMfile = fopen(filename, "r");
    if(!PPMfile)
        return NULL;
    int width, height, maxcolors;

    /*escape magic number*/
    fseek(PPMfile, 2, SEEK_CUR);
    /*escape commented lines and whitespaces*/
    escapeWhitespace(PPMfile);
    fscanf(PPMfile, "%d%d%d", &width, &height, &maxcolors);

    if(maxcolors > MAXCOLOR){
        return NULL;
    }

    Image *image = ImageAloc(width, height);

    if(!image){
        fclose(PPMfile);
        return NULL;
    }

    escapeWhitespace(PPMfile);
    int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            image->pixels[i][j].R = 0;
            image->pixels[i][j].G = 0;
            image->pixels[i][j].B = 0;
            fread(&image->pixels[i][j].R, 1, 1, PPMfile);
            fread(&image->pixels[i][j].G, 1, 1, PPMfile);
            fread(&image->pixels[i][j].B, 1, 1, PPMfile);
        }
    }

    fclose(PPMfile);
    return image;
}

void DumpToPPM(char *filename, Image image){
    FILE *PPMfile;
    PPMfile = fopen(filename, "w");

    fprintf(PPMfile, "P3\n");
    fprintf(PPMfile, "#i love cdl\n");
    fprintf(PPMfile, "%d %d\n", image.width, image.height);
    fprintf(PPMfile, "255\n");

    int i, j;
    for(i = 0; i < image.height; i++){
        for(j = 0; j < image.width; j++){
            fprintf(PPMfile, "%d %d %d ",
                image.pixels[i][j].R,
                image.pixels[i][j].G,
                image.pixels[i][j].B);
        }
    }
    fclose(PPMfile);
}
