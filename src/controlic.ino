#include<Wire.h>

int phaseControlPin = 3; 
int analogPin = A0;
int triggPin =  4;
int currentState = 0;
int previousState = 0;
int controll=0;




void setup() {
   pinMode(phaseControlPin, OUTPUT);
   pinMode(triggPin, INPUT);
   Wire.onReceive(data);  
  // Serial.begin(9600);
}
void data(int x){
  controll=Wire.read();
}

void dimmer(int percentage, int outputPin){
//entrada 0-1023 en percentage
//120hz = 0.00833s = 8.33ms = 8333us
int a = 0;
if(percentage>=1){
  digitalWrite(outputPin,HIGH);
  //rango de operacion de delayUs 3-8332us
  a = percentage*(8.1446); //el numero magico se obtiene de 8332/1023
  //Serial.println(a);
  delayMicroseconds(a);
  digitalWrite(outputPin,LOW);
}
 else
{
  digitalWrite(outputPin,LOW);
}
}

void loop() {
   int set = 0;
   currentState=controll; 
   if(currentState!=previousState){
    set = analogRead(analogPin);
    dimmer(set,phaseControlPin);
    }
   previousState=currentState;
}   
