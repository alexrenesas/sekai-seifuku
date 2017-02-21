#ifndef  BINARYIMAGE_RZ_A1H_H
#define  BINARYIMAGE_RZ_A1H_H

#ifdef  __cplusplus
extern "C" {  /* Start of C Symbol */
#endif

extern const uint8_t  RGA_Sample_BinaryImage[ 0x000FF040uL ];

#define  Title_File                     ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x00000000 ))
#define  Goal_File                      ((const graphics_image_t*)( RGA_Sample_BinaryImage + 0x0007F820 ))

#ifdef  __cplusplus
 }  /* End of C Symbol */ 
#endif

#endif /* BINARYIMAGE_RZ_A1H_H */
