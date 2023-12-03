/*******************************************************************************

*******************************************************************************/

// capacitive sensing includes
#include <CapacitiveSensor.h>

// capacitive sensing constant
CapacitiveSensor sensorA = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin
CapacitiveSensor sensorB = CapacitiveSensor(8,7); 
//CapacitiveSensor sensorC = CapacitiveSensor(13,12); 

//sliding brightness LEDs
#define slide1 3
#define slide2 6

 int duty1 =0;
 int duty2 =0;

void setup() {
   Serial.begin(115200);
  pinMode(slide1, OUTPUT);
  pinMode(slide2, OUTPUT);
  // pinMode(LED2, OUTPUT);
  // pinMode(LED3, OUTPUT);
  // digitalWrite(LED2, LOW);
  // digitalWrite(LED3, LOW);

}

void loop() {
  long measurementA =  sensorA.capacitiveSensor(30);
  duty1 = measurementA/255;
  Serial.println();
  Serial.print("Sensor A: ");
  Serial.print(duty1);

  long measurementB =  sensorB.capacitiveSensor(30);
  duty2 = measurementB/255;
  Serial.println();
  Serial.print("Sensor B: ");
  Serial.print(duty2);

analogWrite(slide1, duty1);
analogWrite(slide2, duty2);
  //delay(500);
  
}
