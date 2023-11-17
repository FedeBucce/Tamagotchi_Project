#ifndef __GAME_F
#define __GAME_F


//Generali
extern void LCD_InitGame(uint16_t color);

//Gestione Batteria
extern void LCD_InitBattery( uint16_t x0, uint16_t y0, uint16_t colore );
extern void LCD_Decrease_Happines(void);
extern void LCD_Decrease_Satiety(void);
extern void LCD_Increase_Satiety(void);
extern void LCD_Increase_Happines(void);

//Gestione Tamagotchi
extern void Conversion_Time_Life_Tamagotchi(int time);
extern void init_tamagotchi(int x0, int y0,uint16_t colore_bordo, uint16_t colore_maglia, uint16_t colore_pantaloni, uint16_t colore_zaino,  uint16_t colore_faccia);
extern void LCD_Update_Tamagotchi(int flag);
extern void draw_apple(int x0, int y0, uint16_t color_apple,  uint16_t color_border);
extern void draw_pera(int x0, int y0, uint16_t color_apple,  uint16_t color_border);
extern void draw_cuore(int x0, int y0, uint16_t color_border, uint16_t color_shadow, uint16_t color_inside);

extern void draw_speaker(int x0, int y0,uint16_t color_border, uint16_t color_shadow);
extern void draw_speaker_volume_0(int x0, int y0, uint16_t color);
extern void draw_speaker_volume_1(int x0, int y0, uint16_t color);
extern void draw_speaker_volume_2(int x0, int y0, uint16_t color);
extern void draw_speaker_volume_3(int x0, int y0, uint16_t color);

extern void Animazione_snack(void);
extern void Animazione_meal(void);
extern void Animazione_touch(void);
extern void set_fine(int end);
extern int get_fine(void);
extern void draw_rip(int x0, int y0);
extern void End_Game(void);

extern void emit_melody(int x);


//extern void emit_sound(int freq, int fatt_mult);

#endif 
