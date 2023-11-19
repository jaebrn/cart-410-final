// EDISON SCIENCE CORNER
// EDISON SCIENCE CORNER
// EDISON SCIENCE CORNER

// EDISON SCIENCE CORNER
// EDISON SCIENCE CORNER
// EDISON SCIENCE CORNER

#include <CapacitiveSensor.h>

CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4); // 1M resistor between pins 2 & 4, pin 4 is sensor pin, add a wire and 
int cnt=0;
int in = 2; 
int out = 4;  
int state = HIGH;  
int r;           
int p = LOW;    
long time = 0;       
long debounce = 200;
void setup()
{
  pinMode(4, INPUT);
  /*    LED Outputs   */
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
}
void loop()                    
{
 
  r = digitalRead(4);
  if (r == HIGH && p == LOW && millis() - time > debounce) {
    cnt++;
  if (state == HIGH)
     state = LOW;
    else 
    time = millis();
  }
  
  if(cnt == 1){
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if(cnt == 2){
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  if(cnt == 3){
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  if(cnt > 3){
      cnt = 1;
  }
  p = r;
}