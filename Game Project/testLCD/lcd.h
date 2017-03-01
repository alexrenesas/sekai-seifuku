#ifndef LCD
#define LCD

#include "mbed.h"
#include "DisplayBace.h"
#include "rtos.h"
#include "RGA.h"
#include "BinaryImage_RZ_A1H.h"
#include "LCD_shield_config_4_3inch.h"

#define GRAPHICS_FORMAT                     (DisplayBase::GRAPHICS_FORMAT_RGB565)
#define WR_RD_WRSWA                         (DisplayBase::WR_RD_WRSWA_32_16BIT)

/* FRAME BUFFER Parameter */
#define FRAME_BUFFER_BYTE_PER_PIXEL         (2)
#define FRAME_BUFFER_STRIDE                 (((LCD_PIXEL_WIDTH * FRAME_BUFFER_BYTE_PER_PIXEL) + 31u) & ~31u)
#define OBSIZE                              (34)

#define MAX_JPEG_SIZE                       (1024 * 450)

void lcdInit();
void draw();
void draw_image(frame_buffer_t* frmbuf_info, const graphics_image_t* image, uint32_t pos_x, uint32_t pos_y, int width, int height);
void draw_set(frame_buffer_t* frmbuf_info, const graphics_image_t* image,  uint32_t pos_x, uint32_t pos_y, int width, int height);
void draw_fin(frame_buffer_t* frmbuf_info);
void Swap_FrameBuffer(frame_buffer_t * frmbuf_info);
void Update_LCD_Display(frame_buffer_t * frmbuf_info);
void Start_LCD_Display(uint8_t * p_buf);
void clear(frame_buffer_t* frmbuf_info, int x, int y, int w, int h); 

 
extern frame_buffer_t frame_buffer_info;




#endif