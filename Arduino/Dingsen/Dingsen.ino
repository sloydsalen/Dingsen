
#include <Wire.h>               // For Display (builtin)
#include <SD.h>                 // for SD (builtin)
#include <LiquidCrystal_I2C.h>  // For Display  https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/blob/master/LiquidCrystal_I2C.h
#include <OneWire.h>            // For Dallas temperture sensor https://github.com/PaulStoffregen/OneWire 
#include <DallasTemperature.h>  // For Dallas temperture sensor https://github.com/milesburton/Arduino-Temperature-Control-Library
                                

// GENERAL
#define loopChoosefileDelay 100
#define loopDelay 0
#define maxNumGroups 100
int group = 1; // choice of group


// DISPLAY
// initialize display
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

// BUTTONS
// define button pins
unsigned int numberOfButtons   = 6;
unsigned int buttons[]         = {7, 6, 5, 4, 3, 2};
unsigned int downButton        = 0;
unsigned int upButton          = 1;
unsigned int recordButton      = 2;
unsigned int printFilesButton  = 3;
unsigned int deleteFilesButton = 4;
unsigned int openCloseButton   = 5;
bool keysPressed[]  = {false, false, false, false, false, false};


// SD CARD
unsigned int SDpin             = 10;
String filenamePrefix = "group_data_";
String filename       = "Undetermined.txt";
bool isOpen           = false;
bool tryingToOpen     = false;
bool fileExists       = false;
bool record           = false;
File file;

// TIME
float time;
unsigned long timeAtStart;

// DALLAS
int dallasPin = 8;
int bitResolution[] = {9, 10, 11, 12, 13}; // low: fast, inaccurate      high: slow, accurate
        // Resolutions ---  9bit: 0.5 deg      10bit: 0.25 deg      11bit: 0.125 deg    12bit: 0.0625 deg
        // Resolutions ---  9bit: ***          10bit: 0.23 sec      11bit: 0.40 sec     12bit: 0.75 sec
int bitResolutionChoice = 2; // index
OneWire oneWire(dallasPin);
DallasTemperature dallas(&oneWire);

// SERIAL COMMUNICATION
bool recievedMessage = false;

void setup()
{
  // initialize serial
  Serial.begin(9600);

  initializeButtonPins();

  // SD CARD
  SD.begin(SDpin);

  // DALLAS
  initiateDallas();

  // DISPLAY
  initializeDisplay();

  // SERIAL COMMUNICATION
  considerSerialProcedure();
  
}



void loop()
{
  if(recievedMessage){ // IF SIGNAL DETECTED --> Serial Communication procedure 
    
    serialResponse();
    
  }else{ // IF NO SIGNAL DETECTED --> Manually Operated device
    
    // get button activity
    for (byte i = 0; i < numberOfButtons; i++) {
      keysPressed[i] = digitalRead(buttons[i]) == 1;
    }
  
    // react to keypad events
    keypad(keysPressed);
  
  
    // HANDLE EVENTS
    handleEvents();
   

    delay(loopDelay);
  }
}


void handleEvents() {
  if (isOpen) { // if group chosen
    writeMode();
    delay(loopDelay);
  } else { // if no group chosen
    chooseFile();
    delay(loopChoosefileDelay);
  }
}








//

