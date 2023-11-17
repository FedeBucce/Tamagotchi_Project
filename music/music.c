#include "music.h"
#include "LPC17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "../Tamagotchi/Game_func.h"
#include "../joystick/joystick.h"
#include "../RIT/RIT.h"
#include "../adc/adc.h"
#include "../timer/timer.h"

void playNote(NOTE note)
{
	if(note.freq != pause)
	{
		reset_timer(2);
		init_timer(2, note.freq);
		enable_timer(2);
	}
	reset_timer(1);
	init_timer(1, note.duration);
	enable_timer(1);
}

BOOL isNotePlaying(void)
{
	return ((LPC_TIM2->TCR != 0) || (LPC_TIM1->TCR != 0));
}

