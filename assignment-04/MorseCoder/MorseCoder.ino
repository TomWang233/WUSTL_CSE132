#include"MorseCodes.h"

const int LED = 8;
char c_incoming;

const unsigned long duration = 500;
const unsigned long dot_time = duration;
const unsigned long dash_time = duration * 3;
const unsigned long off_time = duration;
const unsigned long between_time = duration;
const unsigned long space_time = duration * 3;
unsigned long record = 0;


String morse = "";
String processedMorse = "";
int i = 0;

enum State{
  idle,
  dot,
  dash,
  off,
  between,
  space,
};

State currentState = idle;

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  // TODO
  int int_c = (int)c;
  if(c>= 97 && c <= 122) {
    int_c -= 32;
    c = (char)int_c;
  }
  return c;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
}

void convertIncomingCharsToMorseCode() {
  if(Serial.available() > 0) {
    c_incoming = Serial.read();
    morse = morseEncode(c_incoming);
    processedMorse = processedMorse + morse;
    processedMorse = processedMorse + "!";
    //Serial.println(morse);
    //Serial.println(processedMorse);
    }
   currentState = nextState(currentState);
}

State nextState(State state){
  record = millis();
  while(i < processedMorse.length()){
    unsigned long currentTime = millis();
    switch(state){
      case idle:
          if (processedMorse[i] == '.') {
            state = dot;
          } else if (processedMorse[i] == '-') {
            state = dash;
          } else if (processedMorse[i] == ' ') {
            state = space;
          }else {
          state = idle;
          }
          break;
     
     case dot:
          digitalWrite(LED,HIGH);
          if(currentTime - record >= dot_time){
            record = millis();
            state = off;
            i++;
          }
          break;

     case dash:
          digitalWrite(LED,HIGH);
          if(currentTime - record >= dash_time){
            record = millis();
            state = off;
            i++;
          }
          break;

     case off:
          digitalWrite(LED,LOW);
          if(currentTime - record >= off_time){
            record = millis();
            if(processedMorse[i] == '.'){
              state = dot;
            }else if(processedMorse[i] == '-'){
              state = dash;
            }else if(processedMorse[i] == '!'){
              state = between;
            }else{
              state = space;
            }
          }
          break;
     
     case between:
          digitalWrite(LED,LOW);
          if(currentTime - record >= between_time){
            record = millis();
            state = off;
            i++;
          }
          break;

     case space:
          digitalWrite(LED,LOW);
          if(currentTime - record >= space_time){
            record = millis();
            state = off;
            i++; 
          }
          break;
    }
   
  }
  return state;
}
