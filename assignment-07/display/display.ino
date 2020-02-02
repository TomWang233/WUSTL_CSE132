/* display
 *  
 *  CSE 132 - Assignment 7
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Tom Wang
 *  WUSTL Key: chenyang.wang
 *  
 *  Name: Nikki Xie
 *  WUSTL Key: n.xie
 *  
 */

#include "font.h"
int row[] = {2,3,4,5,6,7,8};
int col[] = {9,10,11,12,13,9,10,11,12};
int count = 0x20;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;
unsigned long record = 0;


void setup ()
{
  // insert code here as needed
  Serial.begin(9600);
  //delay(5000);
  pinMode(2,OUTPUT);//row
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);//row
  pinMode(9,OUTPUT);//column
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);//column
  pinMode(A0,INPUT);//up button
  pinMode(A1,INPUT);//down button
}

void loop ()
{
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  // insert code here as needed
  for(int i = 0; i<=4; i++){
      digitalWrite(col[i],LOW);
      digitalWrite(col[i+1],HIGH);
      digitalWrite(col[i+2],HIGH);
      digitalWrite(col[i+3],HIGH);
      digitalWrite(col[i+4],HIGH);
      byte ledState = font_5x7[count-0x20][i];
      drawChar(ledState);
    }

  int reading = analogRead(A0);
  int reading2 = analogRead(A1);
  //Serial.println(reading);
  if(reading == 1023){
    if (count == 0x7f){
      count = 0x20;
    }else{
      record = millis();
      if(record - lastDebounceTime > debounceDelay){
        count++;
        lastDebounceTime = millis();
      }
  }
  }

  if(reading2 == 1023){
    if(count == 0x20){
      count = 0x7f;
    }else{
      record = millis();
      if(record - lastDebounceTime > debounceDelay){
        count--;
        lastDebounceTime = millis();
      }
  }
  }



}
  

void drawChar(byte input){
  for(int j = 0; j<=6; j++){
      digitalWrite(row[j],((input>>(7-j)) & 0x01));
      delay(0.03);
    }
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
