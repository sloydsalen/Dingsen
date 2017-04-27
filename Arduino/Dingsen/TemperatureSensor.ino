
DeviceAddress tempDeviceAddress;

void initiateDallas(){
  dallas.begin();
  dallas.setResolution(bitResolution[bitResolutionChoice]);
  //dallas.setWaitForConversion(false);
  for(int i=0;i<dallas.getDeviceCount(); i++){
    // Search the wire for address
    dallas.getAddress(tempDeviceAddress, i);
  }
}

float dallasGetTemperature(){
  dallas.requestTemperatures();
  return dallas.getTempCByIndex(0); // the fast way
  //return dallas.getTempC(tempDeviceAddress); // in case of emergency failure, use this
}




