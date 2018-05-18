# Overview 
[PL] 
Ile razy miałeś tak, że chciałeś zabezpieczyć drogocenne przedmioty czy pieniądze przez niepowołanymi rękami. Skarpety? No jest to jakieś wyjście ale trzymanie pieniędzy tam raczej mało uchroni je przed kradzieżą. Banki? Jesteś osobą(typowym Polakiem), co woli mieć kontrole nad pieniądzem? Właśnie myśląc o takich ludziach stworzyliśmy nasz projekt! 
Nasz projekt jest to sejf wykorzystujący technologię RFID oraz awaryjne otwieranie, w przypadku braku karty lub breloka,  czyli klasyczny pin, co oznacza, że zawsze masz dostęp do swoich skarbów. 

[EN]

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
