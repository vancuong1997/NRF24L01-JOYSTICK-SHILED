
#include "Easybot.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   7
#define CSN_PIN  8
EasybotNano Robot; 
int speed=100;

byte address[1][6] = {"robot"};              // Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

/*-----Object Declaration ----*/

RF24 radio(CE_PIN, CSN_PIN); // Activate the Radio

/*-----Declaration of Variables -----*/

int joystick[9];  //  Two element array holding the Joystick readings
bool done = false;
bool debug = 1; 
int x,y,l,r;
bool updated = 0;
void setup()  
{
  Serial.begin(9600); /* Opening the Serial Communication */

  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
    radio.setChannel(108);
    radio.setDataRate(RF24_1MBPS);    // Tốc độ truyền
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  l=0;r=0;  //left speed = 0; right speed = 0; 
    delay(1000);
}//--(end setup )---


void loop()   
{
  if ( radio.available() )
  {
    // Reading the data payload until the RX received everything
  //done = false;
   while (radio.available()) {                                   // While there is data ready
        radio.read( joystick, sizeof(joystick));    // Get the payload
        
        updated = 1; 
       
      }
   Serial.println("updated");    
  }
  else
  {    
    //  Serial.println("No radio available");
     // delay(500);
     l=0;r=0;
  }

     if(updated){
      int button=joystick[2];
      if (button==5)
      {
        x = map(joystick[0],0,670,-100,+100);
        y = map(joystick[1],0,670,-100,+100);
      l = y+x; r = y-x; 
      if (l>100) l = 100; 
      else if (l<-100) l = -100;
      if (r>100) r = 100;
      else if (r<-100) r=-100; 
      if(debug){
      Serial.print("X = ");
      Serial.print(x);
      Serial.print(" Y = ");      
      Serial.print(y);
      Serial.print("     L = ");
      Serial.print(l);
      Serial.print(" R = ");
      Serial.println(r);
      }
      Robot.moveForward(l,r);
      }
      else if (button==1) 
      {
        Robot.moveForward(speed);
        Serial.println("Up");
      }
      else if (button==2) 
      {
        Robot.turnRight(speed);
        Serial.println("Turn Right");
      }
      else if (button==3) 
      {
        Robot.moveBack(speed);
        Serial.println("Down");
      }
      else if (button==4) 
      {
        Robot.turnLeft(speed);
        Serial.println("Turn Left");
      }
      else if (button==0)
      {
        Robot.stop();
      }
      
      updated = 0;
      } 
    else {
      
    }  
 }

