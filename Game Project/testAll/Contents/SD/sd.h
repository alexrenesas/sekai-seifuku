#ifndef SD
#define SD

#include "SDFileSystem.h"
#include <stdio.h>
#include "SDFileSystem_GR_PEACH.h"

#define BUFFER_SIZE                    (8)

#define BG_File                        ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00000000 ))
#define Char_File                      ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x0007F820 ))
#define Obs_File                       ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00080D80 ))

extern SDFileSystem sd;
extern uint8_t  RGA_Sample_BinaryImage[542368];
 
bool sdInit();


#endif