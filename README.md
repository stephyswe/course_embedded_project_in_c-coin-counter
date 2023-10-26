# MyntRaknare

## Installation
Klona repo "git clone" till hårddisk. Öppna projekt i VSCODE från hårddisk med "code .". Skapa en .hex
file genom att klicka på "Makefile" tillägg och "Run" ikonen. Efter .hex fil är skapat öppna 
en webbläsare till wokwi länk, tryck "cancel", tryck sedan "F1" för menu och välj "upload firmware 
and start simulation".

## Presentation
Presentationsfil presentation.mp4 visar projektet som körs i wokwi med beskrivning och kodexempel

## Ritningar

![MoneyBox for Arduino Uno](https://i.imgur.com/YyqhGZ6.png)
![Added Coin](https://i.imgur.com/KVUgFtc.png)
![Coin Statistics](https://i.imgur.com/NNJVcug.png)

## Hårvara och Stift anslutningar

### Hårdvara

| Enhet            | Antal    | Anteckningar
| ---------------- | -------- | ---------------------------- |
| Arduino Uno R3   | 1        |                              |
| 12mm Push button | 6        | Yellow, Gold, Green, Gray    |
| 16x02 LCD Monitor| 1        |                              |


### Stift anslutningar

| Arduino Pin | Enhet        |
| ----------- | -------------|
| GND         | LCD 05 (RW)  |
| GND         | LCD 01 (VS)  |
| 13          | Button Toggle|
| 12          | Button Reset |
| 11          | Button 25    |
| 10          | Button 10    |
| 9           | Button 05    |
| 8           | Button 01    |
| 7           | LCD 14 (D7)  |
| 6           | LCD 13 (D6)  |
| 5           | LCD 12 (D5)  |
| 4           | LCD 11 (D4)  |
| 1           | LCD 06 (E)   |
| 0           | LCD 04 (RS)  |
| 5V          | LCD 02 (SVD) |


## Beskrivning
Programmet "MyntRäknaren" ger användaren information om mynten i deras sparbössa. 4 mynt tillåts - enkronor, femkronor, tiokronor och tjugofemkronor. Efter varje mynt visas en total summa av pengarna, antalet mynt och statistik om myntvarianterna. Finns även möjlighet att återställa räknaren till noll, exempelvis om ägaren byts och på/av funktioner. 

* Wokwi (fysisk utveckling): https://wokwi.com/projects/379402088569472001

## Funktionalitet
grundläggande funktioner:
- Lägga till mynt och uppdatera totalbeloppet
- Kontroll av mynt som läggs in (öka totalen med 1 för varje enkrona, 10 för varje tiokrona, 5 för varje femkrona)
- Återställa räknaren till noll
- Aktivera eller inaktivera
- Användargränssnitt att interagera med

Framtida utökningar:
- Användarvänlighet och gränssnittsförbättringar.
- Felhantering, tester i C++ och validering.

## Användning
Användaren väljer en av fyra knappar som motsvarar olika myntvärden för att lägga till mynt i räknaren. Efter varje mynttillägg visas relevant information och statistik efter en kort fördröjning. Dessutom finns det knappar för återställning och inaktivering av systemet 

## Programmet
Programmet börjar i main() med två funktioner: initialize_hardware() och initialize_message(). Här påbörjas programmet med startmeddelande och initialiserar nödvändig hårdvara.

Main_loop() ansvarar att övervaka knapptryckningar. Knapparna 1-4 lägger till olika mynt via button_click() och update_coin_category(), knapp 5 för återställning via system_reset() och knapp 6 kör system_toggle() som aktivera eller inaktivera systemet. Efter ett mynt valts presenteras beloppet, antalet mynt i sparbössan och 4 sekudner senare med en millis funktion visas hur många mynt per kategori.

### Filer
* lcd.c (obl.)   - LCD skärm
* millis.c (obl) - tidhantering

* main     - huvudfunktion
* system.c - systemrelaterade funktioner
* button.c - hantering av knappar
* message.c - input meddelande

* clang-format - formattering
* Makefile

## Arduino 
Den fysiska delen är uppbyggt kring ett Arduino-bräde och inkluderar en LCD-skärm samt sex knappar. Dessa komponenter samverkar för att skapa en fungerande mynträknare.
