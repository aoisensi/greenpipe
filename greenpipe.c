#include <conio.h>
#include "dglib2.h"

unsigned long frame; //bad code
char_far gvram; //window
char_far dvram; //double buffer

#include "stages.h"
#include "math3.h"

int FPS = 1000/15;

unsigned long starttime; //game start time

int main() {
	starttime = timeGetTime();
	dg_setscreen(0, 0, windowsize.x, windowsize.y, 0, "Green Pipe");
	dvram = dg_createbmp(windowsize.x, windowsize.y);
	do {
		ML();
		if(timeGetTime() - starttime < FPS) continue;
		dg_gcls(dvram, RGB(0,0,0));

		render_qube_test();
		dg_drawbmp(gvram, 0, 0, windowsize.x, windowsize.y, dvram); //write double buffer
		frame++;
	}while(!getch3(0x1b)); //esc to game end
}

