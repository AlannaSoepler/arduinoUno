//Include Libraries
#include <LiquidCrystal.h>

// Global variables and defines
#define LCD_PIN_RS  7
#define LCD_PIN_E 6
#define LCD_PIN_DB4 2
#define LCD_PIN_DB5 3
#define LCD_PIN_DB6 4
#define LCD_PIN_DB7 5
#define LED_PIN_G 10
#define LED_PIN_Y 11
#define LED_PIN_R 12
#define SOUND 13
#define NOTE_FS3 185
// Global variables and defines
#define SOILMOISTURE_5V_PIN_SIG A3
// Object Initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);

void setup() {
//spesified the dementioned of the LCD screen   
lcd.begin(16, 2);
pinMode(LED_PIN_G, OUTPUT);
pinMode(LED_PIN_Y, OUTPUT);
pinMode(LED_PIN_R, OUTPUT);
pinMode(SOUND, OUTPUT);
//data rate in bytes
Serial.begin(57600);
}
void loop() {
//print text in serial monotor  
Serial.print("Moisture Sensor Value:");
//store data from Soil Moisture sensor
int result = analogRead(A3);
//print the data in the serial monotor
Serial.println(result);
//wate to collect result for 5 sec
delay(5000);

//Check if the data is more/equal than 0 and less/equal then 200
if (result >= 0 && result <= 200){
    //Turn on LED light
    digitalWrite(LED_PIN_G, HIGH); 
  //display this on the LCD screen
    lcd.print("moisture level = ");
    //At row 1 and colume 0
    lcd.setCursor(0,1);
    //Display this text
    lcd.print("Dry");
    //At row 2 and colume 0
    lcd.setCursor(0,2);
    //waite for 4 sec
    delay(4000);
    //Turn off LED
    digitalWrite(LED_PIN_G, LOW);
    //Clear everything from the LCD screen
    lcd.clear();
    }else if(result > 200 && result <= 400){
        digitalWrite(LED_PIN_Y, HIGH);
        lcd.print("moisture level = ");
        lcd.setCursor(0,1);
        lcd.print("Damp");
        lcd.setCursor(0,2);
        delay(4000);
        digitalWrite(LED_PIN_Y, LOW);
        lcd.clear();
        }else if(result > 400){
            digitalWrite(LED_PIN_R, HIGH);
            //output the frequency of the Note_G4 value
            tone(SOUND, NOTE_FS3);
            lcd.print("moisture level = ");
            lcd.setCursor(0,1);
            lcd.print("Liquid");
            lcd.setCursor(0,2);
            delay(4000);
            //No Sound
            noTone(SOUND);
            digitalWrite(LED_PIN_R, LOW);
            lcd.clear();
          }
}
