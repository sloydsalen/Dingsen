

// is running when file opened
void writeMode(){
  printToDisplay("File:"+String(filename)+"", 0,0);
  float light = analogRead(inpin);
  float temp  = dallasGetTemperature();
  float values[] = {light,temp};
  printToSerial(values,2);
  printToDisplay(String(values[0])+" "+String(values[1]), 4,1);
  if(record){
    writeToFile(light);
    writeToFile(temp);
    printToDisplay("[R]", 0,1); 
    FileEndLine();
  }else{
    printToDisplay("[ ]", 0,1); 
  }
}



// ================ SERIAL ======================

void printToSerial(float value[],int n){
  Serial.print(String(value[0])+"\t");
  Serial.print(String(value[1])+"\t");
  Serial.println("");
}



