#include <conio.h>
#include "dglib2.h"

#include "stages.h"

int FPS = 1000/60;

unsigned long starttime; //game start time

char_far gvram; //window

int main() {
	starttime = timeGetTime();
	do {
		if(timeGetTime() - starttime < FPS) continue;
		ML();
	}while(!getch3(0x1b)) //esc to game end
}

