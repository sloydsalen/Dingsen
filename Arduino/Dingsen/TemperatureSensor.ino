
void initiateDallas(){
  dallas.begin();
}

float dallasGetTemperature(){
  dallas.requestTemperatures();
  return dallas.getTempCByIndex(0);
}




