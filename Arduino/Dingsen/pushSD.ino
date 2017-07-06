
// For pushing data on chosen file to Serial once pressed
void pushSDdata(String nameOfFile){
  Serial.write("*PUSHING FILE* \n");
  if(SD.exists(nameOfFile)){
    //printToDisplay("Exists", 3,1); 
    File outfile = SD.open(nameOfFile);
    
    while (outfile.available()){
      Serial.write(outfile.read());
    }
    Serial.write("*END OF FILE* \n");
  }  
}
