#include "game.h"

struct inp {
    char up;
    char down;
    char con;
} gamepad;




bool upFlag = true;
bool set = true;

void game() {
    gamepad.up      = 'w';
    gamepad.down    = 's';
    gamepad.con     = 'j';
    
    /*
    if (noDataF) {
        nodat();
    }
    else {title();}
    */
    title();
}

/*
void nodat() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, noblack,0,0);
    draw_set(&frame_buffer_info, nodata,150,110);
    draw_fin(&frame_buffer_info);
}
*/

static void title() {
    drawTitle();
    
    while(1) {
        key = input();
        
        if (key == gamepad.down) {
            upFlag = false;
        }
        if (key == gamepad.up){
            upFlag = true;
        }
        if (key == gamepad.con){
            goto exit_loop;
        }
        drawTitle();
    } exit_loop:
    if (upFlag) { newgame(); }
    else {settings(); }
}

static void drawTitle() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    draw_set(&frame_buffer_info, titl,33,20);
    draw_set(&frame_buffer_info, menu,160,120);
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,123,128);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,120,199);
    }
    draw_fin(&frame_buffer_info);
}

static void settings() {
    drawSettings();
}

static void drawSettings() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    draw_set(&frame_buffer_info, setting,120,40);
    draw_set(&frame_buffer_info, pback,200,230);
    
    if (set) {
        draw_set(&frame_buffer_info, num_thr,260,40);
    }
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,100,40);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,100,130);
    }
    draw_fin(&frame_buffer_info);
}

static void newgame() {
    drawGame();
}

static void drawGame() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    draw_set(&frame_buffer_info,ob,450,236);
    draw_set(&frame_buffer_info,player,60,236);
    draw_fin(&frame_buffer_info);
}