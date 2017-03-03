#include "sd.h"

SDFileSystem_GR_PEACH storage("sd");

uint8_t  RGA_Sample_BinaryImage[542368]__attribute((aligned(32)));

bool sdInit() {
    long lSize;
    size_t result;
    
    printf("SD initialisation...\n");
    
    // open file to be read
    FILE *fp = fopen("/sd/safe.bin", "rb");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }
    //printf("File open success!\n");
    
    // obtain file size:
    fseek (fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind (fp);
    
    result = fread((char*)RGA_Sample_BinaryImage,1,lSize,fp);
    if(result != (lSize)) {
            printf("File read failed\n");
            return 0;
        }
    //printf("File read success!\n");
    
    fclose(fp);
    return 1; 
}

