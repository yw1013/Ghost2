#include "mylib.h"
#include "font.h"

u16 *videoBuffer = (u16*) 0x6000000;


/* drawimage4
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage4(int r, int c, int width, int height, const u16* image){
	for (int i = 0; i < height; i++){
		DMA[3].src = &image[OFFSET(i, 0, width / 2)];
		DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240)/2;
		DMA[3].cnt = (width/2) | DMA_ON;
	}
}


void setPixel4(int r, int c, u8 index) {
	int pixel = OFFSET(r, c, 240);
	int pixelShort = pixel/2;
	if (c & 1) {
		videoBuffer[pixelShort] = (videoBuffer[pixelShort] & 0x00FF) | (index << 8);
	} else {
		videoBuffer[pixelShort] = (videoBuffer[pixelShort] & 0xFF00) | index;
	}
}


void drawRect4(int r, int c, int width, int height, u8 index) {
	volatile u16 color = index | (index << 8);
	for(int i = 0; i < height; i++) {
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240)/2;	
		DMA[3].cnt = (width/2) | DMA_ON | DMA_SOURCE_FIXED;
	}
}


void fillScreen4(u8 index) {
	volatile u16 color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;
}


void flipPage() {
	if(REG_DISPCNT & BUFFERFLAG) {
		REG_DISPCNT &= ~BUFFERFLAG;
		videoBuffer = BUFFER1;
	} else {
		REG_DISPCNT |= BUFFERFLAG;
		videoBuffer = BUFFER0;
	}
}


void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


void setPalette(const u16 *p, int size){
	for(int i = 0; i < size; i++){
		DMA[3].src = &p[i];
		DMA[3].dst = &PALETTE[i];
		DMA[3].cnt = size | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void drawChar4(int r, int c, char ch, u8 index){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j<  6; j++)	{
			if(fontdata_6x8[OFFSET(i, j, 6) + ch*48]){
				setPixel4(r + i, c + j, index);
			}
		}
	}
}


void drawString4(int r, int c, char *str, u8 index){
	while(*str){
		drawChar4(r, c, *str, index);
		str++;
		c += 6;
	}
}


