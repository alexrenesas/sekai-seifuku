#include "sd.h"

SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");


bool sdInit() {
    long lSize;
    char * buffer;
    size_t result;
    
    printf("SD initialisation...\n");   
    
    FILE *fp = fopen("/sd/test.txt", "r");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }
    
    printf("File open success!\n");
    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    lSize = ftell (fp);
    rewind (fp);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    
    if(buffer == NULL) {
        printf("Buffer not allocated\n");
        return 0;
    }
    printf("Buffer allocated!\n");
    // copy the file into the buffer:
    result = fread(buffer,1,lSize,fp);
    if(result != lSize) {
        printf("File read failed\n");
        return 0;
    }
    
    printf("File read success!\n");
    printf("Result:\n %s\n", buffer);
    
    fclose(fp); 
    free(buffer);
    return 1;
}