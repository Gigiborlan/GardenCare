const char readMoistureSensor = '1';
const char turnLampOn = '2';
const char turnLampOff = '3';
const char turnPumpOn = '4';

const int moistureSensorPin = A0;
const int lampPin = 12;
const int pumpPin = 13;
const int moisutreLimit = 300;

unsigned long pumpTurnedOnTime = 0;
unsigned long currentTime = 0;
unsigned long lampTurnedOnTime = 0;
unsigned long lampTurnedOffTime = 0;
const unsigned long pumpTotalTimeOn = 3000;
const unsigned long lampTotalTimeOn = 36000000; //18h
const unsigned long lampTotalTimeOff = 21600000; //6h

//Test values
//const unsigned long pumpTotalTimeOn = 1000; //1s
//const unsigned long lampTotalTimeOn = 5000; //4s
//const unsigned long lampTotalTimeOff = 5000; //2s

bool lampStatus = false;

int moistureSensorValue = 0;
char rasberryComand = 0;

void initializeLamp(){
  digitalWrite(lampPin, HIGH);
  lampTurnedOnTime = millis();
  Serial.println("Lamp turned on");
  lampStatus = true;
}

bool shouldTurnLampOn(){
  if(lampStatus == false){
    currentTime = millis();
    if ( currentTime - lampTurnedOffTime >= lampTotalTimeOff ){
      lampStatus = true;
      lampTurnedOnTime = millis();
      return true;
    }
  }
  return false;
}

bool shouldTurnLampOff(){
  if(lampStatus == true){
    currentTime = millis();
    if ( currentTime - lampTurnedOnTime >= lampTotalTimeOn ){
      lampStatus = false;
      lampTurnedOffTime = millis();
      return true;
    }
  }
  return false;
}

bool shouldTurnPumpOn(){
  moistureSensorValue = analogRead(moistureSensorPin);
  Serial.print("Moisture: ");
  Serial.println(moistureSensorValue);
  
  if ( moistureSensorValue > moisutreLimit ){
    pumpTurnedOnTime = millis();
    return true;
  }
  return false;
}


bool shouldTurnPumpOff(){
  if ( pumpTurnedOnTime != 0 ){
    currentTime = millis();
    if ( currentTime - pumpTurnedOnTime >= pumpTotalTimeOn ){
      pumpTurnedOnTime = 0;
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(lampPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  initializeLamp();
}

void loop() { 
  if (shouldTurnLampOn() == true ) {
    digitalWrite(lampPin, HIGH);
    Serial.println("Lamp turned on");
    
    //Pump turns on along with lights turn on
    if ( shouldTurnPumpOn() == true ) {
      digitalWrite(pumpPin, HIGH);
      Serial.println("Pump turned on");
    }
  }
  
  if (shouldTurnLampOff() == true ) {
    digitalWrite(lampPin, LOW);
    Serial.println("Lamp turned off");
  }

  if ( shouldTurnPumpOff() == true ){
   digitalWrite(pumpPin, LOW);
   Serial.println("Pump turned off");
  }

}
