#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "windows.h"
#include "stdio.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.14159265358979323846f
#define TWO_PI 6.28318530717958647692f
#define HALF_PI 1.57079632679489661923f
#define QUARTER_PI 0.78539816339744830961f
#define INV_PI 0.31830988618379067154f
#define INV_TWO_PI 0.15915494309189533576f
#define HAVE_M_PI


// New useful types
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long UID;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x )\
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Configuration -----------
//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 1024
//#define SCREEN_SIZE 1
//#define WIN_FULLSCREEN false
//#define WIN_RESIZABLE true
//#define WIN_BORDERLESS false
//#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Deku Engine"

#endif __GLOBALS_H__