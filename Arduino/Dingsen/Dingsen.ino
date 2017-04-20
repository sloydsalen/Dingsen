
#include <Wire.h>               // For Display (builtin)
#include <SD.h>                 // for SD (builtin)
#include <LiquidCrystal_I2C.h>  // For Display  https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/blob/master/LiquidCrystal_I2C.h
#include <OneWire.h>            // For Dallas temperture sensor https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>  // For Dallas temperture sensor https://github.com/milesburton/Arduino-Temperature-Control-Library

// GENERAL
int loopDelay = 50;
int group = 1;
int maxNumGroups = 100;

// DISPLAY
// initialize display
LiquidCrystal_I2C lcd(0x27, 16,2);  // Set the LCD I2C address

// BUTTONS
// define button pins
int numberOfButtons   = 6;
int buttons[]         = {7,6,5,4,3,2};
int upButton          = 0;
int downButton        = 1;
int recordButton      = 2;
int printFilesButton  = 3;
int deleteFilesButton = 4;
int openCloseButton   = 5;
bool keysPressed[]  = {false,false,false,false,false,false};


// SD CARD
int SDpin             = 10;
String filenamePrefix = "group_data_";
String filename       = "Undetermined.txt";
bool isOpen           = false;
bool tryingToOpen     = false;
bool record           = false;
File file;


// DALLAS 
int dallasPin = 8;

OneWire oneWire(dallasPin);
DallasTemperature dallas(&oneWire);

// OTHER
int inpin = 15; // photoresistor pin


void setup()   
{ 
  // initialize serial
  Serial.begin(9600);
  
  // initialize inpin
  pinMode(inpin,INPUT);

  for(int i= 0; i<numberOfButtons; i++){
    pinMode(buttons[i],INPUT);
  }

  // SD CARD
  SD.begin(SDpin);

  // DALLAS
  initiateDallas();

  // DISPLAY
  lcd.begin();
  
  // STARTPRINT
  printToDisplay("Things are", 0,0);
  printToDisplay("working well!", 0,1);
  lcd.backlight(); 
  delay(1000);
  lcd.clear();
  
}



void loop()  
{ 

  // get button activity
  for(int i= 0; i<numberOfButtons; i++){
    keysPressed[i] = digitalRead(buttons[i])==1;
  }
  
  // react to keypad events
  keypad(keysPressed);
  
  // HANDLE EVENTS
  handleEvents();

  

  delay(loopDelay);
}


void handleEvents(){
  if(isOpen){ // if group chosen
    writeMode();
  }else{ // if no group chosen
    chooseFile();
  }
}







//

