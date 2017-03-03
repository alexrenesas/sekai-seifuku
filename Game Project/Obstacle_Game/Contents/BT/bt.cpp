#include "bt.h"

Serial btm(P8_13, P8_11);
Serial usb(P6_3, P6_2);

void btInit() {
    btm.baud(115200);
    usb.baud(921600);
}

char input() {
    if (btm.readable()) {
        return btm.getc();
    }
    
    if (usb.readable()) {
        return usb.getc();
    }
    return NULL;
}

    
        
    