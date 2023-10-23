# MyntRaknare

## Beskrivning
Programmet "MyntRäknaren" ger användaren information om mynten i deras sparbössa. 4 mynt tillåts - enkronor, femkronor, tiokronor och tjugofemkronor. Efter varje mynt visas en total summa av pengarna, antalet mynt och statistik om myntvarianterna. Finns även möjlighet att återställa räknaren till noll, exempelvis om ägaren byts och på/av funktioner. 

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

* clang-format - formattering
* Makefile

## Arduino 
Den fysiska delen är uppbyggt kring ett Arduino-bräde och inkluderar en LCD-skärm samt sex knappar. Dessa komponenter samverkar för att skapa en fungerande mynträknare.