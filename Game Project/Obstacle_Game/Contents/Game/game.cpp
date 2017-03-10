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
} s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,
  s11,s12,s13,s14,s15,s16,s17,s18,
  s19,s20,s21,s22;

struct myplayer {
    int x;
    float y;
    int w,h;
} p1;

// spike courses, their timings, and jump levels
spike spikes[22] = {
    s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,
    s11,s12,s13,s14,s15,s16,s17,s18,
    s19,s20,s21,s22
};

int times1[10] = {
    1500,3000,4500,6000,7000,9000,9800,10800,
    12000,13500
};

int times2[13] = {
    1500,3000,3080,4000,6000,7000,7080,7700,
    9000,9700,10400,11100,13000
};

int times3[13] = {
    1500,2000,3000,3500,4000,5000,6000,6500,7000,
    7500,9000,10000,12000
};

int times4[22] = {
    1000,1500,2000,3000,3500,3560,4000,4055,5000,
    5500,6000,8000,8060,8120,8600,9000,9300,9800,
    10500,10560,10620,12000
};

int times5[18] = {
    1000,2000,2500,3000,5000,5050,5400,6000,6050,
    6300,6350,8000,9000,9400,9800,10200,10250,11000
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

int *levels[5] = {times1,times2,times3,times4,times5};
int *jumpLev[3] = {jumps1, jumps3, jumps5};

// Game flags and parameters
int deteru;
char key;
bool jumpFlag = false;
bool pauseFlag = false;
Timer game_timer;
bool upFlag = true;
bool backFlag = false;
bool goalOut = false;
bool contFlag = false;
bool bkTitle = true;
int jump_time;
int jumpDiff;
char gameInput;
int obSpeed;
int d;
int diffSpeed;
int gameDiff;
int detmax;
int noObs;
int levSel;
int jumpSel;
int lastNum;
int lastTime;

// Function declarations
//static void nodat();
static void title();
static void drawTitle();
static void settings();
static void drawSettings();
static void difficulty();
static void controls();
static void newgame();
static void drawGame();
static void reset();
static void obstacles();
static bool goalReached();
static void jump();
static bool collision();
static void pauseFunc();

//******************************************************************************


void game() {
    gamepad.up      = 'w';
    gamepad.down    = 's';
    gamepad.con     = 'j';
    gamepad.bck     = 'b';
    gamepad.lft     = 'a';
    gamepad.rgt     = 'd';
    gamepad.pse     = 'p';
    
    gameDiff = 3;
    
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
    contFlag = false;
    drawSettings();
    while(1) {
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
        
        if (upFlag) {
            difficulty(); 
        }
        else {
            contFlag = true;
            controls(); 
        }
    }
}


static void drawSettings() {
    clear(&frame_buffer_info, 0,0,480,272);
    draw_set(&frame_buffer_info, haikei,0,0,1);
    draw_set(&frame_buffer_info, setting,120,60,1);
    draw_set(&frame_buffer_info, pback,140,235,1);
    
    if(d == 0) {
        draw_set(&frame_buffer_info, jumpcon,290,148,1);
    }
           
    
    if(upFlag == true) {
        draw_set(&frame_buffer_info, arrow,90,68,1);
    }
    else if(upFlag == false) {
        draw_set(&frame_buffer_info, arrow,90,147,1);
    }
    if(contFlag) {
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
        if (d == 3)d = 0;
    }
    
    switch(gameDiff) {
        case 1: 
            draw_set(&frame_buffer_info, num_one,317,58,1);
            break;
        case 2: 
            draw_set(&frame_buffer_info, num_two,317,58,1);
            break;
        case 3: 
            draw_set(&frame_buffer_info, num_thr,317,58,1);
            break;
        case 4: 
            draw_set(&frame_buffer_info, num_fou,317,58,1);
            break;
        case 5: 
            draw_set(&frame_buffer_info, num_fiv,317,58,1);
            break;
    }
    
    draw_fin(&frame_buffer_info);
}

static void difficulty() {     
    while(1) {
        key = input();
        
        if (key == gamepad.lft) {
            if (gameDiff != 1) {
                gameDiff -= 1;
            }
        }
        if (key == gamepad.rgt){
            if (gameDiff != 5) {
                gameDiff += 1;
            }
        }
        if (key == gamepad.con){
            goto exit_loop;
        }
        drawSettings();
    } exit_loop: 
    return;      
}

static void controls() {
    key = NULL;
    drawSettings();
    
    //printf("assigning jump...\n");
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.con = key;
            key = NULL;
            break;
        }
    }
    drawSettings();
    //printf("assigning pause...\n");
    
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.pse = key;
            key = NULL;
            break;
        }
    }
    drawSettings();
    //printf("assigning back...\n");
    
    while(1) {
        key = input();
        if (key != NULL) {
            gamepad.bck = key;
            key = NULL;
            break;
        }
    }
    
    contFlag = false;
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
        if (i==(lastNum-1)) {
            draw_set(&frame_buffer_info,goal,spikes[i].x,220,1);
        } else {
            draw_set(&frame_buffer_info,ob,spikes[i].x,238,1);
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
    pauseFlag = false;
    
    //printf("Game reset...\n");
    
    //printf("gameDiff: %d\n", gameDiff);
    switch(gameDiff) {
        case 1:
            noObs = 10;
            jumpDiff = 40;
            levSel = 0;
            jumpSel = 0;
            diffSpeed = 5;
            lastNum = 10;
            lastTime = 1000;
            break;
        case 2:
            noObs = 13;
            jumpDiff = 40;
            levSel = 1;
            jumpSel = 0;
            diffSpeed = 5;
            lastNum = 13;
            lastTime = 1000;
            break;
        case 3:
            noObs = 13;
            jumpDiff = 30;
            levSel = 2;
            jumpSel = 1;
            diffSpeed = 6;
            lastNum = 13;
            lastTime = 900;
            break;
        case 4:
            noObs = 22;
            jumpDiff = 30;
            levSel = 3;
            jumpSel = 1;
            diffSpeed = 8;
            lastNum = 22;
            lastTime = 700;
            break;
        case 5:
            noObs = 18;
            jumpDiff = 20;
            levSel = 4;
            jumpSel = 2;
            diffSpeed = 8; 
            lastNum = 18;
            lastTime = 700;
            break;
    }
    
    for (int i=0; i<noObs; i++) {
        spikes[i].x = 480;
        spikes[i].y = 236;
        spikes[i].w = 35;
        spikes[i].h = 35;
    }
    
    p1.x = 60;
    p1.y = 238;
    p1.w = 36;
    p1.h = 36;    
    
    
    /*
    printf("noObs: %d\n", noObs);
    printf("jumpDiff: %d\n", jumpDiff);
    printf("levSel: %d\n", levSel);
    printf("jumpSel: %d\n", jumpSel);
    printf("diffSpeed: %d\n", diffSpeed);
    printf("lastNum: %d\n", lastNum); */
}

static bool collision() {
    for (int i=0; i<deteru;i++) {
        if( (p1.x >= spikes[i].x && p1.x <= (spikes[i].x + spikes[i].w)) ||
          ((p1.x + p1.w) >= spikes[i].x && (p1.x + p1.w) <= (spikes[i].x + spikes[i].w)) ){
            if( (p1.y >= spikes[i].y && p1.y <= (spikes[i].y + spikes[i].h)) ||
                ((p1.y + p1.h) >= spikes[i].y && (p1.y + p1.h) <= (spikes[i].y + spikes[i].h)) ){
            if (goalOut) {
                goalReached();
                bkTitle = true;
            }
            return true;
            }
        }
        else if (game_timer.read_ms() > ((levels[levSel][lastNum-1])+lastTime)) {
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
            if (i==(lastNum-1)) {
                draw_set(&frame_buffer_info,goal,spikes[i].x,220,0.6);
            } else {
                draw_set(&frame_buffer_info,ob,spikes[i].x,238,0.6);
                //printf("spike %d position: %d\n", i, spikes[i].x);   
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
            p1.y -= jumpLev[jumpSel][jump_time];
            jump_time++;
        }
        else {
            p1.y += jumpLev[jumpSel][jump_time];
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
    
    if(deteru != lastNum) {
        if (timeCheck >= levels[levSel][deteru]) {
            //printf("Next obstacle!\n");
            deteru++;
        }
    }
    
    if (deteru == lastNum) {
        goalOut = true;
    }
    
    for (int i=0; i < deteru; i++) {
        if(spikes[i].x < -39) {continue;}
        spikes[i].x -= diffSpeed;
        //printf("spike %d position: %d\n", i, spikes[i].x);   
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
