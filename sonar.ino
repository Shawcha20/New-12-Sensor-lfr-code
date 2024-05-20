bool sonar_readf(bool mode) {
  if (tf - millis() > 50 || mode) {
    tf = millis();
    sf = sonarf.ping_cm();
    if (sf <= 2) sf = 50;
  }
  if (sf < obstacle_limit) return 1;
  else return 0;
}
bool sonar_readr(bool mode) {
  if (tr - millis() > 50 || mode) {
    tr = millis();
    sr= sonarr.ping_cm();
    if (sr <= 2) sr = 50;
  }
  if (sr < obstacle_limit) return 1;
  else return 0;
}
bool sonar_readl(bool mode) {
  if (tl - millis() > 50 || mode) {
    tl = millis();
    sl= sonarl.ping_cm();
    if (sl <= 2) sl = 50;
  }
  if (sl < obstacle_limit) return 1;
  else return 0;
}

int sonarf_read1()
{
  if (tf - millis() > 30) {
    tf = millis();
    sf = sonarf.ping_cm();
    if (sf == 0) sf = 50;
//    Serial.print("front");
//    Serial.print(sf);
    return sf;
  }
}
int sonarl_read2()
{
  if (tl - millis() > 30) {
    tl = millis();
    sl = sonarl.ping_cm();
    if (sl == 0) sl = 50;
//    Serial.print("  left");
//    Serial.println(sl);
    return sl;
  }

}
int sonarr_read3()
{
  if (tr - millis() > 30) {
    tr = millis();
    sr = sonarr.ping_cm();
    if (sr == 0) sr = 50;
//    Serial.print("   right : ");
//    Serial.println(sr);
    return sr;
  }

}
void show_sonar()
{
  display.clear();
  int s1, s2, s3;
  s1 = sonarf_read1();
  s2 = sonarl_read2();
  s3 = sonarr_read3();
  
  // Print to Serial for debugging
  Serial.print(s1);
  Serial.print(" ");
  Serial.print(s2);
  Serial.print(" ");
  Serial.println(s3);

  // Display the values in different rows and columns
  display.setCursor(0, 2);  // First column, first row
  display.print("L: ");
  display.print(s2);

  display.setCursor(40, 0); // First column, second row
  display.print("F: ");
  display.print(s1);

  display.setCursor(60, 2); // First column, third row
  display.print("R: ");
  display.print(s3);
}
