#include "mbed.h"
#include "bt.h"
#include <stdio.h>

DigitalOut myled(LED1);
char key;

int main() {
    btInit();
    
    while(1) {
        key = input();
        
        if (key == 's') {
            myled = 1;
            wait(0.1);
            myled = 0;
        }
        
        else if (key == 'N') {
            myled = 1;
        }
    }
}
