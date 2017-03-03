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
#define  back                           ((const graphics_image_t*)( BinaryTable + 0x0000A780 ))
#define  black                          ((const graphics_image_t*)( BinaryTable + 0x0000BAE0 ))
#define  colon                          ((const graphics_image_t*)( BinaryTable + 0x0008B300 ))
#define  goaaalll                       ((const graphics_image_t*)( BinaryTable + 0x0008B5E0 ))
#define  goal                           ((const graphics_image_t*)( BinaryTable + 0x0009BDA0 ))
#define  haikei                         ((const graphics_image_t*)( BinaryTable + 0x0009E160 ))
#define  jumpcon                        ((const graphics_image_t*)( BinaryTable + 0x0011D980 ))
#define  menu                           ((const graphics_image_t*)( BinaryTable + 0x001208E0 ))
#define  ob                             ((const graphics_image_t*)( BinaryTable + 0x0013CEC0 ))
#define  pause                          ((const graphics_image_t*)( BinaryTable + 0x0013E560 ))
#define  paused                         ((const graphics_image_t*)( BinaryTable + 0x0013FB80 ))
#define  pback                          ((const graphics_image_t*)( BinaryTable + 0x00144E80 ))
#define  player                         ((const graphics_image_t*)( BinaryTable + 0x001487A0 ))
#define  settings                       ((const graphics_image_t*)( BinaryTable + 0x00149D00 ))
#define  titl                           ((const graphics_image_t*)( BinaryTable + 0x001662E0 ))

extern uint8_t  BinaryTable[0x0018A580uL];
 
bool sdInit();


#endif