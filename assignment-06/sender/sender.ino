int pot = A0;
int sensor = A1;
int voltage = 0;
int rawTemp = 0;

unsigned long record = 0;
unsigned long currentTime = 0;
const unsigned long duration = 1000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(DEFAULT);
  pinMode(pot, INPUT);
  pinMode(sensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  if(currentTime- record >= duration){
    record = millis();
    send();
  }
}

void send(){
  //sendDebug();
  String debug = String("Communication Start");
  int length = debug.length();
  Serial.write(0x21);
  Serial.write(0x30);
  Serial.write(length >> 8);
  Serial.write(length);
  char send_debug[length];
  debug.toCharArray(send_debug,debug.length()+1);
  for(int i = 0; i < length; i++){
    Serial.write(send_debug[i]);
  }
  //------------------//
  //sendTimeStamp();
  Serial.write(0x21);
  Serial.write(0x32);
  Serial.write(currentTime >> 24);
  Serial.write(currentTime >> 16);
  Serial.write(currentTime >> 8);
  Serial.write(currentTime);
  //------------------//
  //sendVoltage();
  voltage = analogRead(pot);
  Serial.write(0x21);
  Serial.write(0x33);
  Serial.write(voltage >> 8);
  Serial.write(voltage);
  //------------------//
  //sendTemp();
  rawTemp = analogRead(sensor);
  Serial.write(0x21);
  Serial.write(0x34);
  Serial.write(rawTemp >> 8);
  Serial.write(rawTemp );
  //------------------//
  if(voltage > 512){
    //sendError();
    String error = String("High Alarm");
    int length = error.length();
    Serial.write(0x21);
    Serial.write(0x31);
    Serial.write(length >> 8);
    Serial.write(length);
    char send_error[length];
    error.toCharArray(send_error,error.length()+1);
    for(int i = 0; i < length; i++){
      Serial.write(send_error[i]);
    }
   }
}

void sendDebug(){
 
}


void sendError(){
  
}



void sendTimeStamp(){
 
}

void sendVoltage(){
  
}

void sendTemp(){
  
}
