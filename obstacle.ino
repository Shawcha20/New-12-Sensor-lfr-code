void obstacle() {
  motor(0, 0);
  delay(100);
  motor(150, -150);
  delay(turn90_delay);  //turn 90 degree right
  motor(0, 0);
  delay(100); 
  motor(150,150);  //straight
  delay(300);
  motor(0, 0);
  delay(100);
  motor(-150, 150);  //turn 90 left
  delay(turn90_delay);  
  motor(0,0);
  delay(100);
  motor(150,150); // middle stright
  delay(500);
  motor(0, 0);
   motor(-150, 150);  // turn 90 degree left
  delay(turn90_delay);  
  motor(0,0);
  delay(100);
  motor(150,150); //stright
  reading();
  while(sum==0)reading();
  motor(0, 0);
  delay(100);
  motor(130, -130);
  reading();
  while(digitalvalue[4]!=1 &&digitalvalue[5]!=1&&digitalvalue[6]!=1)reading();  //turn 90 degree right
}
