#include "sd.h"

SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

uint8_t  RGA_Sample_BinaryImage[542368]__attribute((aligned(32)));

bool sdInit() {
    long lSize;
    char * buffer;
    char * wbuf;
    size_t result;
    int file_done = 0;    
    long read_prog = 0;
    
    //printf("SD initialisation...\n");
    
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
    
    /*printf("File size: %d bytes\n", lSize); 
    printf("Table size %d bytes\n", sizeof(RGA_Sample_BinaryImage));
    printf("\n");
    printf("Beginning read loop...\n");*/

    while(file_done != BUFFER_SIZE) {
        printf("Loop count: %d/%d\n", (file_done+1), BUFFER_SIZE);
        
        // allocate memory to contain the whole file:
        buffer = (char*) malloc(sizeof(char)*lSize/BUFFER_SIZE);
        
        if(buffer == NULL) {
            printf("Buffer not allocated\n");
            return 0;
        }
        //printf("Buffer allocated!\n");
        
        // copy the file into the buffer:
        result = fread(buffer,1,(lSize/BUFFER_SIZE),fp);
        
        if(result != (lSize/BUFFER_SIZE)) {
            printf("File read failed\n");
            return 0;
        }
        //printf("File read success!\n");
        
        // move the buffer contents over to the table
        //printf("Buffer Looping...\n");
        for(long i = 0; i < (lSize/BUFFER_SIZE); i++) {           
            RGA_Sample_BinaryImage[read_prog] = buffer[i];
            read_prog++;
        }
        
        free(buffer);
        printf("\n");
        file_done++;
    }
    
    //printf("Binary Table: %X\n", RGA_Sample_BinaryImage);
       
    fclose(fp);
    
    file_done = 0;
    read_prog = 0;
        
    // write the buffer contents to a new binary file
    fp = fopen("/sd/you.bin", "wb");
    if(fp == NULL) {
        printf("File open failed\n");
        return 0;
    }  
    printf("File open success!\n");
        
    wbuf = (char*)RGA_Sample_BinaryImage;
    //printf("New Buffer: %X\n", buffer);
    result = fwrite(wbuf, sizeof(char), lSize, fp);
    
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

