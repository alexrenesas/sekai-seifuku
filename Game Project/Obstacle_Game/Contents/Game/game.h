#ifndef GAME
#define GAME

#include "mbed.h"
#include "lcd.h"
#include "bt.h"
#include "sd.h"

void game();
//void nodat();
static void title();
static void drawTitle();
static void settings();
static void drawSettings();
static void newgame();
static void drawGame();


//extern bool noDataF;
extern bool upFlag;
extern char key;
extern bool set;


#endif