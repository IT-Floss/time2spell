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
int read_LCD_buttons() {
  adc_key_in = analogRead(0);      // read the value from the sensor
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result

  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 155)  return btnUP;
  if (adc_key_in < 300)  return btnDOWN;
  if (adc_key_in < 455)  return btnLEFT;
  if (adc_key_in < 700)  return btnSELECT;

  return btnNONE;  // when all others fail, return this...
}

// Software variables
int time2talk = 40;
int time2ask = 15;
int timeNow = 0; //actual time in minutes
int timePas = -1; //actual time in minutes
int time2change = 0;
int progressBar = 0; //Q chars
String txtMsg = "";
int aux = 0;

void setup() {
  // inicializar display LCD en 16 columnas, 2 filas
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   time2spell  ");
  analogWrite(10, 128); //set backlight
}

void loop() {
  timeNow = millis() / 60000; // divided by 60000 for convert to minutes. decrease to speed testing

  if ( timeNow != timePas ) { //each minute do:
    lcd.setCursor(0, 0);
    lcd.print(timeNow);

    txtMsg = time2talk - timeNow;
    txtMsg = " " + txtMsg;

    lcd.setCursor(16 - txtMsg.length() , 0);
    lcd.print(txtMsg);
  }
  timePas = timeNow;

  // draw progression Bar
  if ( timeNow > time2change ) {
    lcd.setCursor(progressBar, 1); // move cursor to second line, and progress char
    lcd.print(char(255));      // print progress char

    progressBar++;
    time2change = progressBar * time2talk / 16; //new threshold
  }

  if ( timeNow > time2talk ) { // what do when time is over
    lcd.setCursor(0, 0);
    lcd.print("  charm's over  ");
    lcd.setCursor(0, 1);
    lcd.print("becoming pumpkin");
    while (true) {
      delay(100000);
    }
  }

  /*
    switch (lcd_key)               // depending on which button was pushed, we perform an action
    {
    case btnRIGHT:
  	  {
        lcd.print("RIGHT    ");
        break;
      }
    case btnLEFT:
  	  {
        lcd.print("LEFT   ");
        break;
      }
    case btnUP:
  	  {
        lcd.print("UP     ");
        break;
      }
    case btnDOWN:
  	  {
        lcd.print("DOWN   ");
        break;
      }
    case btnSELECT:
  	  {
        lcd.print("SELECT ");
        break;
      }
  	       case btnNONE:
       {
       lcd.print("NONE  ");
       break;
       }

    }
    if (lcd_key != btnNONE) {
  	lcd.print(adc_key_in);
    }
  */
}
