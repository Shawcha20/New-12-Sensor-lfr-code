byte push(byte button_number) {
  uint32_t b_timer = 0;
  if (!digitalRead(button_number)) {  //if button is pressed
    delay(50);                        //debounce delay;
    while (!digitalRead(button_number)) {
      delay(50);
      b_timer += 50;
      if (b_timer > 1000) digitalWrite(led, 1);
    }
    digitalWrite(led, 0);
    if (b_timer > 1000) return 2;    //long press
    else if (b_timer > 0) return 1;  //short press
  }
  return 0;
}

byte encRead() {
  long newPosition = myEnc.read();
  if (newPosition >= oldPosition + 4 || newPosition <= oldPosition - 4) {
    if (newPosition > oldPosition) {
      oldPosition = newPosition;
      return 1;
    } 
    else {
      oldPosition = newPosition;
      return 2;
    }
  }
  else return 0;
}


void homescreen() {
  display.clear();
  display.set2X();
  display.setInvertMode(0);
  text("   Line    ", 4, 0);
  text("Following  ", 10, 3);
  text("Robot", 30,5);
}
void line_following() {
  display.clear();
  display.set2X();
  display.setInvertMode(0);
  text("   Line    ", 4, 0);
  text("Following  ", 10, 3);
}
void sonar_show() {
  display.clear();
  display.set2X();
  display.setInvertMode(0);
  text("   Sonar   ", 4, 0);
  text("  Checking  ", 10, 3);
}
void line_obstacle_avoiding() 
{
  display.clear();
  display.set2X();
  display.setInvertMode(0);
  text("   Line    ", 4, 0);
  text("Obstacle  ", 10, 3);
  text(" Avoiding ", 30,5);
}
