#include "mbed.h"
#include <stdio.h>

Serial btm(P8_13, P8_11);
Serial usb(P6_3, P6_2);

char input() {
    
    usb.baud(9600);
    if (btm.readable()) {
        return btm.getc();
    }
    btm.baud(115200);
    if (usb.readable()) {
        return usb.getc();
    }
}

    
        
    