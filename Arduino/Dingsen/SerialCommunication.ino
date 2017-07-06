
// in setup: See if a message waits in serial, if yes do serialCommunication mode
void considerSerialProcedure(){
  String content = listenForSignal(); // try to listen for first message
  if(content==F("INITIATE")){ // if "INITIATE" found
    recievedMessage = true;
    lcd.clear();
    printToDisplay(F("SLAVE MODE"),0,0);
    printToDisplay(F("Serial Detected"),0,1);
    delay(1000); 
    lcd.clear();
    timeAtStart = millis();
  }else{
    lcd.clear();
    printToDisplay(F("MANUAL MODE"),0,0);
    printToDisplay(F("No Serial"),0,1);
    delay(1000); 
    lcd.clear();
  }
}


// Listen for a Serial message ending with line-break and returns NOTHING if empty
String listenForSignal(){
  String content = "";
  if(Serial.available() > 0){
    content = Serial.readStringUntil('\n');
  }
  if (content != "") {
    return content;
  }else{
    return F("NOTHING");
  }
}




void serialResponse(){

  String message = listenForSignal();
  if(message!="NOTHING"){
    handleMessage(message);
    lcd.clear();
    printToDisplay(message,0,0);
    delay(500);
    lcd.clear();
  }
  
  broadcast();
    
}


void handleMessage(String msg){

  if(msg==F("RECORD TRUE")){
    record = true;
  }else if(msg==F("RECORD FALSE")){
    record = false;
  }else if(msg==F("RESET TIME")){
    timeAtStart = millis();
  }else if(msg==F("DELETE ALL")){
    emptySDdirectory("/");
  }else if(msg==F("PRINT STORED")){
    printFilesInDirectory("/");
  }else if(msg==F("TRANSFER ALL")){
    transferAllFiles("/");
  }else if(msg==F("INCREASE RES")){
    bitResolutionChoice += 1;
    bitResolutionChoice = (bitResolutionChoice+5)%5;
  }else if(msg==F("DECREASE RES")){
    bitResolutionChoice -= 1;
    bitResolutionChoice = (bitResolutionChoice+5)%5;
  }
  
  
}

// Writing data to display and Serial port
void broadcast(){
  float temp  = dallasGetTemperature();
  
  if(record){
    time = (millis()-timeAtStart)/1000.;
    
    Serial.print(String(time)+"\t"); // time
    Serial.print(String(temp)+"\t"); // temp
    Serial.println(""); // end line
    
    printToDisplay("Broadcasting",0,0);
    printToDisplay(String(int(time))+"s",0,1);
  }else{
    printToDisplay("Awaiting orders",0,0);  
  }
  printToDisplay(String(temp)+" C",8,1);
}




