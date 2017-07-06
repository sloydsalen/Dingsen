

void initializeDisplay(){
  lcd.begin();
  lcd.backlight();
  for(byte i=0; i<16; i++){
    printToDisplay("=", i, 0);
    printToDisplay("=", i, 1);
    delay(50);
  }
  for(byte i=0; i<17; i++){
    printToDisplay("THINGS SEEM TO  ", 16-i, 0);
    printToDisplay("WORK WELL NOW   ", 16-i, 1);
    delay(50);
  }
  delay(1000);
  lcd.clear();
}

void printToDisplay(String s, int i, int j){
   lcd.setCursor(i,j);
   lcd.print(s);
}
