/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Tom Wang
 *  WUSTL Key: chenyang.wang
 *  
 *  and if two are partnered together
 *  
 *  Name: Nikki Xie 
 *  WUSTL Key: n.xie
 */
 
#define FILTER_COUNTS 10
float temperatures[FILTER_COUNTS];
int count = 0;
int startup = 0;

const int Sensor = A1;
const int Cricket = 4;
int value = 0;
float total = 0.0;
float temp = 0.0;
float average = 0.0;
int LED = LOW;

const unsigned long period = 250;
float chirp = 0;
unsigned long endTime = 0;
unsigned long now = 0;
unsigned long previousMillis = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(Cricket,OUTPUT);
  pinMode(Sensor,INPUT);
  for (int i = 0; i < FILTER_COUNTS; i++) {
    temperatures[i] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  now = millis();
  
  if(now >= endTime){
    chirp = readTemp();
    endTime = now + period;
    startup = startup + 1;
  }
  
  if(now - previousMillis >= chirp){
    previousMillis = now;
    if (LED == LOW) {
      LED = HIGH;
    } else {
      LED = LOW;
    }
    if(startup >= 11){
    digitalWrite(Cricket, LED);
  }
  }
}

float readTemp() {
   total = total - temperatures[count];
   value = analogRead(Sensor);
   temp = 25 + (value*(1.1/1023.0) - 0.75)*100;
   temperatures[count % FILTER_COUNTS] = temp;
   total = total + temperatures[count];
   count += 1;
   if (count >= FILTER_COUNTS) {
    count = 0;
   }
   average = total / FILTER_COUNTS;
   if(startup >= 11){
   Serial.print(temp);
   Serial.print(",");
   Serial.println(average);
   return (1/((7*average - 30)/60))* (1000);
   }
   return 0;
   }
