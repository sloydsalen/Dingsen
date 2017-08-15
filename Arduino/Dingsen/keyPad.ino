
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

    if( keysPressed[downButton] && keysPressed[upButton] && keysPressed[openCloseButton]){
      emptySDdirectory("/");
    }
   
  }else{ // if file is open
    //file.flush(); // Ensure written data is stored in file
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
