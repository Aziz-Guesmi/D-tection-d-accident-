#include "MQ2.h"
#define PIN_MQ2 A1
#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int vib_pin=4;
int capteur_infra = 3;
int vehcule=5;
int lpg;
int accedent;
int Seat_bealt;
String _buffer;
MQ2 mq2(PIN_MQ2);
String number = "+21656423827";
void setup() {
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  delay(1000);
  Serial.begin(9600);
  mq2.begin();
  pinMode(capteur_infra, INPUT);
  pinMode(vib_pin,INPUT);
  pinMode(vehcule,OUTPUT);
  digitalWrite(vehcule,LOW);
}

void loop() {
   lpg = mq2.readLPG();
   Seat_bealt = digitalRead(capteur_infra);
   if (Seat_bealt==0)
    { 
        Serial.println("seat bealt detected");
        while (Seat_bealt==0){
          Seat_bealt = digitalRead(capteur_infra);
          lpg = mq2.readLPG();
          if (lpg<10){
            Serial.println("No alchool detected");
            delay(1000); 
            Serial.println("Car started");
            while (lpg<10 ){
              lpg = mq2.readLPG();
              Seat_bealt = digitalRead(capteur_infra);
              accedent=digitalRead(vib_pin);
              digitalWrite(vehcule,LOW);
              if(Seat_bealt==1)
                {Serial.println("Wornning seat bealt not detected decressing speeding..");
                delay (1000);
                }
                if(accedent==1)
                {
                  while(true){
                    Serial.println("sending SoS msg.");
                    delay(1000);
                    Serial.println("sending SoS msg..");
                    delay(1000);
                    Serial.println("sending SoS msg...");
                    delay(1000);
                    digitalWrite(vehcule,HIGH);
                 }
                 }
                 delay(1000);
              }
            
            }else {
              Serial.println(lpg);
              Serial.println("alchool detected");
              digitalWrite(vehcule,HIGH);
              delay(1000);
              }
            }
          
        }else 
            {Serial.println("Please put on seat bealt");
            digitalWrite(vehcule,HIGH);
            delay (5000);
              }
   
}