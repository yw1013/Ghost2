/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 screenImage start.png win.png over.png 
 * Time-stamp: Sunday 11/08/2015, 22:31:15
 * 
 * Image Information
 * -----------------
 * start.png 240@160
 * win.png 240@160
 * over.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef SCREENIMAGE_H
#define SCREENIMAGE_H

extern const unsigned short screenImage_palette[255];
#define SCREENIMAGE_PALETTE_SIZE 255

extern const unsigned short start[19200];
#define START_SIZE 19200
#define START_WIDTH 240
#define START_HEIGHT 160

extern const unsigned short win[19200];
#define WIN_SIZE 19200
#define WIN_WIDTH 240
#define WIN_HEIGHT 160

extern const unsigned short over[19200];
#define OVER_SIZE 19200
#define OVER_WIDTH 240
#define OVER_HEIGHT 160

#endif

