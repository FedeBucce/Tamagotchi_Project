/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../timer/timer.h"
#include "../Tamagotchi/Game_func.h"
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */

//const int freqs[8]={4240,3779,3367,3175,2834,2525,2249,2120};
/* 
131Hz		k=4240 C3
147Hz		k=3779
165Hz		k=3367
175Hz		k=3175
196Hz		k=2834		
220Hz		k=2525
247Hz		k=2249
262Hz		k=2120 C4
*/


/*
262Hz	k=2120		c4
294Hz	k=1890		
330Hz	k=1684		
349Hz	k=1592		
392Hz	k=1417		
440Hz	k=1263		
494Hz	k=1125		
523Hz	k=1062		c5

*/

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(AD_current != AD_last){
		
		if(AD_current < 0xFFF/4){
			set_volume(0);
			draw_speaker_volume_0(10,10,White);
			draw_speaker_volume_1(10,10,White);
			draw_speaker_volume_2(10,10,White);
			draw_speaker_volume_3(10,10,White);
			draw_speaker_volume_0(10,10,Black);
		}else if(AD_current < 0xFFF/2){
			set_volume(1);
			draw_speaker_volume_0(10,10,White);
			draw_speaker_volume_1(10,10,White);
			draw_speaker_volume_2(10,10,White);
			draw_speaker_volume_3(10,10,White);
			draw_speaker_volume_1(10,10,Black);
		}else if(AD_current < 0xFFF*3/4){
			set_volume(2);
			draw_speaker_volume_0(10,10,White);
			draw_speaker_volume_1(10,10,White);
			draw_speaker_volume_2(10,10,White);
			draw_speaker_volume_3(10,10,White);
			draw_speaker_volume_1(10,10,Black);
			draw_speaker_volume_2(10,10,Black);
		}else if(AD_current < 0xFFF){
			set_volume(3);
			draw_speaker_volume_0(10,10,White);
			draw_speaker_volume_1(10,10,White);
			draw_speaker_volume_2(10,10,White);
			draw_speaker_volume_3(10,10,White);
			draw_speaker_volume_1(10,10,Black);
			draw_speaker_volume_2(10,10,Black);
			draw_speaker_volume_3(10,10,Black);
		}
		
		
		AD_last = AD_current;
  }
	
}
