#include "LPC17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "Game_func.h"
#include "../RIT/RIT.h"

void LCD_InitBattery( uint16_t x0, uint16_t y0, uint16_t colore );
void LCD_init_happines_satiety(int h, int s);

void LCD_Decrease_Happines(void);
void LCD_Decrease_Satiety(void);
void LCD_Increase_Satiety(void);
void LCD_Increase_Happines(void);


static int satiety = 4;
static int happines = 4;

void LCD_InitBattery( uint16_t x0, uint16_t y0, uint16_t colore ){		
	
		//LE BARREIE AVRANNO 4 TACCHE DI 8x18
		LCD_DrawLine(x0,y0-1,x0,y0+21,colore);
		LCD_DrawLine(x0,y0-1,x0+44,y0-1,colore);
		LCD_DrawLine(x0,y0+21,x0+44,y0+21,colore);
		LCD_DrawLine(x0+44,y0,x0+44,y0+21,colore);
	
		LCD_DrawLine(x0+44,y0+5,x0+48,y0+5,colore);
		LCD_DrawLine(x0+44,y0+21-5,x0+48,y0+21-5,colore);
		LCD_DrawLine(x0+48,y0+5,x0+48,y0+21-5,colore);
	
		LCD_DrawRectangle(x0,y0+1,8,18,Black);
		LCD_DrawRectangle(x0+11,y0+1,8,18,Black);
		LCD_DrawRectangle(x0+22,y0+1,8,18,Black);
		LCD_DrawRectangle(x0+33,y0+1,8,18,Black);
	
		LCD_init_happines_satiety(4,4);

}

void LCD_init_happines_satiety(int h, int s){
		happines = 4;
		satiety = 4;
}

void LCD_Decrease_Happines(void){

		if(happines == 4)
					LCD_DrawRectangle(40+33,70+1,8,18,White);
		else if(happines == 3)
					LCD_DrawRectangle(40+22,70+1,8,18,White);
		else if(happines == 2)
					LCD_DrawRectangle(40+11,70+1,8,18,White);
		else if(happines == 1)
					LCD_DrawRectangle(40+1,70+1,8,18,White);
		if(happines != 0)
				happines--;
		
		if((happines == 0 || satiety == 0) && get_status() != 3){
			set_stop(1);										  //Dico al Tim0 che sta morendo il tamagotchi 
			set_status(3);										//Dico al RIT di mettere la variabile status a 3 cosi da poter utilizzare il tasto RESET
			set_fine(1);
			disable_timer(0);  						
			End_Game();
		}
}

void LCD_Decrease_Satiety(void){
		
		if(satiety == 4)
					LCD_DrawRectangle(150+33,70+1,8,18,White);
		else if(satiety == 3)
					LCD_DrawRectangle(150+22,70+1,8,18,White);
		else if(satiety == 2)
					LCD_DrawRectangle(150+11,70+1,8,18,White);
		else if(satiety == 1)
					LCD_DrawRectangle(150+1,70+1,8,18,White);
		if(satiety != 0)
			satiety--;
		
		if((happines == 0 || satiety == 0) && get_status() != 3){
			set_stop(1);												//Dico al Tim0 che sta morendo il tamagotchi 
			set_status(3);											//Dico al RIT di mettere la variabile status a 3 cosi da poter utilizzare il tasto RESET
			set_fine(1);
			disable_timer(0);  									
			End_Game();
		}
}

void LCD_Increase_Satiety(void){
		if(satiety != 0){				//Questo controllo serve per evitare che aggiunga una batteria nel momento in cui sta morendo il tamagotchi
			if(satiety != 4)
					satiety++;
		
			if(satiety == 4)
						LCD_DrawRectangle(150+33,70+1,8,18,Black);
			else if(satiety == 3)
						LCD_DrawRectangle(150+22,70+1,8,18,Black);
			else if(satiety == 2)
						LCD_DrawRectangle(150+11,70+1,8,18,Black);
			else if(satiety == 1)
						LCD_DrawRectangle(150+1,70+1,8,18,Black);
		}
	
}

void LCD_Increase_Happines(void){
		if (happines != 0){			//Questo controllo serve per evitare che aggiunga una batteria nel momento in cui sta morendo il tamagotchi
			if (happines != 4)
					happines++;
		
			if(happines == 4)
						LCD_DrawRectangle(40+33,70+1,8,18,Black);
			else if(happines == 3)
						LCD_DrawRectangle(40+22,70+1,8,18,Black);
			else if(happines == 2)
						LCD_DrawRectangle(40+11,70+1,8,18,Black);
			else if(happines == 1)
						LCD_DrawRectangle(40+1,70+1,8,18,Black);
		}
}


