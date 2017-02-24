#include "mbed.h"
#include "sd.h"
 
int main() {
    Serial pc(USBTX, USBRX);
    
    pc.baud(921600); 
    
    if (!sdInit()) {
        printf("SD card failed\n");
    }
    else {
        printf("SD card success!\n");
    }
}

/* TODO list
- Move Audio_WAV sample over to main and get it to compile      DONE
- Open and read a simple text file                              DONE          
- Open and assign the image binary table file                   DONE
- Move the contents to a separate file to call it from Main     DONE
- Manage the buffer and available memory by reading in parts
*/