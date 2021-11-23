#include <WiFi.h>
#include <Wire.h>
#include <max6675.h>
#include <WiFiMulti.h>
#include <QuickPID.h>


WiFiMulti WiFiMulti;



int thermoDO = 21;
int thermoCS = 22;
int thermoCLK = 23;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float setpoint, input, output;
float kp=2,ki=5,kd=1;
QuickPID PID(&input,&output,&setpoint,kp,ki,kd,QuickPID::REVERSE);

void setup() {
  Wire.begin(18,19);//sda,scl
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  //wifi
    WiFiMulti.addAP("SSID", "PW");

    Serial.println();
    Serial.println();
    Serial.print("Waiting for WiFi... ");
      while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());   
  //pid
  digitalWrite(2,LOW);
  setpoint = 150;
  PID.SetMode(QuickPID::AUTOMATIC);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,LOW);
  const uint16_t port = 56322;
  const char * host = "192.168.1.84";
  Serial.print("Connecting to ");
  Serial.println(host);
  WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        digitalWrite(2,HIGH);
        delay(5000);
        return;
    }

    
  input = thermocouple.readCelsius();

  //pid
  PID.Compute();
  uint8_t entrada = input;
  uint8_t salida = output;
  //wifi/serial output
  String mensaje = String(entrada)+","+String(salida);
  //Serial.print(entrada);
  //Serial.print(",");
  //Serial.println(salida);
  Serial.println(mensaje);
  client.print(mensaje);
  client.stop();
  //i2c
  Wire.beginTransmission(3);//no me acuerdo del address
  Wire.write(salida);
  Wire.endTransmission();
  delay(300);
}
