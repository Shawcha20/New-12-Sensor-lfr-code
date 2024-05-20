void calibration()
{
  
  display.clear();
   text("   1.Calibration   ", 4, 1);
   delay(1000);
   display.clear();
  text("  Calibrating  ", 10, 4);
  Serial.println("1.CALIBRATION");
  int s[12];
  motor(100, -100);
  for (int i = 0; i < 5000 ; i++) {
    reading();
    for (int i = 0; i < 12 ; i++) {
      s[i] = analogvalue[i];
      maximum[i] = max(maximum[i], s[i]);
      minimum[i] = min(minimum[i], s[i]);
    }
  }
  motor(0, 0);
  for (int i = 0; i < 12; i++) {
    mid[i] = (maximum[i] + minimum[i]) / 2;
    EEPROM.write(i, mid[i] / 4); delay(10);
    EEPROM.write(i + 12, maximum[i] / 4); delay(10);
    EEPROM.write(i + 24, minimum[i] / 4); delay(10);
  }
    display.clear();
  int j=20;
  for(int i=11; i>=0; i--)
  {
    display.setCursor(j,30);
    display.print(mid[i]);
    j+=10;
  }
}
