/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../Tamagotchi/Game_func.h"
#include "../RIT/RIT.h"
#include "../music/music.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void set_stop(int fermo);
void set_life(int l);
void set_tim1(int x);
void set_tim2(int x);
void set_animazione(int x);
int get_animazione(void);
void set_volume(int x);


static int stop = 0;
static int life = 0;
static int flag = 0;
static int tim1 = 0;
static int tim2 = 0;
static int volume = 2;
static int animazione = 0;




uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};




void TIMER0_IRQHandler (void)
{	
	life++;
	Conversion_Time_Life_Tamagotchi(life);		//Ogni secondo aumento e stampo la vita che cresce
	
	if(stop!=1) {															//Ho creato un semaforo  in qunto l'ultimo interupt
		if(flag  == 0){													//Non si riesce a eliminare una volta che il tamagotchi muore
				LCD_Update_Tamagotchi(flag);				//Il semaforo impedisce di enrare se il tamagotchi muore
				flag = 1;
		}else{
				LCD_Update_Tamagotchi(flag);
				flag = 0;
		}
	}
	
	tim1++;
	tim2++;
	
	if(tim1 == 5){
		LCD_Decrease_Happines();
		tim1 = 0;
	}
	if(tim2 == 5){
		LCD_Decrease_Satiety();
	  tim2 = 0;
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	disable_timer(1);
	disable_timer(2);
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	currentValue = currentValue * volume;
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;


  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	
	volatile static int count = 0;
	volatile static int stop = 0;
	
	if(animazione == 1)
		Animazione_meal();
	
	else if(animazione == 2)
		Animazione_snack();
	
	else if(animazione == 3){
		stop++;
		count++;
		disable_RIT();
		if(count == 5){
			Animazione_touch();
			count = 0;
		}
	}
	
	
	if(stop == 40){
		stop = 0;
		disable_timer(3);
		animazione = 0;
		enable_RIT();
	}
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

void set_stop(int fermo){
	stop = fermo;
}

void set_life(int l){
	life = l;
}

void set_tim1(int x){
	tim1 = x;
}

void set_tim2(int x){
	tim2 = x;
}

void set_animazione(int x){
	animazione = x;
}

int get_animazione(void){
		return animazione;
}
void set_volume(int x){
	volume = x;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
