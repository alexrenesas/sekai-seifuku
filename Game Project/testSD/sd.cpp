#include "sd.h"

SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

/*
bool sdInit() {
    uint8_t lSize;
    char * buffer;
    size_t result;
    
    printf("SD initialisation...\n");   
    
    
    FILE *fp = fopen("/sd/test.txt", "rb");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }
    
    printf("File open success!\n");
    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    lSize = ftell(fp);
    rewind (fp);
    
    printf("size of file: %d\n", lSize);
    
    // allocate memory to contain the whole file:
    buffer = (char*) malloc(sizeof(char)*lSize);
    
    
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
    
    printf("buffer size: %d\n", sizeof(buffer));
    
    for(int i = 0; i <= lSize; i++) {
    printf("%c", buffer[i]);
    }
    
    printf("\nFile read success!\n");
    printf("Result:\n %s\n", buffer);
    
    fclose(fp); 
    free(buffer);
    return 1;
} */

bool sdInit() {
    uint8_t lSize;
    char * buffer;
    size_t result;
    
    printf("SD initialisation...\n");   
    
    FILE *fp = fopen("/sd/new.bin", "rb");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }
    printf("File open success!\n");
    
    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    lSize = ftell(fp);
    rewind (fp);
    printf("size of file: %d\n", lSize);    

    // allocate memory to contain the whole file:
    buffer = (char*) malloc(sizeof(char)*lSize);
    
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
    
    printf("Buffer Result: %X\n", buffer);
    
    uint8_t  RGA_Sample_BinaryImage[sizeof(buffer)];
    
    // check the contents of both buffer and table
    /*
    printf("Buffer Loop:");
    for(int i = 0; i <= lSize; i++) {
        RGA_Sample_BinaryImage[i] = buffer[i];
        printf("%X", buffer[i]);
    }
    
    printf("\nBinary Table: %X\n", RGA_Sample_BinaryImage);
    printf("BT Loop:");
    for(int i = 0; i <= lSize; i++) {
        printf("%X", RGA_Sample_BinaryImage[i]);
    }
    printf("\n");
    */
    
    fclose(fp); 
    
    // write the buffer contents to a new binary file
    fp = fopen("/sd/you.bin", "wb");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }  
    printf("File open success!\n");
        
    buffer = (char*)RGA_Sample_BinaryImage;
    //printf("New Buffer: %X\n", buffer);
    result = fwrite(buffer, sizeof(char), lSize, fp);
    
    if(result != lSize) {
        printf("File write failed\n");
        return 0;
    }
    printf("File write success\n");
    //fprintf(fp, "%X",buffer);
    fclose(fp);
    
    free(buffer);
    return 1;
}

