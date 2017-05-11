
// For pushing data on chosen file to Serial once pressed
void pushSDdata(){
  if(SD.exists(filename)){
    printToDisplay("Exists", 3,1); 
    File outfile = SD.open(filename);
    
    while (outfile.available()){
      Serial.write(outfile.read());
    }
    Serial.write("*END OF FILE* \n");
  }  
}
