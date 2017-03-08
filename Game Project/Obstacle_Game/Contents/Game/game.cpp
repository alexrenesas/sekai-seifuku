#include "game.h"

struct inp {
    char up;
    char down;
    char con;
    char bck;
} gamepad;

const graphics_image_t* numarray[10] = {
    num_zer, num_one, num_two, num_thr, num_fou, 
    num_fiv, num_six, num_sev, num_eig, num_nin
};

struct spike {
    int x,y;
    int w,h;    
} s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;

struct myplayer {
    int x,y;
    int w,h;
} p1;

spike spikes[10] = {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10};
int times[10] = {500,2000,2500,3000,4000,6000,7000,8700,9200,12000};
int deteru;
bool jumpFlag = false;
Timer game_timer;
bool upFlag = true;
bool backFlag = false;
bool set = true;
bool goalOut = false;
bool bkTitle = true;
char gameInput;
int max_jump = 10;
float gravity = 0.5;
float vel;
float fvel;
int jumpProg;
int fallProg;

void game() {
    gamepad.up      = 'w';
    gamepad.down    = 's';
    gamepad.con     = 'j';
    gamepad.bck     = 'b';
    
    /*
    if (noDataF) {
        nodat();
    }
    else {title();}
    */
    title();
}

/*
static void nodat() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, noblack,0,0);
    draw_set(&frame_buffer_info, nodata,150,110);
    draw_fin(&frame_buffer_info);
}
*/

static void title() {
    while(1) {
        drawTitle();
        upFlag = true;
        
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
    
    upFlag = true;
    while(1) {
        drawSettings();
        
        while(1) {
            key = input();
            if (key == gamepad.down) {
                upFlag = false;
            }
            if (key == gamepad.up){
                upFlag = true;
            }
            if (key == gamepad.bck){
                backFlag = true;
                goto exit_loop;
            }
            if (key == gamepad.con){
                goto exit_loop;
            }
            drawSettings();
        } exit_loop:
        if (backFlag) { 
            backFlag = false;
            return; 
        }
        if (upFlag) { difficulty(); }
        else {controls(); }
    }
}

static void drawSettings() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    draw_set(&frame_buffer_info, setting,120,60);
    draw_set(&frame_buffer_info, pback,140,235);
    
    if (set) {
        draw_set(&frame_buffer_info, num_thr,317,58);
    }
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,90,68);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,90,147);
    }
    draw_fin(&frame_buffer_info);
}

static void difficulty() {
    printf("Difficulty: 3\n");
}

static void controls() {
    printf("Controls\n");
}
//-------------------------------------------------------------------
static void newgame() {
    reset();
    drawGame();  
    while(1) {
        if (collision()) {
            if (bkTitle) {
                break;
            } 
            else {
                wait(1.5);
                reset();
                drawGame();
            }  
        }    
        else {
            gameInput = input();
            obstacles();
            jump();
            drawGame();
        }   
    }
}
//--------------------------------------------------------------------

static void drawGame() {      
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0);
    
    for(int i=0; i<deteru;i++) {
        if (i==9) {
            draw_set(&frame_buffer_info,goal,spikes[i].x,220);
        } else {
            draw_set(&frame_buffer_info,ob,spikes[i].x,238);
            //printf("spike %d position: %d\n", i, spikes[i].x);   
        }
    }
    
    draw_set(&frame_buffer_info,player,p1.x,p1.y);
    draw_fin(&frame_buffer_info);
}

static void reset() {
    //long deru = 500;
    game_timer.reset();
    game_timer.start();
    deteru = 0;
    goalOut = false;
    vel = 20;
    fvel = 2;
    jumpProg = 0;
    fallProg = 10;
    jumpFlag = false;
    bkTitle = false;
    gameInput = input();
    gameInput = NULL;
    
    //printf("Game reset...\n");
    
    for (int i=0; i<10; i++) {
        spikes[i].x = 480;
        spikes[i].y = 236;
        spikes[i].w = 35;
        spikes[i].h = 35;
        
        //printf("spike[%d] position: %d\n", j,spikes[j].x);
    }
    
    p1.x = 60;
    p1.y = 238;
    p1.w = 36;
    p1.h = 36;
       
    
    /*for (int i=0; i<10; i++) {
        times[i] = deru;
        deru += 1500;
        //printf("time allotted for times[%d]: %d\n",l,deru);    
    }*/
    
}

static bool collision() {
    //Let's examine the x axis first:
    //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
    for (int i=0; i<deteru;i++) {
        if( (p1.x >= spikes[i].x && p1.x <= (spikes[i].x + spikes[i].w)) ||
          ((p1.x + p1.w) >= spikes[i].x && (p1.x + p1.w) <= (spikes[i].x + spikes[i].w)) ){
        //Now we look at the y axis:
            if( (p1.y >= spikes[i].y && p1.y <= (spikes[i].y + spikes[i].h)) ||
                ((p1.y + p1.h) >= spikes[i].y && (p1.y + p1.h) <= (spikes[i].y + spikes[i].h)) ){
            //The sprites appear to overlap.
            if (goalOut) {
                goalReached();
                bkTitle = true;
            }
            return true;
            }
        }
        else if (game_timer.read_ms() > (times[9]+700)) {
            goalReached();
            bkTitle = true;
            return true;
        }
    } 
    
    //The sprites do not overlap:
    return false;
}

static void jump() {
    if (gameInput == gamepad.con) {
        //printf("starting jump\n");
        jumpFlag = true;
        gameInput = NULL;
    }
    
    if (jumpFlag) {                             // jump started
        if (jumpProg == max_jump) {             // start of fall
            if(fallProg == 1) {                 // end of fall              
                //printf("end of fall\n");
                p1.y = 238;
                fallProg--;
            }
            else {
                p1.y += fvel;                   // falling
                fvel += (gravity * fallProg);
                fallProg--;
            }
        }
        else {
            if (jumpProg == 9) {                // end of jump
                //printf("end of jump\n");
                p1.y = 115;
                jumpProg++;
            }
            else {
                jumpProg++;                     // jumping
                p1.y -= vel;
                vel -= (gravity * jumpProg);
            }
        }
    }
    
    if ((fallProg == 0) && (jumpProg == 10)) { // reset jump
        //printf("jump was reset\n");
        jumpFlag = false;
        fallProg = 10;
        jumpProg = 0;
        vel = 20;
        fvel = 2;
    }
    
    //printf("player's y pos: %d", p1.y);
}
        

static void obstacles() {
    long timeCheck = game_timer.read_ms();
    
    if(deteru != 10) {
        if (timeCheck >= times[deteru]) {
            //printf("Next obstacle!\n");
            deteru++;
        }
    }
    
    if (deteru == 10) {
        goalOut = true;
    }
    
    for (int i=0; i < deteru; i++) {
        if(spikes[i].x < -39) {continue;}
        spikes[i].x -= 8;
    }
}

static bool goalReached(){
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, black,0,0);
    draw_set(&frame_buffer_info, goaaalll,160,60);
    draw_set(&frame_buffer_info, pback,140,235);
    draw_fin(&frame_buffer_info);
    printf("Goal!\n");
    
    while(1) {
        key = input();
        if (key == gamepad.bck){
            goto exit_loop;
        }
        
    } exit_loop:
    return true;
}
