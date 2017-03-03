#include "game.h"

void game() {
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
void title() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    draw_set(&frame_buffer_info, titl,33,20);
    draw_fin(&frame_buffer_info);
}