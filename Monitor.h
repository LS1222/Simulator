#ifndef __MONITOR_H__
#define __MONITOR_H__

/*===================================
|           INCLUDES                |
====================================*/
#include "Global.h"

/*===================================
|           DEFINES                 |
====================================*/
#define MONITOR_WIDTH  256
#define MONITOR_HEIGHT 256
#define PIXEL_DEFAULT  0
#define ROW_TOP        0
#define ROW_BOTTOM     MONITOR_HEIGHT - 1
#define COL_LEFT       0
#define COL_RIGHT      MONITOR_WIDTH - 1

/*===================================
|           TYPEDEFS                |
====================================*/
typedef char unsigned   pixel;
typedef pixel           monitor_buffer[MONITOR_WIDTH][MONITOR_HEIGHT];
typedef monitor_buffer* SimulatorMonitor;

#endif // __MONITOR_H__
