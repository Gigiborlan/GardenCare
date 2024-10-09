const char readMoistureSensor = '1';
const char turnLampOn = '2';
const char turnLampOff = '3';
const char turnPumpOn = '4';

const int moistureSensorPin = A0;
const int lampPin = 12;
const int pumpPin = 13;

unsigned long pumpTurnedOnBeginTime = 0;
unsigned long currentTime = 0;
const unsigned long pumpTotalTimeOn = 3000;

int moistureSensorValue = 0;
char rasberryComand = 0;

bool shouldTurnPumpOff(){
  if ( pumpTurnedOnBeginTime != 0 ){
    currentTime = millis();
    if ( currentTime - pumpTurnedOnBeginTime >= pumpTotalTimeOn ){
      pumpTurnedOnBeginTime = 0;
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(lampPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
}

void loop() { 
  if (Serial.available() > 0) {
    rasberryComand = Serial.read();
    if (rasberryComand == readMoistureSensor ) {
      moistureSensorValue = analogRead(moistureSensorPin);
      Serial.println(moistureSensorValue);
    }
    if (rasberryComand == turnLampOn ) {
      digitalWrite(lampPin, HIGH);
      Serial.println("Lamp turned on");
    }
    if (rasberryComand == turnLampOff ) {
      digitalWrite(lampPin, LOW);
      Serial.println("Lamp turned off");
    }
    if (rasberryComand == turnPumpOn ) {
      digitalWrite(pumpPin, HIGH);
      pumpTurnedOnBeginTime = millis();
      Serial.println("Pump turned on");
    }
  }
  
  if ( shouldTurnPumpOff() == true ){
   digitalWrite(pumpPin, LOW);
   Serial.println("Pump turned off");
  }

}
