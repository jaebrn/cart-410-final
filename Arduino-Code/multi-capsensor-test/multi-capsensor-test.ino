/*******************************************************************************

 Bare Conductive Capacitive Proximity Sensor
 -------------------------------------------

 For Arduino boards. Use a large resistor, about 1M between pin 2 and 4 and
 connect pin 2 to a sensor, for example Electric Paint.

 Based on code by Paul Badger.

 Bare Conductive code written by Pascal Loose

 This work is licensed under a MIT license https://opensource.org/licenses/MIT

 Copyright (c) 2020, Bare Conductive

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

// capacitive sensing includes
#include <CapacitiveSensor.h>
#define LED1 3
#define LED2 5
#define LED3 6

// capacitive sensing constant
CapacitiveSensor sensorA = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin
CapacitiveSensor sensorB = CapacitiveSensor(8,7); 
CapacitiveSensor sensorC = CapacitiveSensor(13,12); 

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

}

void loop() {
  long measurementA =  sensorA.capacitiveSensor(30);
  Serial.println();
  Serial.print("Sensor A: ");
  Serial.print(measurementA);

  long measurementB =  sensorB.capacitiveSensor(30);
  Serial.println();
  Serial.print("Sensor B: ");
  Serial.print(measurementB);

  long measurementC =  sensorC.capacitiveSensor(30);
  Serial.println();
  Serial.print("Sensor C: ");
  Serial.print(measurementC);

  //delay();
  
if(measurementA > 800){
  digitalWrite(LED1, HIGH);
}else {
  digitalWrite(LED1, LOW);}

if(measurementB > 800){
  digitalWrite(LED2, HIGH);
}else {
  digitalWrite(LED2, LOW);}

if(measurementC > 800){
  digitalWrite(LED3, HIGH);
}else{
  
  digitalWrite(LED3, LOW);
}
// if(measurement>1000){
//   digitalWrite(LED3,HIGH);
// }else if(measurement>500){
//   digitalWrite(LED2, HIGH);
//   } else if(measurement>200){
//     digitalWrite(LED1, HIGH);}
// else{
//   digitalWrite(LED1, LOW);
//    digitalWrite(LED2, LOW);
//    digitalWrite(LED3, LOW);
// }
}
