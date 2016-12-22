#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "font.h"
#include "screenImage.h"
#include "movingObj.h"

typedef struct{
	int row;
	int col;
	int speed;
} Character;

Character player = {144, 113, 0};
Character g1 = {19, 0, 1};
Character g10 = {19, 70, 1};
Character g11 = {19, 140, 1};

Character g2 = {38, 220, 1};
Character g20 = {38, 130, 1};
Character g21 = {38, 40, 1};

Character g3 = {57, 103, 1};
Character g30 = {57, 49, 1};

Character g4 = {108, 43, 1};
Character g40 = {108, 121, 1};

Character g5 = {89, 130, 1};
Character g50 = {89, 30, 1};

Character g6 = {128, 200, 1};
Character g60 = {128, 100, 1};

void drawPlayer();
int movePlayer();
void moveGhost();
void delay();

enum STATE {START, PLAY, OVER, WIN};
enum STATE state = START;

int LIVES = 3;

int main(){

	REG_DISPCNT = MODE_4 | BG2_EN | BUFFERFLAG;

	int state = START;
	while(1){
		switch(state){
		case START:
			for (int i = 0; i < SCREENIMAGE_PALETTE_SIZE; i++) {
				PALETTE[i] = screenImage_palette[i];
			}
			drawImage4(0, 0, START_WIDTH, START_HEIGHT, start);

			player.row = 144;
			player.col = 113;
			player.speed = 1;


			g1.row = 19;
			g1.col = 0;
			g1.speed = 2;

			g10.row = 19;
			g10.col = 70;
			g10.speed = 2;

			g11.row = 19;
			g11.col = 140;
			g11.speed = 2;

			g2.row = 38;
			g2.col = 220;
			g2.speed = 1;

			g20.row = 38;
			g20.col = 130;
			g20.speed = 1;

			g21.row = 38;
			g21.col = 40;
			g21.speed = 1;

			g3.row = 57;
			g3.col = 103;
			g3.speed = 1;

			g30.row = 57;
			g30.col = 49;
			g30.speed = 1;

			g4.row = 108;
			g4.col = 43;
			g4.speed = 2;

			g40.row = 108;
			g40.col = 121;
			g40.speed = 2;

			g5.row = 89;
			g5.col = 130;
			g5.speed = 1;

			g50.row = 89;
			g50.col = 30;
			g50.speed = 1;

			g6.row = 128;
			g6.col = 200;
			g6.speed = 1;

			g60.row = 128;
			g60.col = 100;
			g60.speed = 1;

			LIVES = 3;

			if(KEY_DOWN_NOW(BUTTON_START)){
				state = PLAY;
			}
			break;

		case PLAY:
			for (int i = 0; i < MOVINGOBJ_PALETTE_SIZE; i++) {
				PALETTE[i] = movingObj_palette[i];
			}
			drawImage4(0,0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background);
			if(KEY_DOWN_NOW(BUTTON_SELECT)){
				state = START;
			}
			drawPlayer();
			state = movePlayer();
			break;

		case OVER:
			for (int i = 0; i < SCREENIMAGE_PALETTE_SIZE; i++) {
				PALETTE[i] = screenImage_palette[i];
			}
			drawImage4(0,0, OVER_WIDTH, OVER_HEIGHT, over);
			if(KEY_DOWN_NOW(BUTTON_SELECT)){
				state = START;
			}
			break;

		case WIN:
			for (int i = 0; i < SCREENIMAGE_PALETTE_SIZE; i++) {
				PALETTE[i] = screenImage_palette[i];
			}
			drawImage4(0,0, WIN_WIDTH, WIN_HEIGHT, win);
			if(KEY_DOWN_NOW(BUTTON_SELECT)){
				state = START;
			}
			break;
		}
		waitForVblank();
		flipPage();
	}
	return 0;		
}

void drawPlayer(){
	if(player.col < 0){
		player.col = 0;
	} else if(player.col > 225){
		player.col = 225;
	}
	if(player.row < 0){
		player.row = 0;
	} else if(player.row > 145){
		player.row = 145;
	}
	drawImage4(player.row, player.col, FROG1_WIDTH, FROG1_HEIGHT, frog1);
	flipPage();

	// drawImage4(player.row, player.col, FROG2_WIDTH, FROG2_HEIGHT, frog2);
	// flipPage();

	// drawImage4(player.row, player.col, FROG3_WIDTH, FROG3_HEIGHT, frog3);
	// flipPage();
	// delay(1);
	
	// drawImage4(player.row, player.col, FROG4_WIDTH, FROG4_HEIGHT, frog4);
	// flipPage();
	
	// drawImage4(player.row, player.col, FROG1_WIDTH, FROG1_HEIGHT, frog1);
	// flipPage();

}

int movePlayer(){
	drawPlayer();
	while(1){
		drawImage4(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background);

		char liveStr[15];
		drawString4(147, 5, "LIVES: ", PALETTE[0]);
		sprintf(liveStr, "%d", LIVES);
		drawString4(147, 45, liveStr, PALETTE[0]);

		if(KEY_DOWN_NOW(BUTTON_SELECT)){
			return START;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT)){
			player.col -= player.speed;
			drawPlayer();
			flipPage();
		}	
		if(KEY_DOWN_NOW(BUTTON_RIGHT)){
			player.col += player.speed;
			drawPlayer();
			flipPage();
		}
		if(KEY_DOWN_NOW(BUTTON_UP)){
			player.row -= player.speed;
			drawImage4(player.row, player.col, FROG2_WIDTH, FROG2_HEIGHT, frog2);
			flipPage();

			drawImage4(player.row, player.col, FROG3_WIDTH, FROG3_HEIGHT, frog3);
			flipPage();
			delay(1);
	
			drawImage4(player.row, player.col, FROG4_WIDTH, FROG4_HEIGHT, frog4);
			flipPage();
			
			drawImage4(player.row, player.col, FROG1_WIDTH, FROG1_HEIGHT, frog1);
			flipPage();
			//flipPage();
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)){
			player.row += player.speed;
			drawPlayer();
			flipPage();
		}
		if(player.row <=2){
			return WIN;
		}

		if
		((player.row + 14 >= g1.row && player.row <= g1.row + 14 && player.col + 14 >= g1.col && player.col <= g1.col + 14) ||
		(player.row + 14 >= g10.row && player.row <= g10.row + 14 && player.col + 14 >= g10.col && player.col <= g10.col + 14) ||
		(player.row + 14 >= g11.row && player.row <= g11.row + 14 && player.col + 14 >= g11.col && player.col <= g11.col + 14) ||
		(player.row + 14 >= g2.row && player.row <= g2.row + 14 && player.col + 14 >= g2.col && player.col <= g2.col + 14) ||
		(player.row + 14 >= g20.row && player.row <= g20.row + 14 && player.col + 14 >= g20.col && player.col <= g20.col + 14) ||
		(player.row + 14 >= g21.row && player.row <= g21.row + 14 && player.col + 14 >= g21.col && player.col <= g21.col + 14) ||
		(player.row + 14 >= g3.row && player.row <= g3.row + 14 && player.col + 14 >= g3.col && player.col <= g3.col + 14) ||
		(player.row + 14 >= g30.row && player.row <= g30.row + 14 && player.col + 14 >= g30.col && player.col <= g30.col + 14) ||
		(player.row + 14 >= g4.row && player.row <= g4.row + 14 && player.col + 14 >= g4.col && player.col <= g4.col + 14) ||
		(player.row + 14 >= g40.row && player.row <= g40.row + 14 && player.col + 14 >= g40.col && player.col <= g40.col + 14) ||
		(player.row + 14 >= g5.row && player.row <= g5.row + 14 && player.col + 14 >= g5.col && player.col <= g5.col + 14) ||
		(player.row + 14 >= g50.row && player.row <= g50.row + 14 && player.col + 14 >= g50.col && player.col <= g50.col + 14) ||
		(player.row + 14 >= g6.row && player.row <= g6.row + 14 && player.col + 14 >= g6.col && player.col <= g6.col + 14) ||
		(player.row + 14 >= g60.row && player.row <= g60.row + 14 && player.col + 14 >= g60.col && player.col <= g60.col + 14)){
			LIVES -= 1;
			if(LIVES == 0){
				return OVER;
			}
			drawImage4(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background);
			drawString4(76, 90, "BE CAREFUL!", PALETTE[40]);
			player.row = 144;
			player.col = 113;
		 	drawPlayer();
		 	delay(80);
		} 


		moveGhost();

		g1.col %= 240;
		g10.col %= 240;
		g11.col %= 240;
		g2.col %= 240;
		g20.col %= 240;
		g21.col %= 240;
		g3.col %= 240;
		g30.col %= 240;
		g4.col %= 240;
		g40.col %= 240;
		g5.col %= 240;
		g50.col %= 240;
		g6.col %= 240;
		g60.col %= 240;
	}
	return 0;
}

void moveGhost(){

	g1.col += g1.speed;
	g10.col += g10.speed;
	g11.col += g11.speed;
	g2.col += g2.speed;
	g20.col += g20.speed;
	g21.col += g21.speed;
	g3.col += g3.speed;
	g30.col += g30.speed;
	g4.col += g4.speed;
	g40.col += g40.speed;
	g5.col += g5.speed;
	g50.col += g50.speed;
	g6.col += g6.speed;
	g60.col += g60.speed;
	delay(1);
	drawImage4(player.row, player.col, FROG1_WIDTH, FROG1_HEIGHT, frog1);

	drawImage4(g1.row, g1.col, GHOST1_WIDTH, GHOST1_HEIGHT, ghost1);
	drawImage4(g10.row, g10.col, GHOST1_WIDTH, GHOST1_HEIGHT, ghost1);
	drawImage4(g11.row, g11.col, GHOST1_WIDTH, GHOST1_HEIGHT, ghost1);

	drawImage4(g2.row, g2.col, GHOST2L_WIDTH, GHOST2L_HEIGHT, ghost2L);
	drawImage4(g20.row, g20.col, GHOST2L_WIDTH, GHOST2L_HEIGHT, ghost2L);
	drawImage4(g21.row, g21.col, GHOST2L_WIDTH, GHOST2L_HEIGHT, ghost2L);

	drawImage4(g3.row, g3.col, GHOSTB_WIDTH, GHOSTB_HEIGHT, ghostB);
	drawImage4(g30.row, g30.col, GHOSTB_WIDTH, GHOSTB_HEIGHT, ghostB);

	drawImage4(g4.row, g4.col, GHOSTO_WIDTH, GHOSTO_HEIGHT, ghostO);
	drawImage4(g40.row, g40.col, GHOSTO_WIDTH, GHOSTO_HEIGHT, ghostO);

	drawImage4(g5.row, g5.col, GHOSTPL_WIDTH, GHOSTPL_HEIGHT, ghostPL);
	drawImage4(g50.row, g50.col, GHOSTPL_WIDTH, GHOSTPL_HEIGHT, ghostPL);

	drawImage4(g6.row, g6.col, GHOSTRL_WIDTH, GHOSTRL_HEIGHT, ghostRL);
	drawImage4(g60.row, g60.col, GHOSTRL_WIDTH, GHOSTRL_HEIGHT, ghostRL);

	flipPage();
}

void delay(int n) {
	volatile int x = 0;
	for (int i = 0; i < n*4000; i++) {
		x++;
	} 	
}