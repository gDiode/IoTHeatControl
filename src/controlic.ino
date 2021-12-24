int phaseControlPin = 1; 
int analogPin = A0;
int triggPin =  2;
int currentState = 0;
int previousState = 0;
//int controll=0;

void setup() {
   //Serial.begin(9600);
   pinMode(phaseControlPin, OUTPUT);
   pinMode(triggPin, INPUT);
  // Serial.begin(9600);
}

void dimmer(int percentage, int outputPin){
//entrada 0-1023 en percentage
//120hz = 0.00833s = 8.33ms = 8333us
//lower percentage value ==higher power
int a = 0;
if(percentage<=3){
  digitalWrite(outputPin,HIGH);
}
else if(percentage>850){//valor obtenido en prueba
  digitalWrite(outputPin,LOW);
}
else{//respuesta linear
  digitalWrite(outputPin,LOW);
  //rango de operacion de delayUs 3-8332us
  a = percentage*(8.0482); //el numero magico se obtiene de 8332/1023
  //Serial.println(a);
  delayMicroseconds(a);
  digitalWrite(outputPin,HIGH);
}
}

void loop() {
   
   int set = 0;

   currentState=digitalRead(triggPin);
   //Serial.println(analogRead(analogPin));
   
   if(currentState!=previousState){
    set = analogRead(analogPin);
    dimmer(set,phaseControlPin);
    }
   previousState=currentState;
}   
