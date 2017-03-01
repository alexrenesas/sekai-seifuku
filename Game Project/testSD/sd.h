#ifndef SD
#define SD

#include "mbed.h"
#include "SDFileSystem.h"
#include <stdio.h>

#define BUFFER_SIZE                 (8)
 
extern SDFileSystem sd;
static uint8_t  RGA_Sample_BinaryImage[542368];
 
bool sdInit();


#endif