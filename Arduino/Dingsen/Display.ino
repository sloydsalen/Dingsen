

void initializeDisplay(){
  lcd.begin();
  printToDisplay("Things are", 0, 0);
  printToDisplay("working well!", 0, 1);
  lcd.backlight();
  delay(1000);
  lcd.clear();
}

void printToDisplay(String s, int i, int j){
   lcd.setCursor(i,j);
   lcd.print(s);
}
