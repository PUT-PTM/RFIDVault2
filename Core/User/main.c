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
    TM_KEYPAD_Update();
}

void clearPin(uint8_t* arr) {
    for (uint8_t a = 0; a < 4; a++) {
			arr[a] = 99;
		}
}
uint8_t setPin(uint8_t* TempPin, uint8_t Number) {
	for (uint8_t i = 0; i < 4; i++) {
		if (TempPin[i] == 99) {
			TempPin[i] = Number;
			return 1;
		}
	}
	return 0;
}
uint8_t comparePin(uint8_t* TempPin, uint8_t* UserPin) {
	for (uint8_t i = 0; i < 4; i++) {
		if (TempPin[i] != UserPin[i]) {
			return 0;
		}
	}
	return 1;
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
	uint8_t TempPin[4] = {99, 99, 99, 99};
	uint8_t PinA[4] = {1, 2, 3, 4};
	uint8_t PinB[4] = {2, 3, 4, 5};
	uint8_t PinC[4] = {3, 4, 5, 6};
	uint8_t PinD[4] = {4, 5, 6, 7};
	uint8_t activeUser[4] = {98, 98, 98, 98};
	
	uint8_t lastview = 99;
	uint8_t pinStart = 0;
	uint8_t pinChange = 0;
	SystemInit();
	
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_ILI9341_Init();
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
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
			//if(lastview != 1) {
				TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
				lastview = 1;
			//}
			
			if (TM_MFRC522_Compare(CardID, MyIDB) == MI_OK) {				
				if (position == 900) {
					position = 400;
					TM_ILI9341_Puts(45, 80, "Witaj Krzychu!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
					TM_ILI9341_Puts(50, 150, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
				} else {
					position = 900;
					TM_ILI9341_Puts(65, 80, "Do widzenia!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
					TM_ILI9341_Puts(40, 150, "Zamek zamkniety", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
				}
				TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, position);	
				Delayms(3000);
			} else if (TM_MFRC522_Compare(CardID, MyIDK) == MI_OK) {
				if (position == 900) {
					position = 400;
					TM_ILI9341_Puts(60, 80, "Witaj WerVa!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
					TM_ILI9341_Puts(50, 150, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
				} else {
					position = 900;
					TM_ILI9341_Puts(65, 80, "Do widzenia!", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
					TM_ILI9341_Puts(40, 150, "Zamek zamkniety", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
				}
				TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, position);	
				Delayms(3000);
			} else {
				TM_ILI9341_Puts(10, 130, "Nie rozpoznano", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
				TM_ILI9341_Puts(10, 150, "identyfikatora", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
			}
			clearPin(TempPin);
			pinStart = 0;
			
			/* CardID check */
			/*
			TM_ILI9341_Puts(10, 10, "Wykryto karte", &TM_Font_11x18, 0x00, 0xFFFF);
			sprintf(buffer, "0x%02x\n0x%02x\n0x%02x\n0x%02x\n0x%02x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
			TM_ILI9341_Puts(10, 30, buffer, &TM_Font_11x18, 0x00, 0xFFFF);
			*/			
		} else {
			Keypad_Button = TM_KEYPAD_Read();
			if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED) {/* Keypad is pressed */
				switch (Keypad_Button) {
					case TM_KEYPAD_Button_0:        /* Button 0 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 0)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_1:        /* Button 1 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 1)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_2:        /* Button 2 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 2)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_3:        /* Button 3 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 3)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_4:        /* Button 4 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 4)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_5:        /* Button 5 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 5)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_6:        /* Button 6 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 6)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_7:        /* Button 7 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 7)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_8:        /* Button 8 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 8)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_9:        /* Button 9 pressed */
							if(pinStart == 1){
								if(setPin(TempPin, 9)){
									pinChange = 1;
								}
							}
							break;
					case TM_KEYPAD_Button_STAR:        /* Button STAR pressed */
							TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
							clearPin(TempPin);
							pinStart = 0;
							lastview = 99;
							break;
					case TM_KEYPAD_Button_HASH:        /* Button HASH pressed */
							if(pinStart == 1 && comparePin(TempPin, activeUser) == 1){
								TM_ILI9341_Puts(200, 100, "*", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
								clearPin(TempPin);
								pinStart = 0;
								if (position == 900) {
									position = 400;
									TM_ILI9341_Puts(50, 150, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
								} else {
									position = 900;
									TM_ILI9341_Puts(40, 150, "Zamek zamkniety", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
								}
								TM_PWM_SetChannelMicros(&TIM2_Data, TM_PWM_Channel_1, position);
								Delayms(3000);
							} else if (pinStart == 1) {
								clearPin(TempPin);
								pinStart = 0;
								TM_ILI9341_Puts(35, 170, "Niepoprawny kod!", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
								Delayms(1500);
							}
							break;
					case TM_KEYPAD_Button_A:        /* Button A pressed, only on large keyboard */
							if(comparePin(PinA, activeUser) == 0){
								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
								for (uint8_t i = 0; i < 4; i++) {
									 activeUser[i] = PinA[i];
								}
								lastview = 2;
								pinStart = 1;
								pinChange = 1;
								TM_ILI9341_Puts(10, 10, "Wprowadz pin uzytkownika A!", &TM_Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
							}
							break;
					case TM_KEYPAD_Button_B:        /* Button B pressed, only on large keyboard */
							if(comparePin(PinB, activeUser) == 0){
								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
								for (uint8_t i = 0; i < 4; i++) {
									 activeUser[i] = PinB[i];
								};
								lastview = 2;
								pinStart = 1;
								pinChange = 1;
								TM_ILI9341_Puts(10, 10, "Wprowadz pin uzytkownika B!", &TM_Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
							}
							break;
					case TM_KEYPAD_Button_C:        /* Button C pressed, only on large keyboard */
							if(comparePin(PinC, activeUser) == 0){
								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
								for (uint8_t i = 0; i < 4; i++) {
									 activeUser[i] = PinC[i];
								};
								lastview = 2;
								pinStart = 1;
								pinChange = 1;
								TM_ILI9341_Puts(10, 10, "Wprowadz pin uzytkownika C!", &TM_Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
							}
							break;
					case TM_KEYPAD_Button_D:        /* Button D pressed, only on large keyboard */
							if(comparePin(PinD, activeUser) == 0){
								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
								for (uint8_t i = 0; i < 4; i++) {
									 activeUser[i] = PinD[i];
								};
								lastview = 2;
								pinStart = 1;
								pinChange = 1;
								TM_ILI9341_Puts(10, 10, "Wprowadz pin uzytkownika D!", &TM_Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
							}
							break;
					default:
						break;
				}
			} else {
				if(lastview != 0 && TempPin[0] == 99 && pinStart == 0) {
					for (uint8_t i = 0; i < 4; i++) {
						 activeUser[i] = 98;
					}
					TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
					lastview = 0;
					TM_ILI9341_Puts(10, 10, "Zbliz czujnik lub podaj pin", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					if (position == 900) {
						TM_ILI9341_Puts(40, 200, "Zamek zamkniety", &TM_Font_16x26, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
					} else {
						TM_ILI9341_Puts(50, 200, "Zamek otwarty", &TM_Font_16x26, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
					}
				} else if(pinStart == 1 && pinChange == 1){
					pinChange = 0;
					if(TempPin[0] != 99){
						if(TempPin[1] != 99){
							TM_ILI9341_Puts(80, 100, "*", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						} else {
							sprintf(buff, "%d", TempPin[0]);
							TM_ILI9341_Puts(80, 100, buff, &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						}
					} else {
						TM_ILI9341_Puts(80, 100, "_", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					}						
					if(TempPin[1] != 99){
						if(TempPin[2] != 99){
							TM_ILI9341_Puts(120, 100, "*", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						} else {
							sprintf(buff, "%d", TempPin[1]);
							TM_ILI9341_Puts(120, 100, buff, &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						}
					} else {
						TM_ILI9341_Puts(120, 100, "_", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					}
					if(TempPin[2] != 99){
						if(TempPin[3] != 99){
							TM_ILI9341_Puts(160, 100, "*", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						} else {
							sprintf(buff, "%d", TempPin[2]);
							TM_ILI9341_Puts(160, 100, buff, &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
						}
					} else {
						TM_ILI9341_Puts(160, 100, "_", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					}						
					if(TempPin[3] != 99){
						sprintf(buff, "%d", TempPin[3]);
						TM_ILI9341_Puts(200, 100, buff, &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					} else {
						TM_ILI9341_Puts(200, 100, "_", &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					}						
					TM_ILI9341_Puts(10, 220, "(*)Wyczysc", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
					TM_ILI9341_Puts(180, 220, "Potwierdz(#)", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
				}
			}
		}
	}
}

