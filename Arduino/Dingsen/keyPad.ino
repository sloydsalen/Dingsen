
void initializeButtonPins(){
  for (int i = 0; i < numberOfButtons; i++) {
    pinMode(buttons[i], INPUT);
  }
}

void keypad(bool keysPressed[]){
  if(!isOpen){ // if file is NOT open
    // VERTICAL NAVIGATION BUTTONS
    if( keysPressed[downButton]){ // DOWN
      lcd.clear();
      fileExists   = false;
      tryingToOpen = false;
      group -= 1;
      group = (group+maxNumGroups)%maxNumGroups;
    }
    if( keysPressed[upButton]){ // UP
      lcd.clear();
      fileExists   = false;
      tryingToOpen = false;
      group += 1;
      group = (group+maxNumGroups)%maxNumGroups;
    }

    if( keysPressed[printFilesButton]){ // PRINT SD CARD CONTENT
      pushSDdata(filename);
      printFilesInDirectory("/");
    }
    
    if( keysPressed[deleteFilesButton]){ // EMPTY SD CARD
      lcd.clear();
      printToDisplay("DELETE? Press",0,0);
      printToDisplay("REC and DELETE",0,1);
      delay(2000);
      lcd.clear();
      // emptySDdirectory("/");
    }
    if( keysPressed[deleteFilesButton] && keysPressed[recordButton]){
      emptySDdirectory("/");
    }
   
  }else{ // if file is open
    file.flush(); // Ensure written data is stored in file
    if( keysPressed[recordButton]){ // RECORD BUTTON
      if(record){ // about to close
        closeFile(file);
      }else{ // about to open
        openFile();
      }
      delay(200);
      lcd.clear();
      record = !record; // toggle record mode
      
    }
  }

  

  // OPEN/CLOSE BUTTON
  if( keysPressed[openCloseButton]){ 
    if(isOpen){
      leaveInitiated();
      //closeFile(file);
      tryingToOpen = false;
    }else{
      tryingToOpen = true;
      //openFile();
    }
  }
}
