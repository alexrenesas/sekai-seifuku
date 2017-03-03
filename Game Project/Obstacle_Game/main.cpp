#include "mbed.h"
#include "lcd.h"
#include "bt.h"
#include "sd.h"
#include "game.h"

//bool noDataF = false;

int main() {
    
    btInit();
    lcdInit();
    
    if (!sdInit()) {
        printf("No Data!\n");
        //noDataF = true;
    }
    else {
        printf("Ready!\n");
    }
    game();
    
}
   