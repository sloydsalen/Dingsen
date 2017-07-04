
#include <Wire.h>               // For Display (builtin)
#include <SD.h>                 // for SD (builtin)
#include <LiquidCrystal_I2C.h>  // For Display  https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/blob/master/LiquidCrystal_I2C.h
#include <OneWire.h>            // For Dallas temperture sensor https://github.com/PaulStoffregen/OneWire 
#include <DallasTemperature.h>  // For Dallas temperture sensor https://github.com/milesburton/Arduino-Temperature-Control-Library
                                

// GENERAL
int loopChoosefileDelay   = 100;
int loopDelay             = 0;
int group                 = 1;
int maxNumGroups          = 100;

// DISPLAY
// initialize display
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

// BUTTONS
// define button pins
int numberOfButtons   = 6;
int buttons[]         = {7, 6, 5, 4, 3, 2};
int upButton          = 0;
int downButton        = 1;
int recordButton      = 2;
int printFilesButton  = 3;
int deleteFilesButton = 4;
int openCloseButton   = 5;
bool keysPressed[]  = {false, false, false, false, false, false};


// SD CARD
int SDpin             = 10;
String filenamePrefix = "group_data_";
String filename       = "Undetermined.txt";
bool isOpen           = false;
bool tryingToOpen     = false;
bool record           = true;
File file;

// TIME
float time;
unsigned long timeAtStart;


// DALLAS
int dallasPin = 8;
int bitResolution[] = {9, 10, 11, 12, 13}; // low: fast, inaccurate      high: slow, accurate
        // Resolutions ---  9bit: 0.5 deg      10bit: 0.25 deg      11bit: 0.125 deg    12bit: 0.0625 deg
        // Resolutions ---  9bit: ***          10bit: 0.23 sec      11bit: 0.40 sec     12bit: 0.75 sec
int bitResolutionChoice = 3; // index
OneWire oneWire(dallasPin);
DallasTemperature dallas(&oneWire);


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
}



void loop()
{

  // get button activity
  for (int i = 0; i < numberOfButtons; i++) {
    keysPressed[i] = digitalRead(buttons[i]) == 1;
  }

  // react to keypad events
  keypad(keysPressed);


  // HANDLE EVENTS
  handleEvents();


  delay(loopDelay);
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

