#include "mbed.h"
#include "lcd.h"
#include "bt.h"
//#include "sd.h"

void go();
char key;

int main() {
    
    btInit();
    lcdInit();
    
    while(1) {
        key = input();
        if (key == 'g') {
            go();
        }
    }
}

void go() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, BG_File, 0, 0);
    draw_fin(&frame_buffer_info);
}
    
/* TODO list
- Bring over LCD and get it to compile                          DONE
- Bring over Bluetooth and get it to compile                    DONE
- Press a button, which causes the LCD to display               DONE
*/