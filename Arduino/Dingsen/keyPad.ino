
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
      group -= 1;
      group = (group+maxNumGroups)%maxNumGroups;
    }
    if( keysPressed[upButton]){ // UP
      lcd.clear();
      group += 1;
      group = (group+maxNumGroups)%maxNumGroups;
    }

    if( keysPressed[printFilesButton]){ // PRINT SD CARD CONTENT
      printFilesInDirectory("/");
    }
    
    if( keysPressed[deleteFilesButton]){ // FLUSH SD CARD
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
    if( keysPressed[recordButton]){ // RECORD BUTTON
      record = !record; // toggle record mode
      delay(200); 
      lcd.clear();
    }
  }

  

  // OPEN/CLOSE BUTTON
  if( keysPressed[openCloseButton]){ 
    if(isOpen){
      closeFile(file);
    }else{
      openFile();
    }
  }
}
