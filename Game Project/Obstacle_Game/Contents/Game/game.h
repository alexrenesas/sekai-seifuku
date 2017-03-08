#ifndef GAME
#define GAME

#include "mbed.h"
#include "lcd.h"
#include "bt.h"
#include "sd.h"

void game();
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
static bool loopCheck();


//extern bool noDataF;
extern bool backFlag;
extern bool goalOut;
extern bool upFlag;
extern bool bkTitle;
extern char key;
extern bool set;
extern int times[];
extern int deteru;
#endif