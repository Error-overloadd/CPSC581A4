
#include "DHT.h"
#define DHTPIN 24     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;
int trigPin = 9;    // TRIG pin
int echoPin = 8;    // ECHO pin
signed short minutes=4, secondes=59;
float duration_us, distance_cm;
bool timeflag=true;
char timeline[16];

bool servowork= false;
void setup() {

  lcd.init(); // initialize the lcd
  lcd.backlight();
  servo.attach(12);
  servo.write(0);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);

  dht.begin();

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("4 times a day ");
  lcd.setCursor(0, 1);
  sprintf(timeline,"%0.2d mins %0.2d secs", minutes, secondes);
  lcd.print(timeline);
  delay(1000);

  
   if (secondes >= 0 && minutes>=0 && timeflag==true){
     secondes--;
     if (secondes == 0 && minutes >0) {
        minutes --;
       
       
       secondes = 59;
     }
     if (secondes == 0 && minutes == 0) {
         servo.write(90);   
          timeflag = false;
        }
     
  }
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
 Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  //delay(500);
 if(distance_cm<=6){
      Setreset(); 
      Serial.print("This works");
   }
  // if(minutes==0 && secondes == 0){
    
  //   delay(1000);
    
   
  // //exit(0);

  //  // continue;
  // }


}

void Setreset(){
 
    servo.write(0);
    minutes=4, secondes=59;
    delay(1000);
    timeflag=true;
  }






