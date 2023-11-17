/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "../Tamagotchi/Game_func.h"
#include "../music/music.h"
#include "../adc/adc.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void set_status(int stat);
int get_status(void);
void set_emit_s(int x);

					
					
static int status = -1;																	//variabile globale che mi tiene cosnto di quale operazione voglio fare con il joystick
static int select = 0;
static int right = 0;
static int left = 0;
static int emit_s = 0;
int freqs1[8]={2120,1890,1684,1592,1417,1263,1125,1062};


#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1


//SHORTENING UNDERTALE: TOO MANY REPETITIONS
NOTE song[] = 
{
	// 1
	{c3, time_semicroma},
	

};

NOTE song1[] = 
{
	// 1
	{d3, time_semicroma},
	{f3, time_semicroma},
	{d3, time_croma}
	
};

NOTE song2[] = 
{
	// 1
	{g3, time_semicroma},
	{f3, time_semicroma},
	{e3, time_croma},
	{d3, time_semicroma},
	{c3, time_semicroma}

};
NOTE song3[] = 
{
	// 1
	{c3, time_semicroma},
	{d3, time_semicroma},
	{e3, time_croma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	{a3, time_semicroma},
	{b3, time_croma},
	{c4, time_semicroma}
	

};

void RIT_IRQHandler (void)
{				
	static int currentNote = 0;
	static int ticks = 0;

	ADC_start_conversion();
	
	
	if(emit_s==0){
	
			if(get_fine()==1 ){
				set_fine(0);
				set_stop(1);										  //Dico al Tim0 che sta morendo il tamagotchi 
				set_status(3);										//Dico al RIT di mettere la variabile status a 3 cosi da poter utilizzare il tasto RESET
				disable_timer(0);  						
				disable_timer(3);
				End_Game();
			}
			if(status!=3){																					//se status è uguale a 3 vuol dire che l'unica opzione è il reset quindi disabilito il dx e sx del joystick
					if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){        
						//JOYSTICK PRESS LEFT
						left++;
						switch(left){
							case 1:         
								
								LCD_Empty_Rectangle(5,250 ,110,65,1,Red);
								LCD_Empty_Rectangle(125,250,110,65,1,Black);     
								status = 0; //satiety
								
							
								break;
							default:   
								break;
						}
					}else{
						left = 0;
					}       
											 
					if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
						//JOYSTICK PRESS RIGHT
						right++;     
						switch(right){
							case 1:
								LCD_Empty_Rectangle(125,250,110,65,1,Red);
								LCD_Empty_Rectangle(5,250,110,65,1,Black);
								status = 1; //happines         
										 
								break;
							default:
								break;             
						}
					}else{
						right = 0;
					}
			}
			
			if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){				//In bas
				//JOYSTICK PRESS SELECT
				select++;
				switch(select){
					case 1:
						if(status == 0)
						{
							
							set_emit_s(1);
							set_animazione(1);
							set_fine(1);												//Blocco l'animazione della end_game 
							disable_RIT();
							disable_timer(0);
							enable_timer(3);
							
							
						}
						else if(status == 1)
						{
							set_emit_s(1);
							set_animazione(2);
							set_fine(1);					//Blocco l'animazione della end_game 
							disable_RIT();
							disable_timer(0);
							enable_timer(3);
						}else if (status == 3){	//Reset_IRQn di tutti i valori 
							set_emit_s(5);
							status = -1;
							set_stop(0);
							set_fine(0);
							LCD_InitGame(Black);
							
							reset_timer(0);
							set_tim1(0);
							set_tim2(0);
							reset_RIT();
							enable_timer(0);                            
							enable_RIT();
						}
						break;
						
					default:
						break;
				}
				
			}else{
				select = 0;
			}
			
			if(getDisplayPoint(&display, Read_Ads7846(), &matrix)){
				if(display.x > 80 && display.x <160 && display.y>130 && display.y < 210 && get_animazione() == 0 && get_fine() == 0){
					set_animazione(3);
					enable_timer(3);
				}
			} 
	
	}
	
	
	if( emit_s == 1 ){
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song[currentNote++]);
				}
			}
			
			if(currentNote == (sizeof(song) / sizeof(song[0])))
			{
				disable_RIT();
				currentNote = 0;
				emit_s = 0;
			}
	} else if( emit_s == 2 ){
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song1[currentNote++]);
				}
			}
			
			if(currentNote == (sizeof(song1) / sizeof(song1[0])))
			{
				disable_RIT();
				currentNote = 0;
				emit_s = 0;
			}
	}else if( emit_s == 3 ){
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song2[currentNote++]);
				}
			}
			
			if(currentNote == (sizeof(song2) / sizeof(song2[0])))
			{
				currentNote = 0;
				emit_s = 0;
			}
	}else if( emit_s == 4 ){
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song3[currentNote++]);
				}
			}
			
			if(currentNote == (sizeof(song3) / sizeof(song3[0])))
			{
				currentNote = 0;
				emit_s = 0;
			}
	}else if( emit_s == 5 ){
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song[currentNote++]);
				}
			}
			
			if(currentNote == (sizeof(song) / sizeof(song[0])))
			{
				currentNote = 0;
				emit_s = 0;
			}
	}

	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

void set_status(int stat){
	status = stat;
}

int get_status(void){
	return status;
} 

void set_emit_s(int x){
	emit_s = x;
	enable_RIT();
}



/******************************************************************************
**                            End Of File
******************************************************************************/
