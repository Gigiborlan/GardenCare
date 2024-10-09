const char readMoistureSensor = '1';
const char turnLampOn = '2';
const char turnLampOff = '3';
const char turnPumpOn = '4';

const int moistureSensorPin = A0;

unsigned long pumpTurnedOnBeginTime = 0;
unsigned long currentTime = 0;
const unsigned long pumpTotalTimeOn = 3000;

int moistureSensorValue = 0;
char rasberryComand = 0;

void setup() {
  Serial.begin(9600);
}

void loop() { 
  if (Serial.available() > 0) {
    rasberryComand = Serial.read();
    if (rasberryComand == readMoistureSensor ) {
      moistureSensorValue = analogRead(moistureSensorPin);
      Serial.println(moistureSensorValue);
    }
    if (rasberryComand == turnLampOn ) {
      //digital write
      Serial.println("Lamp turned on");
    }
    if (rasberryComand == turnLampOff ) {
      //digital write
      Serial.println("Lamp turned off");
    }
    if (rasberryComand == turnPumpOn ) {
      //digital write
      pumpTurnedOnBeginTime = millis();
      Serial.println("Pump turned on");
    }
  }
  
  
  if ( pumpTurnedOnBeginTime != 0 ){
    currentTime = millis();
    if ( currentTime - pumpTurnedOnBeginTime >= pumpTotalTimeOn ){
      //digital write
      pumpTurnedOnBeginTime = 0;
      Serial.println("Pump turned off");
    }
  }

}
