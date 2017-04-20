
void chooseFile(){
  filename = "group"+String(group)+".txt"; // update potential filename
  if(tryingToOpen){// Q: delete pre-existing file
    printToDisplay("Delete existing", 0,0);
    printToDisplay("file?", 0,1);
  }else{// choosing file
    printToDisplay("Choose group:"+String(group), 0,0); 
    bool fileExists = SD.exists(filename);
    if(fileExists){
      printToDisplay("Exists", 3,1); 
    }
  }
}


void handleExistingFile(){
  if(keysPressed[3]){
    printToDisplay("!!!!", 4,1); 
    delay(800);
    SD.remove(filename);
  }
}

void removeFile(){
  SD.remove(filename);
}

void openFile(){
  file = SD.open(filename, FILE_WRITE); 
  file.println("--");
  file.print("GROUP: ");
  file.println(group);
  file.println("--");
  isOpen = true;
  printToDisplay("Opening file", 0,1);
  delay(500); // Wait 500ms after file chosen
  lcd.clear();
}



void closeFile(File file){
  file.close();
  printToDisplay("Closing file", 0,1);
  isOpen = false;
  record = false;
  delay(500); // Wait 500ms after file chosen
  lcd.clear();
}


void writeToFile(float value){
  file.print(String(value)+"\t"); // separate with tab
}

void FileEndLine(){
  file.println("");
}

void emptySDdirectory(String directory){
  lcd.clear();
  printToDisplay("Deleting SD",0,0);
  delay(500);
  
  File root = SD.open(directory);
  root.rewindDirectory();
  
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) {
      break; // no more files
    }

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
  printToDisplay("Printing SD",0,0);
  delay(1000);
  File root = SD.open(directory);
  root.rewindDirectory();
  
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    String nameOfFile = String(entry.name());
    printToDisplay("            ",0,1);
    printToDisplay(nameOfFile,0,1);
    delay(1000);

    entry.close();
  }
  lcd.clear();
}



