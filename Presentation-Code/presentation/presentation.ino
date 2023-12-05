#include <CapacitiveSensor.h>

//State change button:
#define buttonPin A0
int buttonState = 0;
int prevButtonState = 0;
int mode = 1; // 1 = demo mode, 0 = sensor mode

//Sensors:
CapacitiveSensor sensorA = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin
long measurementA = 0; //reading

CapacitiveSensor sensorB = CapacitiveSensor(9,7); //1M resistor between pins 9 & 7, pin 7 is sensor pin
long measurementB = 0; //reading

//Sliding brightness LEDs, PWM duty cycles
#define slide1 3 //cluster 1
#define slide2 6 //cluster 2
  //Sensor Mode
  int duty1 = 0;
  int duty2 = 0;
  //Demo mode 
  int value;
  unsigned long time=0;
  int period = 2000;

//Static brightness BLINKING LEDs
int blinks[] = {5,8,10,11,12,13}; //Pins
int blinkClusters = 6; // Number of clusters (size of blinks[])
int blinkStates[] = {LOW,LOW,LOW,LOW,LOW,LOW}; //Cluster states 
long blinkIntervals[] = {0,0,0,0,0,0}; //Cluster blink intervals

//Timer variables used to determine blink behaviour
unsigned long previousMillis[] = {0,0,0,0,0,0}; 
unsigned long currentMillis = 0;
unsigned long slidePrevMillis = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(57600);

 //sliding LED pin modes
   pinMode(slide1, OUTPUT);
   pinMode(slide2, OUTPUT);
   //Blink pin modes
  for(int i=1; i< blinkClusters+1; i++){
     pinMode(blinks[i-1], OUTPUT);
     digitalWrite(blinks[i-1], LOW);
     blinkIntervals[i-1] = random(100) + 5000/i; // variating intervals within array of clusters
  }
}

void loop() {
  //DETERMINING MODE: DEMO OR SENSOR
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && prevButtonState == LOW) {
    mode++;
  } 
  mode %= 2;
  prevButtonState = buttonState;
  //MODE ASSIGNMENT
  switch (mode){
    case 0:
      sensorMode();
      break;
    case 1:
      demoMode();
      break;
    default: demoMode();
    break;
  }
 // currentMillis = millis();
}

void sensorMode(){
   Serial.println();
  Serial.print("SENSOR MODE");
   measurementA =  sensorA.capacitiveSensor(30)/1000;
    measurementB =  sensorB.capacitiveSensor(30)/1000;
    currentMillis = millis();
     if(measurementA >= 50){ //attempt at calibration.. revisit above map function
duty1 = measurementA;
  }else{
    duty1 =0;
  }
    if(measurementB >= 50){
 duty2 = measurementB; // Duty cycle 2 (brightness) varies from sensor B input
  }else{
    duty2 = 0;
  }
  for (int i=0; i<blinkClusters; i++){
    if(currentMillis - previousMillis[i] >= (blinkIntervals[i])/measurementA){
      previousMillis[i] = currentMillis;
      if(blinkStates[i] == LOW){
        blinkStates[i] = HIGH; //activate cluster based on intervals
      }else{
        blinkStates[i] = LOW;
      }
    }

    digitalWrite(blinks[i], blinkStates[i]); // blink cluster state application
      analogWrite(slide1, duty1);
  analogWrite(slide2, duty2);
 
 
}
}

void demoMode(){
  Serial.println();
  Serial.print("DEMO MODE");

//Sliding lights:
    time = millis();
  value = 128+127*cos(2*PI/period*time);
  analogWrite(slide1, value);          
  analogWrite(slide2, value);           

  for (int i=0; i<blinkClusters; i++){
    if(time - previousMillis[i] >= blinkIntervals[i]){
      previousMillis[i] = time;
      if(blinkStates[i] == LOW){
        blinkStates[i] = HIGH; //activate cluster based on intervals
      }else{
        blinkStates[i] = LOW;
      }
    }

    digitalWrite(blinks[i], blinkStates[i]); // blink cluster state application
  
  }
}
