/*
Description:


Using LCD Keypad Field v1.0 https://www.dfrobot.com/wiki/index.php/Arduino_LCD_KeyPad_Shield_(SKU:_DFR0009)

Listado de pines utilizados del Arduino:
4: LCD DB4 (pin 11 LCD)
5: LCD DB5 (pin 12 LCD)
6: LCD DB6 (pin 13 LCD)
7: LCD DB7 (pin 14 LCD)
8: LCD RS (pin 4 LCD) 
9: LCD Enable (pin 6 LCD)
10: LCD BackLight
A0: read buttons

*/

// Librerias para manejo de LCD y sensor de humedad DHT11
#include <LiquidCrystal.h>

//const for buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int lcd_key     = 0;
int adc_key_in  = 0;

// inicializar libreria para display LCD con los pines de Arduino
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/

 return btnNONE;  // when all others fail, return this...
}

void setup() { 

// inicializar display LCD en 16 columnas, 2 filas
  lcd.begin(16, 2);
} 

void loop() {
 lcd.setCursor(3,0);            // move cursor to first line
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
 lcd.print(millis()/1000);      // display seconds elapsed since power-up

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
     
 }
lcd.print(adc_key_in); 

}





