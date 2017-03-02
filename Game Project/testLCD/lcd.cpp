#include "lcd.h"

InterruptIn button(USER_BUTTON0);
static Serial pc(USBTX, USBRX);
static DisplayBase Display;
static Canvas2D_ContextClass canvas2d;
static DigitalOut  lcd_pwon(P7_15);
static DigitalOut  lcd_blon(P8_1);
static PwmOut      lcd_cntrst(P8_15);

#if defined(__ICCARM__)
#pragma data_alignment=32
static uint8_t user_frame_buffer1[FRAME_BUFFER_STRIDE * LCD_PIXEL_HEIGHT];
#pragma data_alignment=32
static uint8_t user_frame_buffer2[FRAME_BUFFER_STRIDE * LCD_PIXEL_HEIGHT];
#pragma data_alignment=8
static uint8_t JpegBuffer[MAX_JPEG_SIZE]@ ".mirrorram";  //8 bytes aligned!;
#else
static uint8_t user_frame_buffer1[FRAME_BUFFER_STRIDE * LCD_PIXEL_HEIGHT]__attribute((aligned(32)));  /* 32 bytes aligned */
static uint8_t user_frame_buffer2[FRAME_BUFFER_STRIDE * LCD_PIXEL_HEIGHT]__attribute((aligned(32))); /* 32 bytes aligned */
static uint8_t JpegBuffer[MAX_JPEG_SIZE]__attribute((section("NC_BSS"),aligned(8)));  //8 bytes aligned!;
#endif
frame_buffer_t frame_buffer_info;
static volatile int32_t vsync_count = 0;

/****** LCD ******/
static void IntCallbackFunc_LoVsync(DisplayBase::int_type_t int_type) {
    /* Interrupt callback function for Vsync interruption */
    if (vsync_count > 0) {
        vsync_count--;
    }
}

static void Wait_Vsync(const int32_t wait_count) {
    /* Wait for the specified number of times Vsync occurs */
    vsync_count = wait_count;
    while (vsync_count > 0) {
        /* Do nothing */
    }
}

static void Init_LCD_Display(void) {
    DisplayBase::graphics_error_t error;
    DisplayBase::lcd_config_t lcd_config;

    PinName lvds_pin[8] = {
        /* data pin */
        P5_7, P5_6, P5_5, P5_4, P5_3, P5_2, P5_1, P5_0
    };

    lcd_pwon = 0;
    lcd_blon = 0;
    Thread::wait(100);
    lcd_pwon = 1;
    lcd_blon = 1;

    Display.Graphics_Lvds_Port_Init(lvds_pin, 8);


    /* Graphics initialization process */
    lcd_config = LcdCfgTbl_LCD_shield;
    error = Display.Graphics_init(&lcd_config);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        mbed_die();
    }

    /* Interrupt callback function setting (Vsync signal output from scaler 0) */
    error = Display.Graphics_Irq_Handler_Set(DisplayBase::INT_TYPE_S0_LO_VSYNC, 0, IntCallbackFunc_LoVsync);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        mbed_die();
    }
}

static void Start_LCD_Display(uint8_t * p_buf) {
    DisplayBase::rect_t rect;

    rect.vs = 0;
    rect.vw = LCD_PIXEL_HEIGHT;
    rect.hs = 0;
    rect.hw = LCD_PIXEL_WIDTH;
    Display.Graphics_Read_Setting(
        DisplayBase::GRAPHICS_LAYER_0,
        (void *)p_buf,
        FRAME_BUFFER_STRIDE,
        GRAPHICS_FORMAT,
        WR_RD_WRSWA,
        &rect
    );
    Display.Graphics_Start(DisplayBase::GRAPHICS_LAYER_0);
}

static void Update_LCD_Display(frame_buffer_t * frmbuf_info) {
    Display.Graphics_Read_Change(DisplayBase::GRAPHICS_LAYER_0,
     (void *)frmbuf_info->buffer_address[frmbuf_info->draw_buffer_index]);
    Wait_Vsync(1);
}

static void Swap_FrameBuffer(frame_buffer_t * frmbuf_info) {
    if (frmbuf_info->draw_buffer_index == 1) {
        frmbuf_info->draw_buffer_index = 0;
    } else {
        frmbuf_info->draw_buffer_index = 1;
    }
}

void draw_image(frame_buffer_t* frmbuf_info, const graphics_image_t* image, 
 uint32_t pos_x, uint32_t pos_y, int width, int height) {

    Swap_FrameBuffer(frmbuf_info);
    /* Clear */
    canvas2d.clearRect(0, 0, frmbuf_info->width, frmbuf_info->height);
    /* Draw a image */
    canvas2d.globalAlpha = 1.0f;
    canvas2d.drawImage((const graphics_image_t*)image, pos_x, pos_y, width, height);
    R_OSPL_CLEAR_ERROR();
    /* Complete drawing */
    R_GRAPHICS_Finish(canvas2d.c_LanguageContext);
    Update_LCD_Display(frmbuf_info);
}

void draw_set(frame_buffer_t* frmbuf_info, const graphics_image_t* image, 
 uint32_t pos_x, uint32_t pos_y) {
    
    canvas2d.globalAlpha = 1.0f;
    canvas2d.drawImage((const graphics_image_t*)image, pos_x, pos_y);
    R_OSPL_CLEAR_ERROR(); 
}

void draw_fin(frame_buffer_t* frmbuf_info) {
    /* Complete drawing */
    R_GRAPHICS_Finish(canvas2d.c_LanguageContext);
    Update_LCD_Display(frmbuf_info);    
}

void clear(frame_buffer_t* frmbuf_info, int x, int y, int w, int h) {
    Swap_FrameBuffer(frmbuf_info);
    canvas2d.clearRect(x,y,w,h);
}

void lcdInit() {
    errnum_t err;
    Canvas2D_ContextConfigClass config;
    
     /* Change the baud rate of the printf() */
    pc.baud(921600);
    
    /* Initialization of LCD */
    Init_LCD_Display();    
    
    memset(user_frame_buffer1, 0, sizeof(user_frame_buffer1));
    memset(user_frame_buffer2, 0, sizeof(user_frame_buffer2));
    frame_buffer_info.buffer_address[0] = user_frame_buffer1;
    frame_buffer_info.buffer_address[1] = user_frame_buffer2;
    frame_buffer_info.buffer_count      = 2;
    frame_buffer_info.show_buffer_index = 0;
    frame_buffer_info.draw_buffer_index = 0;
    frame_buffer_info.width             = LCD_PIXEL_WIDTH;
    frame_buffer_info.byte_per_pixel    = FRAME_BUFFER_BYTE_PER_PIXEL;
    frame_buffer_info.stride            = LCD_PIXEL_WIDTH * FRAME_BUFFER_BYTE_PER_PIXEL;
    frame_buffer_info.height            = LCD_PIXEL_HEIGHT;
    frame_buffer_info.pixel_format      = PIXEL_FORMAT_RGB565;

    config.frame_buffer = &frame_buffer_info;
    canvas2d = R_RGA_New_Canvas2D_ContextClass(config);
    err = R_OSPL_GetErrNum();
    if (err != 0) {
        printf("Line %d, error %d\n", __LINE__, err);
        mbed_die();
    }

    /* Start of LCD */
    Start_LCD_Display(frame_buffer_info.buffer_address[0]);

    /* Backlight on */
    Thread::wait(200);
    lcd_cntrst.write(1.0);   
}