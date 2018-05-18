# Overview 
[PL] 
Ile razy miałeś tak, że chciałeś zabezpieczyć drogocenne przedmioty czy pieniądze przez niepowołanymi rękami. Skarpety? No jest to jakieś wyjście ale trzymanie pieniędzy tam raczej mało uchroni je przed kradzieżą. Banki? Jesteś osobą(typowym Polakiem), co woli mieć kontrole nad pieniądzem? Właśnie myśląc o takich ludziach stworzyliśmy nasz projekt! 
Nasz projekt jest to sejf wykorzystujący technologię RFID oraz awaryjne otwieranie, w przypadku braku karty lub breloka,  czyli klasyczny pin, co oznacza, że zawsze masz dostęp do swoich skarbów. 

[EN]
How many times have you wanted to protect precious things or your money from /unauthorized hands/. Socks? Well, it might seem like a good solution, but keeping your money there won't protect it from stealing. Do you like to have control over money? We've made our project for people like you!
Our project is a safe, that uses RFID technology. It also has emergency open - in case you forget your card or pendant you can use a PIN number, which means you always have access to your treasures.

## Description 
[PL]
W naszym projekcie wykorzystaliśmy: 
Elektronika:
- STM32F429I-DISCO - zestaw uruchomieniowy z mikrokontrolerem i wbudowanym wyświetlaczem
- moduł czytnika RFID RC522 13,56MHz + karta + brelok
- klawiatura membranowa 4 x 4
- serwomechanizm modelarski TowerPro SG90
- listwa led z lampki na USB
- powerbank 11000mAh
- wyłącznik krańcowy
Obudowa:
- sklejka 
- dibond (płyta kompozytowa)
[EN]

- Keypad
	C1	>	PD0			//Keypad COLUMN 1
	C2	>	PD1			//Keypad COLUMN 2
	C3	>	PD2			//Keypad COLUMN 3
	C4	>	PD3			//Keypad COLUMN 4 (not used on small size)
	R1	>	PC1			//Keypad ROW 1
	R2	>	PC4			//Keypad ROW 2
	R3	>	PC3			//Keypad ROW 3
	R4	>	PC5			//Keypad ROW 4
	
- LCD Screen (Built in - pins from documentation)
	SDO		>	PF8		//Output from LCD for SPI	Not used, can be left
	LED		>	3.3V	//Backlight	
	SCK		>	PF7		//SPI clock	
	SDI		>	(MOSI)	//PF9	SPI master output	
	D/C		>	PD13	//Data/Command register	
	RESET	>	PD12	//Reset LCD	Not used on discovery board
	CS		>	PC2		//Chip select for SPI	
	GND		>	GND		//Ground	
	VCC		>	3.3V	//Positive power supply
	
- MF RC522 (RFID Reader)
	CS(SDA)	>	PG2		//Chip select for SPI
	SCK		>	PB3		//Serial Clock for SPI
	MISO	>	PB4		//Master In Slave Out for SPI
	MOSI	>	PB5		//Master Out Slave In for SPI
	GND		>	GND		//Ground
	VCC		>	3.3V	//3.3V power
	RST		>	3.3V	//Reset pin
- SERVO
	PWM		>	PA5

## Tools 
Keil uVision v5.25.2.0

STM32F429 32BIT Cortex M4 MCU with 2,4" QVGA TFT LCD display

## How to compile
1. Download repository
2. Compile
3. Have fun

### Future improvements
You found something that we could improve? 

Make issue and we maybe try to fix it ;)

### Attributions 
All Libraries by Tilen Majerle 


More information and documentation here > http://stm32f4-discovery.net

### License 
MIT

### Credits
Krzysztof Wieczorek <krzysiu_1996@o2.pl>

Jakub Werwiński <werwa999@gmail.com>

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra
