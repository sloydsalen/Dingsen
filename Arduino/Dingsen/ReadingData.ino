

// is running when file opened
void writeMode(){
  printToDisplay("File:"+String(filename)+"", 0,0);
 
  float temp  = dallasGetTemperature();

  // print to Display
  printToDisplay(String(temp)+" C",4,1);
  
  
  if(record){
    time = (millis()-timeAtStart)/1000.;
    
    // print to Serial
    Serial.print(String(time)+"\t"); // time
    Serial.print(String(temp)+"\t"); // temp
    Serial.println(""); // end line
    
    // Write to file
    file.print(String(time)+"\t"); // time
    file.print(String(temp)+"\t"); // temp
    file.println(""); // end line
    
    printToDisplay(F("[R]"), 0,1); 
  }else{
    printToDisplay(F("[ ]"), 0,1); 
  }
}





