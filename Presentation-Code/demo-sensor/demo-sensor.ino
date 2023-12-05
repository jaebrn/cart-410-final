#include <CapacitiveSensor.h>

CapacitiveSensor demo = CapacitiveSensor(4,2);
long unsigned reading = 0;
#define LED 11

void setup() {
  Serial.begin(56700);
  pinMode(LED, OUTPUT);
}

void loop() {
  reading = demo.capacitiveSensor(30);
  Serial.println();
  Serial.print(reading);
  if(reading < 500){
    analogWrite(LED, 0);
  }else{
  analogWrite(LED, reading/100);
  }

}
