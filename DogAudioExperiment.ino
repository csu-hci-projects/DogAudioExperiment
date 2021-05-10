#include <SD.h>                           //include SD module library
#include <TMRpcm.h>                       //include speaker control library

// code for bluetooth https://create.arduino.cc/projecthub/mayooghgirish/arduino-bluetooth-basic-tutorial-d8b737
// code for microSD reader https://steemit.com/utopian-io/@kimp0gi/playing-music-in-arduino-using-sd-card-module

#define SD_ChipSelectPin 4                //define CS pin
int motorForwardPin = A3;                  // pin used to control foward motor direction
int motorReversePin = A6;                  // pin used to control reverse motor correction
bool isPlayingAudio = false;              //variable used to determine if audio is playing from speakers
char Incoming_value = 0;                  //Variable for storing Incoming_value
const int hallPin = 2;
int hallVal = 0;



TMRpcm tmrpcm;                            //crete an object for speaker library

void setup(){  
  pinMode (hallPin, INPUT);
  pinMode(motorForwardPin, OUTPUT);       // sets the pin as output
  pinMode(motorReversePin, OUTPUT);       // sets the pin as output
  analogWrite(motorForwardPin, LOW);      // turn pin off
  analogWrite(motorReversePin, LOW);      // turn pin off
  tmrpcm.speakerPin = 9;                  //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission

  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    Serial.print("SD FAILED.");
    return;                               //don't do anything more if not
  }
}

void loop(){
  if(Serial.available() > 0 && !isPlayingAudio){
      Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
      Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
      if(Incoming_value == '0'){           //Checks whether value of Incoming_value is equal to 0 
        // play robot joe sit
        tmrpcm.play("robotSit.wav");
      }
      else if(Incoming_value == '1')   {    
        // play robot joe shake
        tmrpcm.play("robotShake.wav");
      }
      else if(Incoming_value == '2')   {    
        // play robot joe down
        tmrpcm.play("robotDown.wav");
      }
      else if(Incoming_value == '3')   {    
        // play tanner joe sit
        tmrpcm.play("tannerSit.wav");
      }
      else if(Incoming_value == '4')   {    
        // play tanner joe shake
        tmrpcm.play("tannerShake.wav");
      }
      else if(Incoming_value == '5')   {    
        // play tanner joe down
        tmrpcm.play("tannerDown.wav");
      }
      else if(Incoming_value == '6')   {    
            // dispense treat
            analogWrite(motorForwardPin, 128);      //turns motor on
            delay(250);                             //waits 1/4 a second to start reading hall sensor values
            bool isDispensing = true;
            while(isDispensing){
                hallVal = digitalRead(hallPin);     //reads hall sensor values and sets the value you to low or high depending on if the reading is above of below 128
                if(hallVal == LOW){
                  analogWrite(motorForwardPin, LOW);      // turn motor off
                  isDispensing = false;
                }
            }
      }
   }                              
}
