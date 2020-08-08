//Hack against covid
//Codezoned
//interfacing PIR sensors with arduino

//defining Global Variables
const byte BUTTON=2; // our button pin
const byte LED=7; // LED (built-in on Uno)
#include <LiquidCrystal.h>
LiquidCrystal lcd (13,12,11,10,9,8);
const int buzzerPin=3;
 
unsigned long buttonPushedMillis; // when button was released
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 2500; // wait time to turn on LED
unsigned long turnOffDelay = 5000; // turn off LED after this time
bool ledReady = false; // flag for when button is let go
bool ledState = false; // LED state (for LED is on or not)
 
void setup() {
 pinMode(BUTTON, INPUT_PULLUP);
 pinMode(LED, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
 digitalWrite(LED, LOW);
 lcd.begin (16,2);
}
 
void loop() {
 // get the time at the start of this loop()
 unsigned long currentMillis = millis(); 
 lcd.setCursor(0,0);
 lcd.print("UV-C System"); //printing on LCD
 int pirstate=digitalRead(1);
 // check the button
 if (digitalRead(BUTTON) == LOW) {
  // update the time when button was pushed
  buttonPushedMillis = currentMillis;
  ledReady = true;
 }
  
 // make sure this code isn't checked until after button has been let go
 if (ledReady) {
   //this is typical millis code here:
   if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
     // okay, enough time has passed since the button was let go.
     digitalWrite(LED, HIGH);
     // setup our next "state"
     ledState = true;
     tone(buzzerPin,2000,2000);
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Sanitizing_area");
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
     // wait for next button press
     ledReady = false;
   }
 }
  
 // see if we are watching for the time to turn off LED
 if (ledState) {
   // okay, led on, check for now long
   if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay or pirstate==HIGH) {
     ledState = false;
     tone(buzzerPin,2000,4000);
     lcd.setCursor(0,1);
     lcd.print("Sanitization_stoped");
     digitalWrite(LED, LOW);
   }
 }
} 
