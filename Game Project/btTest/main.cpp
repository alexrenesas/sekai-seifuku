#include "mbed.h"
#include "bt.h"
#include <stdio.h>

DigitalOut myled(LED1);
char key;

int main() {
    while(1) {
        key = input();
        
        wait(1);
        
        if (key == 's') {
            myled = 1;
            wait(0.2);
            myled = 0;
        }
        
        else if (key == 'N') {
            myled = 1;
        }
    }
}
