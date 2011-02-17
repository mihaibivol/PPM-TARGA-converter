#include"convert.h"

int main(int argc, char **argv){

    if(argc != 3){
        printf("Usage: convert file1 file2\n");
        return ERROR;
    }

    /*check extensions*/
    char *ext1 = argv[1], *ext2 = argv[2];

    while(strchr(ext1, '.') != NULL)
        ext1 = strchr(ext1, '.') + 1;

    while(strchr(ext2, '.') != NULL)
        ext2 = strchr(ext2, '.') + 1;

    if(ext1 == argv[1] || ext2 == argv[2]){
        Error("ERROR: bad filenames, please check extension\n");
        return ERROR;
    }

    if(!strcmp(ext1, "tga") && !strcmp(ext2, "ppm"))
        return TGAtoPPM(argv[1], argv[2]);

    if(!strcmp(ext1, "ppm") && !strcmp(ext2, "tga"))
        return PPMtoTGA(argv[1], argv[2]);

    printf("Can't do that!\n");
    return ERROR;
}
