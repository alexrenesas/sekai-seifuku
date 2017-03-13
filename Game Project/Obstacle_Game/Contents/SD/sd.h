#ifndef SD
#define SD

#include "SDFileSystem.h"
#include <stdio.h>
#include "SDFileSystem_GR_PEACH.h"

#define  num_one                        ((const graphics_image_t*)( BinaryTable + 0x00000000 ))
#define  num_two                        ((const graphics_image_t*)( BinaryTable + 0x00000FE0 ))
#define  num_thr                        ((const graphics_image_t*)( BinaryTable + 0x00001FC0 ))
#define  num_fou                        ((const graphics_image_t*)( BinaryTable + 0x00002FA0 ))
#define  num_fiv                        ((const graphics_image_t*)( BinaryTable + 0x00003F80 ))
#define  num_six                        ((const graphics_image_t*)( BinaryTable + 0x00004F60 ))
#define  num_sev                        ((const graphics_image_t*)( BinaryTable + 0x00005F40 ))
#define  num_eig                        ((const graphics_image_t*)( BinaryTable + 0x00006F20 ))
#define  num_nin                        ((const graphics_image_t*)( BinaryTable + 0x00007F00 ))
#define  num_zer                        ((const graphics_image_t*)( BinaryTable + 0x00008EE0 ))
#define  arrow                          ((const graphics_image_t*)( BinaryTable + 0x00009EC0 ))
#define  yarrow                         ((const graphics_image_t*)( BinaryTable + 0x0000A780 ))
#define  back                           ((const graphics_image_t*)( BinaryTable + 0x0000B040 ))
#define  dead                           ((const graphics_image_t*)( BinaryTable + 0x0000C3A0 ))
#define  black                          ((const graphics_image_t*)( BinaryTable + 0x0008BBC0 ))
#define  white                          ((const graphics_image_t*)( BinaryTable + 0x0010B3E0 ))
#define  dot                            ((const graphics_image_t*)( BinaryTable + 0x0018AC00 ))
#define  goaaalll                       ((const graphics_image_t*)( BinaryTable + 0x0018B360 ))
#define  goal                           ((const graphics_image_t*)( BinaryTable + 0x0019BB20 ))
#define  haikei                         ((const graphics_image_t*)( BinaryTable + 0x0019DEE0 ))
#define  jumpcon                        ((const graphics_image_t*)( BinaryTable + 0x0021D700 ))
#define  menu                           ((const graphics_image_t*)( BinaryTable + 0x00220660 ))
#define  ob                             ((const graphics_image_t*)( BinaryTable + 0x0023CC40 ))
#define  pause                          ((const graphics_image_t*)( BinaryTable + 0x0023E2E0 ))
#define  paused                         ((const graphics_image_t*)( BinaryTable + 0x0023F900 ))
#define  pback                          ((const graphics_image_t*)( BinaryTable + 0x00244C00 ))
#define  player                         ((const graphics_image_t*)( BinaryTable + 0x00248520 ))
#define  setting                       ((const graphics_image_t*)( BinaryTable + 0x00249A80 ))
#define  titl                          ((const graphics_image_t*)( BinaryTable + 0x00266060 ))

extern uint8_t  BinaryTable[0x0028A300uL];
 
bool sdInit();


#endif