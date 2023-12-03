/*******************************************************************************

*******************************************************************************/

//Libraries:
#include <CapacitiveSensor.h>

//Capacitive Sensors:
//Sensor A:
CapacitiveSensor sensorA = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin
long measurementA = 0; //reading
long measurementALow = 0; //calibrated min
long measurementAHigh = 0; //calibrated max

//Sensor B:
CapacitiveSensor sensorB = CapacitiveSensor(9,7); //1M resistor between pins 9 & 7, pin 7 is sensor pin
long measurementB = 0; //reading
long measurementBLow = 0; //calibrated min
long measurementBHigh = 0; //calibrated max

//Sliding brightness LEDs, PWM duty cycles
#define slide1 3 //cluster 1
int duty1 =0;
#define slide2 6 //cluster 2
int duty2 =0;

//Static brightness BLINKING LEDs
int blinks[] = {5,8,10,11,12,13}; //Pins
int blinkClusters = 6; // Number of clusters (size of blinks[])
int blinkStates[] = {LOW,LOW,LOW,LOW,LOW,LOW}; //Cluster states 
long blinkIntervals[] = {0,0,0,0,0,0}; //Cluster blink intervals

//Timer variables used to determine blink behaviour
unsigned long previousMillis[] = {0,0,0,0,0,0}; 
unsigned long currentMillis;

//SETUP: RUNS ONCE
void setup() {
   Serial.begin(57600);

  //sliding LED pin modes
  pinMode(slide1, OUTPUT);
  pinMode(slide2, OUTPUT);

  //blinking LED pin modes
  for(int i=1; i< blinkClusters+1; i++){
    pinMode(blinks[i-1], OUTPUT);
    digitalWrite(blinks[i-1], LOW);
    blinkIntervals[i-1] = random(100) + 5000/i; // variating intervals within array of clusters
  }
}

void loop() {
  currentMillis = millis(); // timer to indicate blink intervals
    
  //Accessing Sensor A
  measurementA =  sensorA.capacitiveSensor(30); //Sensor A reading
  map(measurementA, measurementALow, measurementAHigh, 0, 255); //Scaling for duty cycle 1
  duty1 = measurementA; // Duty cycle 1 (brightness) varies from sensor A input
  // Serial.println();
  // Serial.print("Sensor A: ");
  // Serial.print(measurementA);

  //Accessing Sensor B
  measurementB =  sensorB.capacitiveSensor(30); //Sensor B reading
  map(measurementB, measurementBLow, measurementBHigh, 0, 255); //Scaling for duty cycle 2
  duty2 = measurementB; // Duty cycle 2 (brightness) varies from sensor B input
  // Serial.println();
  // Serial.print("Sensor B: ");
  // Serial.print(measurementB);

  //long measurementTotal = (measurementA + measurementB)/2;

//Blink cluster assessment
  for (int i=0; i<blinkClusters; i++){
    if(currentMillis - previousMillis[i] >= blinkIntervals[i]){
      previousMillis[i] = currentMillis;
      if(blinkStates[i] == LOW){
        blinkStates[i] = HIGH; //activate cluster based on intervals
      }else{
        blinkStates[i] = LOW;
      }
    }

    digitalWrite(blinks[i], blinkStates[i]); // blink cluster state application
    // Serial.println();
    // Serial.print("Blink ");
    // Serial.print(blinks[i]);
    // Serial.print(" State: ");
    // Serial.print(blinkStates[i]);
    // delay(100);
  }

  //Writing to liding brightness LEDs
  analogWrite(slide1, duty1);
  analogWrite(slide2, duty2);
 
 
  //delay(500);
  
}
