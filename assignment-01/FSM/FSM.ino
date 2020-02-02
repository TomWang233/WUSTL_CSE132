/*
   FSM assignment
*/
// Team: Tom Wang, Nikki Xie

#include <Arduino.h>
#include <Wire.h>

enum State {
  up0,        
  up1,        
  up2,        
  up3,        
  up4,        
  up5,        
  up6,        
  up7,
  dn0,
  dn1,
  dn2,
  dn3,
  dn4,
  dn5,
  dn6,
  dn7,        
};

State currentState = up0;

bool bit1, bit2, bit3;
bool press = false;
String stateNames[] = {"up0","up1","up2","up3","up4","up5","up6","up7","dn0","dn1","dn2","dn3","dn4","dn5","dn6","dn7",};

void setup() {
  Serial.begin(9600);
}

void loop() {
  press = checkReverse();
  currentState = nextState(currentState);
  delay(1000);
}


State nextState(State state){
  switch (state) {
    case up0:              
      bit1 = 0;       
      bit2 = 0;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn7; 
      }else{
        pprint(state);
        state = up1;
      }         
      break;                      
   
    case up1:               
      bit1 = 1;
      bit2 = 0;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn0; 
      }else{
        pprint(state);
        state = up2;
      }  
      break;

    case up2:
      bit1 = 0;
      bit2 = 1;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn1; 
      }else{
        pprint(state);
        state = up3;
      }  
      break;

    case up3:
      bit1 = 1;
      bit2 = 1;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn2; 
      }else{
        pprint(state);
        state = up4;
      }  
      break;

    case up4:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn3; 
      }else{
        pprint(state);
        state = up5;
      }  
      break;

    case up5:
      bit1 = 1;
      bit2 = 0;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn4; 
      }else{
        pprint(state);
        state = up6;
      }  
      break;

    case up6:
      bit1 = 0;
      bit2 = 1;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn5; 
      }else{
        pprint(state);
        state = up7;
      }  
      break;

    case up7:
      bit1 = 1;
      bit2 = 1;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = dn6; 
      }else{
        pprint(state);
        state = up0;
      }  
      break;

    case dn7:
      bit1 = 1;
      bit2 = 1;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up0; 
      }else{
        pprint(state);
        state = dn6;
      }  
      break;

    case dn6:
      bit1 = 0;
      bit2 = 1;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up7; 
      }else{
        pprint(state);
        state = dn5;
      }  
      break;

    case dn5:
      bit1 = 1;
      bit2 = 0;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up6; 
      }else{
        pprint(state);
        state = dn4;
      }  
      break;

    case dn4:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up5; 
      }else{
        pprint(state);
        state = dn3;
      }  
      break;

    case dn3:
      bit1 = 1;
      bit2 = 1;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up4; 
      }else{
        pprint(state);
        state = dn2;
      }  
      break;

    case dn2:
      bit1 = 0;
      bit2 = 1;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up3; 
      }else{
        pprint(state);
        state = dn1;
      }  
      break;

    case dn1:               
      bit1 = 1;
      bit2 = 0;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up2; 
      }else{
        pprint(state);
        state = dn0;
      }  
      break;

    case dn0:              
      bit1 = 0;       
      bit2 = 0;
      bit3 = 0;
      if(press){
        pprint(state);
        Serial.println("--Reverse--");
        state = up1; 
      }else{
        pprint(state);
        state = dn7;
      }         
      break;
  }
  return state;
}

bool checkReverse(){
  char reverse = Serial.read();
  if(reverse != -1){
    return true;
  }else{
    return false;
  }
}

void pprint(State state) {
  Serial.print(stateNames[state]);
  Serial.print("  :  ");
  Serial.print(bit3);
  Serial.print(bit2);
  Serial.println(bit1);
}
