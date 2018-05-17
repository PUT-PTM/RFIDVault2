#include "stm32f4xx.h"

/**
 *	@libraries http://stm32f4-discovery.com
 **/
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_mfrc522.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_pwm.h"
#include "tm_stm32f4_keypad.h"

#include <stdio.h>

void TM_DELAY_1msHandler(void) {
    /* Process keypad */
    TM_KEYPAD_Update();
}

int main(void) {
	TM_PWM_TIM_t TIM2_Data;
	
	TM_KEYPAD_Button_t Keypad_Button;
  char buff[20];
	uint16_t position = 900;
	
	uint8_t CardID[5];
	
	uint8_t MyIDB[5] = {
		0x10, 0x95, 0x24, 0xd9, 0x78	/* Brelok */
	};
	uint8_t MyIDK[5] = {
		0x65, 0x60, 0x06, 0x85, 0x86	/* Karta */
	};
	//char buffer[50];
	
	uint8_t lastview = 0;
	
	SystemInit();
	
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_ILI9341_Init();
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_1);	
	
	TM_MFRC522_Init();
	
	TM_KEYPAD_Init(TM_KEYPAD_Type_Large);
	
	TM_PWM_InitTimer(TIM2, &TIM2_Data, 100);
	TM_PWM_InitChannel(&TIM2_Data, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
	TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, 900);
	
	Delayms(1000);

	while (1) {
		if (TM_MFRC522_Check(CardID) == MI_OK) {
			/* CardID is valid */
			if(lastview != 1) {
				TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
				lastview = 1;
			}
			if (TM_MFRC522_Compare(CardID, MyIDB) == MI_OK) {				
						if (position == 900) {
							position = 400;
							TM_ILI9341_Puts(10, 100, "Witaj Krzychu!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							TM_ILI9341_Puts(15, 150, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
						} else {
							position = 900;
							TM_ILI9341_Puts(10, 100, "Dowidzenia!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							TM_ILI9341_Puts(15, 150, "Zamek zamkniety", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
						}
						TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, position);	
						Delayms(3000);
			} else if (TM_MFRC522_Compare(CardID, MyIDK) == MI_OK) {
				TM_ILI9341_Puts(25, 100, "Witaj WerVa!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
						TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, 400);
				TM_ILI9341_Puts(15, 150, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
						Delayms(3000);
						TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, 900);
			} else {
				TM_ILI9341_Puts(10, 130, "Nie rozpoznano", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_WHITE);
				TM_ILI9341_Puts(10, 150, "identyfikatora", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_WHITE);
			}
			/* CardID check */
			/*
			TM_ILI9341_Puts(10, 10, "Wykryto karte", &TM_Font_11x18, 0x00, 0xFFFF);
			sprintf(buffer, "0x%02x\n0x%02x\n0x%02x\n0x%02x\n0x%02x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
			TM_ILI9341_Puts(10, 30, buffer, &TM_Font_11x18, 0x00, 0xFFFF);
			*/			
		} else {
			if(lastview != 0) {
				TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
				lastview = 0;
			}
			Keypad_Button = TM_KEYPAD_Read();
			if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED) {/* Keypad is pressed */
				switch (Keypad_Button) {
					case TM_KEYPAD_Button_0:        /* Button 0 pressed */
							TM_ILI9341_Puts(10, 100, "0!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_1:        /* Button 1 pressed */
							TM_ILI9341_Puts(10, 100, "1!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_2:        /* Button 2 pressed */
							TM_ILI9341_Puts(10, 100, "2!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_3:        /* Button 3 pressed */
							TM_ILI9341_Puts(10, 100, "3!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_4:        /* Button 4 pressed */
							TM_ILI9341_Puts(10, 100, "4!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_5:        /* Button 5 pressed */
							TM_ILI9341_Puts(10, 100, "5!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_6:        /* Button 6 pressed */
							TM_ILI9341_Puts(10, 100, "6!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_7:        /* Button 7 pressed */
							TM_ILI9341_Puts(10, 100, "7!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_8:        /* Button 8 pressed */
							TM_ILI9341_Puts(10, 100, "8!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_9:        /* Button 9 pressed */
							TM_ILI9341_Puts(10, 100, "9!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							/* Do your stuff here */
							break;
					case TM_KEYPAD_Button_STAR:        /* Button STAR pressed */
							TM_ILI9341_Puts(10, 100, "*!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_HASH:        /* Button HASH pressed */
							TM_ILI9341_Puts(10, 100, "#!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_A:        /* Button A pressed, only on large keyboard */
							/* Do your stuff here */
							TM_ILI9341_Puts(10, 100, "A!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_B:        /* Button B pressed, only on large keyboard */
							/* Do your stuff here */\
							TM_ILI9341_Puts(10, 100, "B!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_C:        /* Button C pressed, only on large keyboard */
							/* Do your stuff here */
							TM_ILI9341_Puts(10, 100, "C!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					case TM_KEYPAD_Button_D:        /* Button D pressed, only on large keyboard */
							/* Do your stuff here */
							TM_ILI9341_Puts(10, 100, "D!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
							break;
					default:
						break;
				}
			} else {
				TM_ILI9341_Puts(10, 10, "Nie wykryto karty", &TM_Font_11x18, 0x00, ILI9341_COLOR_WHITE);
				TM_ILI9341_Puts(10, 50, "Zbliz czujnik lub podaj pin", &TM_Font_11x18, 0x00, ILI9341_COLOR_WHITE);
			}
		}
	}
}

