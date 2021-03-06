
void chooseFile(){
  filename = "file"+String(group)+".txt"; // update potential filename
  if(fileExists&&tryingToOpen){// Q: delete pre-existing file
    lcd.clear();
    printToDisplay(F("Stupid choice!"), 0,0);
    delay(1000);
    lcd.clear();
    tryingToOpen = false;
  }else if(tryingToOpen){
    initiateExperiment();
  }else{// choosing file
    printToDisplay("File: "+String(group), 0,0); 
    fileExists = SD.exists(filename);
    if(fileExists){
      printToDisplay(F("Exists"), 3,1);
    }
  }
}

void openFile(){
  Serial.println("FILE:"+filename);
  file = SD.open(filename, FILE_WRITE); 
  file.println(filename);
  printToDisplay(F("Opening file"), 0,1);
  delay(1500); // Wait 500ms after file chosen
  lcd.clear();
  timeAtStart = millis();
}

void initiateExperiment(){
  isOpen = true;
  printToDisplay(F("Initiating"), 0,1);
  delay(500); // Wait 500ms after file chosen
  lcd.clear();
}

void leaveInitiated(){

  if(record){
    Serial.println(F("CLOSING"));
    file.close();
    
    printToDisplay(F("*SAVING DATA*"), 0,1);
    delay(1000); // Wait 1000ms after file chosen
  }
  
  isOpen       = false;
  tryingToOpen = false;
  record       = false;
  
  printToDisplay(F("Back to menu"), 0,1);
  delay(500); // Wait 500ms after file chosen
  lcd.clear();
}



void closeFile(File file){
  Serial.println(F("CLOSING"));
  file.close();
  
  isOpen       = false;
  tryingToOpen = false;

  printToDisplay(F("*SAVING DATA*"), 0,1);
  delay(1000); // Wait 1000ms after file chosen
  lcd.clear();
}



void emptySDdirectory(String directory){
  lcd.clear();
  printToDisplay(F("Deleting SD"),0,0);
  delay(500);
  
  File root = SD.open(directory);
  root.rewindDirectory();
  
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) { break; }// no more files

    String nameOfFile = String(entry.name());
    printToDisplay("            ",0,1);
    printToDisplay(nameOfFile,0,1);
    SD.remove(nameOfFile);
    delay(500);
  
    entry.close();
  }
  lcd.clear();
}


void printFilesInDirectory(String directory){
  lcd.clear();
  printToDisplay(F("Printing SD"),0,0);
  delay(1000);
  File root = SD.open(directory);
  root.rewindDirectory();

  while (true) {
    File entry =  root.openNextFile();
    if (!entry) { break;} // no more files in directory
    String nameOfFile = String(entry.name());
    printToDisplay("            ",0,1);
    printToDisplay(nameOfFile,0,1);
    delay(500);

    entry.close();
  }
  lcd.clear();
}


void transferAllFiles(String directory){
  File root = SD.open(directory);
  root.rewindDirectory();
  while (true) {
    File entry =  root.openNextFile();
    if (!entry) { break;} // no more files in directory
    
    String nameOfFile = String(entry.name());
    printToDisplay(F("            "),0,1);
    printToDisplay(entry.name(),0,1);
    delay(400);
    entry.close();
    if(nameOfFile.substring(0,4)=="FILE"){
      
      printToDisplay(F("            "),0,1);
      printToDisplay(nameOfFile,0,1);
      delay(400);
  
      pushSDdata(nameOfFile);
    }
    
  }
  Serial.write("*END OF TRANSFER* \n");
}

/*
void transferAllFiles(String directory){
  File root = SD.open(directory);
  root.rewindDirectory();
  while (true) {
    File entry =  root.openNextFile();
    if (!entry) { break;} // no more files in directory
    
    String nameOfFile = String(entry.name());
    Serial.write(entry.name());
    entry.close();
    
    printToDisplay(F("            "),0,1);
    printToDisplay(nameOfFile,0,1);

    pushSDdata(nameOfFile);
    
  }
  Serial.write("*END OF TRANSFER* \n");
}

*/
