#ifndef  BINARYIMAGE_RZ_A1H_H
#define  BINARYIMAGE_RZ_A1H_H

#ifdef  __cplusplus
extern "C" {  /* Start of C Symbol */
#endif

extern const uint8_t  RGA_Sample_BinaryImage[ 0x00120060uL ];

#define  Obs_File                       ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00000000 ))
#define  num_one                        ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x000016A0 ))
#define  Haikei_File                    ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00002680 ))
#define  Set_File                       ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00081EA0 ))
#define  goal_File                      ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x0009E480 ))
#define  Blk_File                       ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x000A0840 ))

#ifdef  __cplusplus
 }  /* End of C Symbol */ 
#endif

#endif /* BINARYIMAGE_RZ_A1H_H */
