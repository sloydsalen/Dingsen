

// is running when file opened
void writeMode(){
  printToDisplay("File:"+String(filename)+"", 0,0);
  time = (millis()-timeAtStart)/1000.;
  float temp  = dallasGetTemperature();

  
  // print to Display
  // printToDisplay(String(int(10*time)/10.)+"s", 4,1);  not print time to display
  printToDisplay(String(temp)+" C",4,1);
  
  
  if(record){
    // print to Serial
    Serial.print(String(time)+"\t"); // time
    Serial.print(String(temp)+"\t"); // temp
    Serial.println(""); // end line
    
    // Write to file
    file.print(String(time)+"\t"); // time
    file.print(String(temp)+"\t"); // temp
    file.println(""); // end line
    
    printToDisplay("[R]", 0,1); 
  }else{
    printToDisplay("[ ]", 0,1); 
  }
}





