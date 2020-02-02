#include <Arduino.h>
#include <Wire.h>
//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 8;
const int HOT_PIN = 4;
const int COLD_PIN = 7;
const int DRY_PIN = 2;
const int LOCK_PIN = 13;
//Economy mode voltage less than 0.1V
//Deluxe mode voltage 2.45V to 2.55V
//Super Deluxe mode voltage greater than 4.9V
int press = 0;
int value = 0;
float convert = 0.0;
enum State {
  idle,
  eco,
  del,
  supdel,
};

State currentState = idle;

void setup() {
  Serial.begin(9600);
  pinMode(POT_PIN, INPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(COLD_PIN,OUTPUT);
  pinMode(HOT_PIN,OUTPUT);
  pinMode(DRY_PIN,OUTPUT);
  pinMode(LOCK_PIN,OUTPUT);
  analogReference(DEFAULT);
}

void loop() {
  currentState = nextState(currentState);
}

State nextState(State state){
  switch (state){
    case idle:
      //Serial.println("idle");
      digitalWrite(COLD_PIN,LOW);
      digitalWrite(HOT_PIN,LOW);
      digitalWrite(DRY_PIN,LOW);
      digitalWrite(LOCK_PIN,LOW);
      value = analogRead(POT_PIN);
      convert = value*(5.0/1023.0);
      press = digitalRead(BUTTON_PIN);
      Serial.println(convert);
      if(convert < 0.1 && press == LOW){
          state = eco;
      }else if(convert > 2.40 && convert < 2.60 && press == LOW){
          state = del; 
      }else if(convert > 4.95 && press == LOW){
          state = supdel;
      }else{
        state = idle;
      }
      break;
    case eco:
      Serial.println("eco");
      digitalWrite(COLD_PIN,HIGH);
      digitalWrite(LOCK_PIN,HIGH);
      delay(5000);
      digitalWrite(COLD_PIN,LOW);
      digitalWrite(DRY_PIN,HIGH);
      value = analogRead(POT_PIN);
      convert = value*(5.0/1023.0);
      if(convert > 0.1) { // delux mode dry
        Serial.println("eco water: deluxe dry");
        delay(7000);
      } else {
        Serial.println("deluxe water: eco dry");
        delay(2000);
      }
      state = idle;
      
      break;
    case del:
      Serial.println("del");
      digitalWrite(HOT_PIN,HIGH);
      digitalWrite(LOCK_PIN,HIGH);
      delay(7000);
      digitalWrite(HOT_PIN,LOW);
      digitalWrite(DRY_PIN,HIGH);
     // digitalWrite(LOCK_PIN,HIGH);
      value = analogRead(POT_PIN);
      convert = value*(5.0/1023.0);
      if(convert < 0.1) { // eco mode dry
      //digitalWrite(LOCK_PIN,HIGH);
        Serial.println("deluxe water: eco dry");
        delay(2000);
      } else {
        Serial.println("deluxe water: deluxe dry");
        delay(7000);
      }
      state = idle;
      
      break;
    case supdel:
      Serial.println("super deluxe water: hot water");
      digitalWrite(HOT_PIN,HIGH);
      digitalWrite(LOCK_PIN,HIGH);
      delay(7000);
      value = analogRead(POT_PIN);
      convert = value*(5.0/1023.0);
      if(convert < 0.1) { // eco mode dry
        //turn off hot water, and turn on dry in eco mode 
        digitalWrite(HOT_PIN,LOW);
        digitalWrite(DRY_PIN,HIGH);
        Serial.println("super deluxe water: eco dry");
        delay(2000);
      } else {
        //turn on , and turn on dry in eco mode 
        digitalWrite(COLD_PIN,HIGH);
        Serial.println("super deluxe water: medium water");
        delay(7000);
        digitalWrite(HOT_PIN,LOW);
        digitalWrite(COLD_PIN,LOW);
        digitalWrite(DRY_PIN,HIGH);
        //digitalWrite(LOCK_PIN,HIGH);
        Serial.println("super deluxe water: deluxe dry");
        delay(7000);
      }
      state = idle;
      
      break;
    }
    return state;
}
