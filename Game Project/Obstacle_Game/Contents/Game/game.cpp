#include "game.h"

//****************************** VARIABLES *************************************
// controller buttons
struct inp {
    char up;
    char down;
    char con;
    char bck;
    char lft;
    char rgt;
    char pse;
} gamepad;

// stores each number
const graphics_image_t* numarray[10] = {
    num_zer, num_one, num_two, num_thr, num_fou, 
    num_fiv, num_six, num_sev, num_eig, num_nin
};

// Player and obstacle structs
struct spike {
    int x,y;
    int w,h;    
} s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;

struct myplayer {
    int x;
    float y;
    int w,h;
} p1;

// spike courses, their timings, and jump levels
spike spikes1[10] = {
    s1,s2,s3,s4,s5,s6,s7,s8,s9,s10
};

int times1[10] = {
    500,2000,2500,3000,4000,6000,
    7000,8700,9200,12000
};

int jumps1[40] = {
    12,12,12,11,11,10,10,9,9,8,8,7,7,6,5,4,3,2,0,0,
    0,0,2,3,4,5,6,7,7,8,8,9,9,10,10,11,11,12,12,12  
};

int jumps3[30] = {
    15,15,14,14,13,13,11,11,9,7,5,3,1,0,0,
    0,0,1,3,5,7,9,11,11,13,13,14,14,15,15
};

int jumps5[20] = {
    20,19,18,17,15,12,9,6,2,0,
    0,2,6,9,12,15,17,18,19,20
};

// Game flags and parameters
int deteru;
bool jumpFlag = false;
bool pauseFlag = false;
Timer game_timer;
bool upFlag = true;
bool backFlag = false;
bool set = true;
bool goalOut = false;
bool bkTitle = true;
int jump_time;
int jumpDiff;
char gameInput;
int obSpeed;
int d;

//******************************************************************************


void game() {
    gamepad.up      = 'w';
    gamepad.down    = 's';
    gamepad.con     = 'j';
    gamepad.bck     = 'b';
    gamepad.lft     = 'a';
    gamepad.rgt     = 'd';
    gamepad.pse     = 'p';
    
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
    draw_set(&frame_buffer_info, noblack,0,0,1);
    draw_set(&frame_buffer_info, nodata,150,110,1);
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
    draw_set(&frame_buffer_info, haikei,0,0,1);
    draw_set(&frame_buffer_info, titl,33,20,1);
    draw_set(&frame_buffer_info, menu,160,120,1);
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,123,128,1);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,120,199,1);
    }
    draw_fin(&frame_buffer_info);
}

static void settings() {
    upFlag = true;
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
        printf("Title > ");
        return; 
    }
    
    if (upFlag) { difficulty(); }
    else {controls(); }
}


static void drawSettings() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0,1);
    draw_set(&frame_buffer_info, setting,120,60,1);
    draw_set(&frame_buffer_info, pback,140,235,1);
    
    if (set) {
        //draw_set(&frame_buffer_info, num_thr,317,58,1);
    }
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,90,68,1);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,90,147,1);
    }
    draw_fin(&frame_buffer_info);
}

static void difficulty() {
    printf("Difficulty: 3\n");
}

static void controls() {
    key = NULL;
    drawCont();
    
    //printf("assigning jump...\n");
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.con = key;
            key = NULL;
            break;
        }
    }
    drawCont();
    //printf("assigning pause...\n");
    
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.pse = key;
            key = NULL;
            break;
        }
    }
    drawCont();
    //printf("assigning back...\n");
    
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.bck = key;
            key = NULL;
            break;
        }
    }
}

static void drawCont() {
    //printf("%d > ", d);
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0,1);
    draw_set(&frame_buffer_info, setting,120,60,1);
    draw_set(&frame_buffer_info, pback,140,235,1);
    draw_set(&frame_buffer_info, arrow,90,147,1);
    
    switch(d) {
        case 0: 
            draw_set(&frame_buffer_info, jumpcon,290,148,1);
            d++;
            break;
        case 1: 
            draw_set(&frame_buffer_info, pause,287,148,1);
            d++;
            break;
        case 2: 
            draw_set(&frame_buffer_info, back,285,148,1);
            d++;
            break;
    }
    
    draw_fin(&frame_buffer_info);
    //printf("%d\n", d);
    
    if (d == 3) d = 0;
}    
    
//****************************** NEW GAME **************************************
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
            pauseFunc();
            if (bkTitle) {
                break;
            } 
            obstacles();
            jump();
            drawGame();
        }   
    }
}
//******************************************************************************

static void drawGame() {      
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0,1);
    
    for(int i=0; i<deteru;i++) {
        if (i==9) {
            draw_set(&frame_buffer_info,goal,spikes1[i].x,220,1);
        } else {
            draw_set(&frame_buffer_info,ob,spikes1[i].x,238,1);
            //printf("spike %d position: %d\n", i, spikes1[i].x);   
        }
    }
    if(jumpFlag) {
        //printf("player y pos: %f\n", p1.y);
    }
    
    draw_set(&frame_buffer_info,player,p1.x,p1.y,1);
    draw_fin(&frame_buffer_info);
}

static void reset() {
    game_timer.reset();
    game_timer.start();
    deteru = 0;
    goalOut = false;
    jump_time = 0;
    jumpFlag = false;
    bkTitle = false;
    gameInput = input();
    gameInput = NULL;
    jumpDiff = 20;
    pauseFlag = false;
    
    //printf("Game reset...\n");
    
    for (int i=0; i<10; i++) {
        spikes1[i].x = 480;
        spikes1[i].y = 236;
        spikes1[i].w = 35;
        spikes1[i].h = 35;
    }
    
    p1.x = 60;
    p1.y = 238;
    p1.w = 36;
    p1.h = 36;
         
}

static bool collision() {
    for (int i=0; i<deteru;i++) {
        if( (p1.x >= spikes1[i].x && p1.x <= (spikes1[i].x + spikes1[i].w)) ||
          ((p1.x + p1.w) >= spikes1[i].x && (p1.x + p1.w) <= (spikes1[i].x + spikes1[i].w)) ){
            if( (p1.y >= spikes1[i].y && p1.y <= (spikes1[i].y + spikes1[i].h)) ||
                ((p1.y + p1.h) >= spikes1[i].y && (p1.y + p1.h) <= (spikes1[i].y + spikes1[i].h)) ){
            if (goalOut) {
                goalReached();
                bkTitle = true;
            }
            return true;
            }
        }
        else if (game_timer.read_ms() > (times1[9]+700)) {
            goalReached();
            bkTitle = true;
            return true;
        }
    } 
    return false;
}

static void pauseFunc() {
    if (gameInput == gamepad.pse) {
        pauseFlag = true;
        gameInput = NULL;
    }
    
    if (pauseFlag) {
        game_timer.stop();
        clear(&frame_buffer_info, 0,0,480,272);
        draw_set(&frame_buffer_info, haikei,0,0,0.6);
    
        for(int i=0; i<deteru;i++) {
            if (i==9) {
                draw_set(&frame_buffer_info,goal,spikes1[i].x,220,0.6);
            } else {
                draw_set(&frame_buffer_info,ob,spikes1[i].x,238,0.6);
                //printf("spike %d position: %d\n", i, spikes1[i].x);   
            }
        }
        
        draw_set(&frame_buffer_info,player,p1.x,p1.y,0.6);
        draw_set(&frame_buffer_info,black,0,0,0.9);
        draw_set(&frame_buffer_info,paused,170,115,0.9);
        draw_set(&frame_buffer_info, pback,140,235,0.9);
        draw_fin(&frame_buffer_info);
        
        while(1) {   
            key = input();
            
            if (key == gamepad.pse){
                pauseFlag = false;
                goto exit_loop;
            }
            if (key == gamepad.bck){
                bkTitle = true;
                goto exit_loop;
            }
        } exit_loop:
        
        game_timer.start();
    }       
}
    

static void jump() {
    if (gameInput == gamepad.con) {
        //printf("starting jump\n");
        jumpFlag = true;
        gameInput = NULL;
    }
    
    if (jumpFlag) {
        if (jump_time < (jumpDiff/2)) {
            p1.y -= jumps5[jump_time];
            jump_time++;
        }
        else {
            p1.y += jumps5[jump_time];
            jump_time++;
        }
    }
    
    if (jump_time == jumpDiff) {
        //printf("jump was reset\n");
        jumpFlag = false;
        jump_time = 0;
    }
}
        

static void obstacles() {
    long timeCheck = game_timer.read_ms();
    
    if(deteru != 10) {
        if (timeCheck >= times1[deteru]) {
            //printf("Next obstacle!\n");
            deteru++;
        }
    }
    
    if (deteru == 10) {
        goalOut = true;
    }
    
    for (int i=0; i < deteru; i++) {
        if(spikes1[i].x < -39) {continue;}
        spikes1[i].x -= 8;
    }
}

static bool goalReached(){
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, black,0,0,1);
    draw_set(&frame_buffer_info, goaaalll,160,60,1);
    draw_set(&frame_buffer_info, pback,140,235,1);
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
