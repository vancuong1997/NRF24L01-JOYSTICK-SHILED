#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define KeyA 2
#define KeyB 3
#define KeyC 4
#define KeyD 5
#define KeyE 6
const uint64_t pipe = 0xE8E8F0F0E1LL;
byte address[][6] = {"robot"};      
RF24 radio(CE_PIN, CSN_PIN); // Activate  the Radio
int button=0;
int joystick[3];  // Two element array holding the Joystick readings

void setup()   
{
   Serial.begin(9600); 
   pinMode(KeyA,INPUT);
   pinMode(KeyB,INPUT);
   pinMode(KeyC,INPUT);
   pinMode(KeyD,INPUT);
   pinMode(KeyE,INPUT);
  
  radio.begin();
  radio.setChannel(108);
  radio.setDataRate(RF24_1MBPS);    // Tốc độ truyền
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipe);
  Serial.println("Start");
  delay(1000);
}


void loop()   
{
  joystick[0] = analogRead(JOYSTICK_X); 
  joystick[1] = analogRead(JOYSTICK_Y); 
  if (!digitalRead(KeyA)) button = 1;
  else if (!digitalRead(KeyB)) button = 2;
   else if (!digitalRead(KeyC)) button = 3;
    else if (!digitalRead(KeyD)) button = 4;
    else if (!digitalRead(KeyE)) button = 5;
     else button = 0;
   joystick[2]= button;
   radio.write( joystick, sizeof(joystick) );
    delay(500);
}
