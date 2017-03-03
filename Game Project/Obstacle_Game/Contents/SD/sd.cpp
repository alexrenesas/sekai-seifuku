#include "sd.h"

SDFileSystem_GR_PEACH storage("sd");

uint8_t  BinaryTable[0x0018A580uL]__attribute((aligned(32)));

bool sdInit() {
    long lSize;
    size_t result;
    
    printf("Loading...\n");
    
    // open file to be read
    FILE *fp = fopen("/sd/game.bin", "rb");
    if(fp == NULL) {
        return 0;
    }
    //printf("File open success!\n");
    
    // obtain file size:
    fseek (fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind (fp);
    
    result = fread((char*)BinaryTable,1,lSize,fp);
    if(result != (lSize)) {
            printf("File read failed\n");
            return 0;
        }
    //printf("File read success!\n");
    
    fclose(fp);
    return 1; 
}

