#include "lcd.h"

int cnt = 480;

void go();

int main() {
    
    lcdInit();  
    while(1) { 
        go(); 
        if (cnt < -36) cnt = 480;  
      }   
        
}

void go() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, Haikei_File, 0, 0);
    draw_set(&frame_buffer_info,Obs_File, cnt, 236);
    draw_fin(&frame_buffer_info);
    cnt -= 10;
    
}
    
/* TODO list
- Move DigitalSignage over to my own program and succesfully compile    DONE
- Create binary images with the tool and add them to the project        DONE
- Draw an image using my sample program                                 DONE
- Learn how headers work, and how to pass data over to the lcd prog     DONE
- Learn how to use image synthesis (by not clearing the buffer?)        DONE
- Test the limits of image synthesis to draw my game screen             DONE
- Make an object move smoothly to a given fps                           DONE
- Correctly implement the double buffer                                 DONE
- Create the game image files and convert them to binary                DONE
*/