#include "LPC17xx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "Game_func.h"
#include "../RIT/RIT.h"


void LCD_InitGame(uint16_t color);
void init_tamagotchi(int x0, int y0,uint16_t colore_bordo, uint16_t colore_maglia, uint16_t colore_pantaloni, uint16_t colore_zaino, uint16_t colore_faccia);
void LCD_Update_Tamagotchi(int flag);

void Conversion_Time_Life_Tamagotchi(int time);

void draw_apple(int x0, int y0, uint16_t color_apple,  uint16_t color_border);
void draw_pera(int x0, int y0, uint16_t color_apple,  uint16_t color_border);
void draw_cuore(int x0, int y0, uint16_t color_border, uint16_t color_shadow, uint16_t color_inside);
void Animazione_snack(void);
void Animazione_meal(void);
void Animazione_touch(void);

void draw_speaker(int x0, int y0,uint16_t color_border, uint16_t color_shadow);
void draw_speaker_volume_0(int x0, int y0, uint16_t color);
void draw_speaker_volume_1(int x0, int y0, uint16_t color);
void draw_speaker_volume_2(int x0, int y0, uint16_t color);
void draw_speaker_volume_3(int x0, int y0, uint16_t color);

void set_fine(int end);
int get_fine(void);
void draw_rip(int x0, int y0);
void End_Game(void);


void emit_melody(int x);

//void emit_sound(int freq, int fatt_mult);

int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};



static int fine = 0;			// fine è un semaforo che impedisce che l'animazione in cui il tamagotchi mangia e quella in cui scappa si sovrappongono e creino un bug

void LCD_InitGame(uint16_t color){
	set_life(0);
	set_stop(0);
	//PET_INIT
	LCD_DrawRectangle(80,130,80,80,White);
	init_tamagotchi(80,130,Black,Blue2,Blue,Green,Grey);
	
	//CHOISE_INIT
	LCD_DrawRectangle(5,250,235,70,White);
	LCD_Empty_Rectangle(5,250,110,65,1,color);
	LCD_Empty_Rectangle(125,250,110,65,1,color);
	GUI_Text(30,275,(uint8_t *) " Meal ", color, White);
	GUI_Text(150,275,(uint8_t *) " Snack ", color, White);
	
	//AGE_INIT
	GUI_Text(65,20,(uint8_t *) " Age: ", color, White);
	GUI_Text(110,20,(uint8_t *) "00:00:00", color, White);
	
	//BATTERY_INIT
	LCD_InitBattery(40,70,color);
	LCD_InitBattery(150,70,color);		
	GUI_Text(25,45,(uint8_t *) " Happiness ", color, White);
	GUI_Text(135,45,(uint8_t *) " Satiety ", color, White);
	
	//SOUND INIT
	draw_speaker(10,10,Black,White);
	draw_speaker_volume_1(10,10,Black);
	draw_speaker_volume_2(10,10,Black);
	draw_speaker_volume_3(10,10,Black);
}

void init_tamagotchi(int x0, int y0, uint16_t colore_bordo, uint16_t colore_maglia, uint16_t colore_pantaloni, uint16_t colore_zaino, uint16_t colore_faccia){	
	
	//BORDI BIANCHI
	LCD_DrawRectangle(x0,y0,5,40,White);
	LCD_DrawRectangle(x0,y0,10,5,White);
	LCD_DrawRectangle(x0,y0+60,5,20,White);
	LCD_DrawRectangle(x0+5,y0+75,5,5,White);
	LCD_DrawRectangle(x0+20,y0+5,40,5,White);
	LCD_DrawRectangle(x0+25,y0+75,30,5,White);
	LCD_DrawRectangle(x0+70,y0+5,10,5,White);
	LCD_DrawRectangle(x0+75,y0+5,5,40,White);
	LCD_DrawRectangle(x0+70,y0+75,5,5,White);
	LCD_DrawRectangle(x0+75,y0+60,5,20,White);
	LCD_DrawRectangle(x0+80,y0+45,5,15,White);
	
	//BORDI BIANCHI	FACCIA
	LCD_DrawRectangle(x0+10,y0+10,5,40,White);
	LCD_DrawRectangle(x0+15,y0+10,5,15,White);
	LCD_DrawRectangle(x0+15,y0+40,5,10,White);
	LCD_DrawRectangle(x0+20,y0+15,40,5,White);
	LCD_DrawRectangle(x0+20,y0+45,40,5,White);
	LCD_DrawRectangle(x0+60,y0+10,5,15,White);
	LCD_DrawRectangle(x0+60,y0+40,5,10,White);
	LCD_DrawRectangle(x0+65,y0+10,5,40,White);
	
	//BORDO
	LCD_DrawRectangle(x0+10,y0+5,10,5,colore_bordo);
	LCD_DrawRectangle(x0+20,y0+10,40,5,colore_bordo);
	LCD_DrawRectangle(x0+60,y0+5,10,5,colore_bordo);
	LCD_DrawRectangle(x0+5,y0+10,5,35,colore_bordo);
	LCD_DrawRectangle(x0,y0+45,5,15,colore_bordo);
	LCD_DrawRectangle(x0+5,y0+60,5,15,colore_bordo);
	LCD_DrawRectangle(x0+10,y0+75,15,5,colore_bordo);
	LCD_DrawRectangle(x0+25,y0+70,30,5,colore_bordo);
	LCD_DrawRectangle(x0+55,y0+75,15,5,colore_bordo);
	LCD_DrawRectangle(x0+70,y0+60,5,15,colore_bordo);
	LCD_DrawRectangle(x0+75,y0+45,5,15,colore_bordo);
	LCD_DrawRectangle(x0+70,y0+10,5,40,colore_bordo);
	
	//BORDI BIANCHI VESTITI
	LCD_DrawRectangle(x0+5,y0+50,5,10,White);
	LCD_DrawRectangle(x0+70,y0+50,5,10,White);	
	
	//VESTITI
	LCD_DrawRectangle(x0+5,y0+45,10,5,colore_zaino);
	LCD_DrawRectangle(x0+10,y0+50,5,10,colore_zaino);
	LCD_DrawRectangle(x0+65,y0+45,10,5,colore_zaino);
	LCD_DrawRectangle(x0+65,y0+50,5,10,colore_zaino);
	LCD_DrawRectangle(x0+15,y0+50,50,10,colore_maglia);
	LCD_DrawRectangle(x0+10,y0+60,60,5,colore_maglia);
	LCD_DrawRectangle(x0+10,y0+65,60,5,colore_pantaloni);
	LCD_DrawRectangle(x0+10,y0+70,15,5,colore_pantaloni);
	LCD_DrawRectangle(x0+55,y0+70,15,5,colore_pantaloni);
	
	//FACCIA
	LCD_DrawRectangle(x0+15,y0+25,5,15,colore_faccia);
	LCD_DrawRectangle(x0+20,y0+20,40,25,colore_faccia);
	LCD_DrawRectangle(x0+60,y0+25,5,15,colore_faccia);
	LCD_DrawRectangle(x0+20,y0+30,5,5,colore_bordo);
	LCD_DrawRectangle(x0+55,y0+30,5,5,colore_bordo);
	LCD_DrawRectangle(x0+30,y0+35,20,5,colore_bordo);

}

void LCD_Update_Tamagotchi(int flag){
	
	
	if(flag  == 0){
			LCD_DrawRectangle(100,160,5,2,White);
			LCD_DrawRectangle(100,163,5,2,White);
			LCD_DrawRectangle(135,160,5,2,White);
			LCD_DrawRectangle(135,163,5,2,White);
			flag = 1;
	}else{
			LCD_DrawRectangle(100,160,5,2,Black);
			LCD_DrawRectangle(100,163,5,2,Black);
			LCD_DrawRectangle(135,160,5,2,Black);
			LCD_DrawRectangle(135,163,5,2,Black);
			flag = 0;
	}
	
			
}

void Conversion_Time_Life_Tamagotchi(int time){
		int ore, minuti, secondi;
		char stringa[15];

		ore=time/3600;
	  minuti=(time%3600)/60;
		secondi=(time%3600)%60;
					
		sprintf(stringa,"%02d:%02d:%02d", ore, minuti, secondi);
		
		GUI_Text(110,20,(uint8_t *) "00:00:00", White, White);
		GUI_Text(110,20,(uint8_t *) stringa, Black, White);
}

void Animazione_meal(void){
			volatile static int i = 0, j = 0;
			static int controllo = 0;  
			int x = 5;
	
			if(controllo == 0)
				draw_pera(220,220,Green,Black);
		
			if(controllo < 10){
					
				LCD_DrawRectangle(80+i,130,5,80,White);
				init_tamagotchi(80+i+x,130,Black,Blue2,Blue,Green,Grey);
				i = i+5;
				controllo++;
			
			}else if(controllo < 21){
				
				draw_pera(220,220-j,White,White);
				draw_pera(220,220-j-3,Green,Black);													
				j = j+3;																											
			
				if (controllo == 15) emit_melody(2);	

				if(controllo == 20)
					LCD_DrawRectangle(220,220-j-3-17,40,40,White);

				controllo++;
				
			 }else if(controllo < 33){
				
				LCD_DrawRectangle(80+i,130,5,80,White);
				init_tamagotchi(80+i,130,Black,Blue2,Blue,Green,Grey);
				i = i-5;
				controllo++;
				
				if(controllo == 32)	{
					
					set_animazione(0);
					disable_timer(3);
					fine = 0;											//libero l'animazione della end_game
					i = 0;
					j = 0;
					controllo = 0;
					
					enable_RIT();
					enable_timer(0);
					enable_timer(1);
					LCD_Increase_Satiety();
					set_tim2(0);
				}
				
			}
			
}	

void Animazione_snack(void){
		  volatile static int i = 0, j = 0;
			static int controllo = 0;  
			int x = 5;

	
			if(controllo == 0)
				draw_apple(220,220,Red,Black);

			if(controllo < 10){
	
				LCD_DrawRectangle(80+i,130,5,80,White);
				init_tamagotchi(80+i+x,130,Black,Blue2,Blue,Green,Grey);
				i = i+5;
				controllo++;
			
			}else if(controllo < 21){
				
				if (controllo == 15) emit_melody(2);
				
				draw_apple(220,220-j,White,White);
				draw_apple(220,220-j-3,Red,Black);														
				j = j+3;																											
			
				if(controllo == 20){
					
					LCD_DrawRectangle(220,220-j-3-17,40,40,White);
				}
				controllo++;
				
			} else if(controllo < 33){
			
				LCD_DrawRectangle(80+i,130,5,80,White);
				init_tamagotchi(80+i,130,Black,Blue2,Blue,Green,Grey);
				i = i-5;
				controllo++;
				
				if(controllo == 32)	{
					disable_timer(3);
					set_animazione(0);
					fine = 0;											//libero l'animazione della end_game
					i = 0;
					j = 0;
					controllo = 0;

					enable_RIT();
					enable_timer(0);
					LCD_Increase_Happines();
					set_tim1(0);
				}
				
			}
		
			
}


void set_fine(int end){
		fine = end;
}

int get_fine(void){
		return fine;
}

void draw_apple(int x0, int y0, uint16_t color_apple,  uint16_t color_border){
		LCD_DrawRectangle(x0,y0,20,20,color_apple);
		LCD_DrawRectangle(x0 + 5,y0+1,1,2,color_border);
		LCD_DrawRectangle(x0 + 5,y0+2,11,1,color_border);
		LCD_DrawRectangle(x0 + 15,y0+1,1,2,color_border);
		LCD_DrawRectangle(x0 + 10,y0-6,1,8,color_border);
		LCD_DrawRectangle(x0 +10,y0-6,3,1,color_border);
}

void draw_pera(int x0, int y0, uint16_t color_apple,  uint16_t color_border){
		LCD_DrawRectangle(x0+1,y0+5,18,15,color_apple);
		LCD_DrawRectangle(x0+3,y0-11,14,16,color_apple);
		LCD_DrawRectangle(x0 + 6,y0-9,1,2,color_border);
		LCD_DrawRectangle(x0 + 6,y0-8,9,1,color_border);
		LCD_DrawRectangle(x0 + 14,y0-9,1,2,color_border);
		LCD_DrawRectangle(x0 + 10,y0-17,1,9,color_border);
		LCD_DrawRectangle(x0 +10,y0-17,3,1,color_border);
}

void draw_rip(int x0, int y0){	
  	//LAPIDE
		LCD_DrawRectangle(x0+3,y0+74,3,3,Black);
		LCD_DrawRectangle(x0+6,y0+77,68,3,Black);
		LCD_DrawRectangle(x0+6,y0+71,68,3,Black);
		LCD_DrawRectangle(x0+75,y0+74,3,3,Black);
		LCD_DrawRectangle(x0+9,y0+18,3,53,Black);
		LCD_DrawRectangle(x0+12,y0+12,3,6,Black);
		LCD_DrawRectangle(x0+15,y0+9,3,3,Black);
		LCD_DrawRectangle(x0+18,y0+6,3,3,Black);
		LCD_DrawRectangle(x0+21,y0+3,6,3,Black);
		LCD_DrawRectangle(x0+27,y0,26,3,Black);
		LCD_DrawRectangle(x0+54,y0+3,6,3,Black);
		LCD_DrawRectangle(x0+60,y0+6,3,3,Black);
		LCD_DrawRectangle(x0+63,y0+9,3,3,Black);
		LCD_DrawRectangle(x0+66,y0+12,3,6,Black);
		LCD_DrawRectangle(x0+69,y0+18,3,53,Black);
	
		//SCRITTA
	
		LCD_DrawRectangle(x0+22,y0+21,3,15,Black);
		LCD_DrawRectangle(x0+25,y0+21,9,3,Black);
		LCD_DrawRectangle(x0+25,y0+27,6,3,Black);
		LCD_DrawRectangle(x0+31,y0+24,3,3,Black);
		LCD_DrawRectangle(x0+31,y0+30,3,6,Black);
		
		LCD_DrawRectangle(x0+37,y0+21,9,3,Black);
		LCD_DrawRectangle(x0+40,y0+24,3,9,Black);
		LCD_DrawRectangle(x0+37,y0+33,9,3,Black);
		
		LCD_DrawRectangle(x0+49,y0+21,3,15,Black);
		LCD_DrawRectangle(x0+51,y0+21,6,3,Black);
		LCD_DrawRectangle(x0+52,y0+26,6,3,Black);
		LCD_DrawRectangle(x0+58,y0+24,3,3,Black);
		
}


void End_Game(void){
		int i = 1;
		fine = 1;
		if(get_animazione() == 0 && fine == 1){
			
			for( i = 0; i <= 200; i=i+5){
					if(i==150) emit_melody(3);
					LCD_DrawRectangle(80+i,130,5,80,White);
					init_tamagotchi(80+i+5,130,Black,Blue2,Blue,Green,Grey);
			}
			
			LCD_DrawRectangle(80+20,130+30,5,5,White);
			LCD_DrawRectangle(80+55,130+30,5,5,White);
			LCD_DrawRectangle(80,130,80,80,White);
			draw_rip(80,130);
			
		
			LCD_DrawRectangle(5,250,235,70,White);
			LCD_Empty_Rectangle(5,250,230,65,1,Red);
			GUI_Text(100,275,(uint8_t *) " Reset ", Black, White);
			
			fine = 0;
		
		}
		reset_RIT();
		enable_RIT();
}

void draw_cuore(int x0, int y0, uint16_t color_border, uint16_t color_shadow, uint16_t color_inside){	
  	//BORDO CUORE
		LCD_DrawRectangle(x0+4,y0+1,4,1,color_border);
		LCD_DrawRectangle(x0+8,y0+2,1,2,color_border);
		LCD_DrawRectangle(x0+8,y0+3,3,1,color_border);
		LCD_DrawRectangle(x0+10,y0+2,1,2,color_border);
		LCD_DrawRectangle(x0+11,y0+1,4,1,color_border);
		LCD_DrawRectangle(x0+15,y0+2,1,2,color_border);
		LCD_DrawRectangle(x0+16,y0+3,1,1,color_border);
		LCD_DrawRectangle(x0+17,y0+4,1,5,color_border);
		LCD_DrawRectangle(x0+15,y0+9,2,1,color_border);
		LCD_DrawRectangle(x0+15,y0+10,1,1,color_border);
		LCD_DrawRectangle(x0+13,y0+11,2,1,color_border);
		LCD_DrawRectangle(x0+11,y0+12,2,1,color_border);
		LCD_DrawRectangle(x0+11,y0+13,1,1,color_border);
		LCD_DrawRectangle(x0+8,y0+14,3,1,color_border);
		LCD_DrawRectangle(x0+7,y0+13,1,1,color_border);
		LCD_DrawRectangle(x0+6,y0+12,2,1,color_border);
		LCD_DrawRectangle(x0+4,y0+11,2,1,color_border);
		LCD_DrawRectangle(x0+3,y0+10,1,1,color_border);
		LCD_DrawRectangle(x0+2,y0+9,2,1,color_border);
		LCD_DrawRectangle(x0+1,y0+4,1,5,color_border);
		LCD_DrawRectangle(x0+2,y0+3,2,1,color_border);
		LCD_DrawRectangle(x0+3,y0+2,1,1,color_border);

		//RIEMPIMENTO
	
		LCD_DrawRectangle(x0+4,y0+2,4,2,color_inside);
		LCD_DrawRectangle(x0+11,y0+2,4,2,color_inside);
		LCD_DrawRectangle(x0+2,y0+4,15,5,color_inside);
		LCD_DrawRectangle(x0+4,y0+9,11,2,color_inside);
		LCD_DrawRectangle(x0+6,y0+11,7,1,color_inside);
		LCD_DrawRectangle(x0+8,y0+12,3,2,color_inside);
		
		LCD_DrawRectangle(x0+4,y0+4,2,1,color_shadow);
}

void draw_speaker(int x0, int y0, uint16_t color_border, uint16_t color_shadow ){	
  	//PARTE PRINCIPALE
		LCD_DrawRectangle(x0+1,y0+8,8,5,color_border);
		LCD_DrawRectangle(x0+5,y0+7,4,1,color_border);
		LCD_DrawRectangle(x0+6,y0+6,3,1,color_border);
		LCD_DrawRectangle(x0+7,y0+5,2,1,color_border);
		LCD_DrawRectangle(x0+8,y0+4,1,1,color_border);
		LCD_DrawRectangle(x0+5,y0+13,4,1,color_border);
		LCD_DrawRectangle(x0+6,y0+14,3,1,color_border);
		LCD_DrawRectangle(x0+7,y0+15,2,1,color_border);
		LCD_DrawRectangle(x0+8,y0+16,1,1,color_border);
		LCD_DrawRectangle(x0+3,y0+9,3,1,color_shadow);
		LCD_DrawRectangle(x0+6,y0+8,1,1,color_shadow);
		LCD_DrawRectangle(x0+7,y0+7,1,1,color_shadow);
}

void draw_speaker_volume_0(int x0, int y0, uint16_t color){	
		LCD_DrawRectangle(x0+10,y0+8,1,1,color);
		LCD_DrawRectangle(x0+11,y0+9,1,1,color);
		LCD_DrawRectangle(x0+12,y0+10,1,1,color);
		LCD_DrawRectangle(x0+13,y0+11,1,1,color);
		LCD_DrawRectangle(x0+14,y0+12,1,1,color);
		LCD_DrawRectangle(x0+10,y0+12,1,1,color);
		LCD_DrawRectangle(x0+11,y0+11,1,1,color);
		LCD_DrawRectangle(x0+13,y0+9,1,1,color);
		LCD_DrawRectangle(x0+14,y0+8,1,1,color);
}

void draw_speaker_volume_1(int x0, int y0, uint16_t color){	
		LCD_DrawRectangle(x0+10,y0+7,1,1,color);
		LCD_DrawRectangle(x0+11,y0+8,1,1,color);
		LCD_DrawRectangle(x0+12,y0+9,1,3,color);
		LCD_DrawRectangle(x0+11,y0+12,1,1,color);
		LCD_DrawRectangle(x0+10,y0+13,1,1,color);
}

void draw_speaker_volume_2(int x0, int y0, uint16_t color){	
		LCD_DrawRectangle(x0+10,y0+7,1,1,color);
		LCD_DrawRectangle(x0+11,y0+8,1,1,color);
		LCD_DrawRectangle(x0+14,y0+7,1,1,color);
		LCD_DrawRectangle(x0+15,y0+8,1,5,color);
		LCD_DrawRectangle(x0+14,y0+13,1,1,color);
		LCD_DrawRectangle(x0+13,y0+14,1,1,color);
		LCD_DrawRectangle(x0+12,y0+15,1,1,color);
}

void draw_speaker_volume_3(int x0, int y0, uint16_t color){	
		LCD_DrawRectangle(x0+14,y0+3,1,1,color);
		LCD_DrawRectangle(x0+15,y0+4,1,1,color);
		LCD_DrawRectangle(x0+16,y0+5,1,1,color);
		LCD_DrawRectangle(x0+17,y0+6,1,1,color);
		LCD_DrawRectangle(x0+18,y0+7,1,7,color);
		LCD_DrawRectangle(x0+17,y0+14,1,1,color);
		LCD_DrawRectangle(x0+16,y0+15,1,1,color);
		LCD_DrawRectangle(x0+16,y0+16,1,1,color);
		LCD_DrawRectangle(x0+14,y0+17,1,1,color);
}

void Animazione_touch(void){
	int static flag = 0;
	int static stop = 0;

	stop++;
	if (flag == 0){
		draw_cuore(170,130,White,White,White);
		draw_cuore(50, 150,White,White,White);
		draw_cuore(170,170,White,White,White);
		emit_melody(4);
		draw_cuore(50,130,Black,White,Red);
		draw_cuore(170, 150,Black,White,Red);
		draw_cuore(50,170,Black,White,Red);
		
		flag = 1;
	}else{
		draw_cuore(50,130,White,White,White);
		draw_cuore(170, 150,White,White,White);
		draw_cuore(50,170,White,White,White);
		emit_melody(4);
		draw_cuore(170,130,Black,White,Red);
		draw_cuore(50, 150,Black,White,Red);
		draw_cuore(170,170,Black,White,Red);
		
		flag = 0;
	}
	
	if(stop == 8){
		stop = 0;
		set_animazione(0);
		draw_cuore(50,130,White,White,White);
		draw_cuore(170, 150,White,White,White);
		draw_cuore(50,170,White,White,White);
		draw_cuore(170,130,White,White,White);
		draw_cuore(50, 150,White,White,White);
		draw_cuore(170,170,White,White,White);
		LCD_Increase_Happines();
		set_tim1(0);
	}
	
}

void emit_melody(int x){
		set_emit_s(x);
		
}
