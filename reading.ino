void reading()
{
  sum=0;
  for(int i=0;i<12; i++)
  {
    digitalWrite(s0,i & 0x01);
    digitalWrite(s1,i & 0x02);
    digitalWrite(s2,i & 0x04);
    digitalWrite(s3,i & 0x08);
    analogvalue[i]= analogRead(input);
    (analogvalue[i]>500) ? digitalvalue[i]=1 ^ i_mode: digitalvalue[i]=0 ^ i_mode;
  }
  digitalsum= 1*digitalvalue[11]+ 2* digitalvalue[10]+ 4 * digitalvalue[9]+ 8 *digitalvalue[8] + 16 *digitalvalue[7]+ 32 *digitalvalue[6]+ 64 *digitalvalue[5]+128 *digitalvalue[4]+256 *digitalvalue[3]+512 *digitalvalue[2]+1024*digitalvalue[1]+2048*digitalvalue[0]; 
  sum= digitalvalue[0]+ digitalvalue[1]+digitalvalue[2]+ digitalvalue[3]+ digitalvalue[4]+ digitalvalue[5]+ digitalvalue[6]+ digitalvalue[7]+digitalvalue[8]+digitalvalue[9]+digitalvalue[10]+digitalvalue[11];
}
void show_value()
{  reading();
  display.clear();

  int xOffset = 0;
  int yOffset = 4; // Middle of the display for vertical centering
  int xStart = 10; // Start some pixels from the left edge for centering
  
  // Display the digital values in a single row with spacing
  for (int i = 0; i < 12; i++) {
    display.setCursor(xStart + i * 10, yOffset);
    display.print(digitalvalue[i]);
    
    // Print to Serial as well
    Serial.print(digitalvalue[i]);
    Serial.print(" ");
  }

  // Print to Serial for debugging
  Serial.print(String(digitalsum, 10) + " "); // Converting binary to decimal
  Serial.print(sum);
  Serial.println();
  
  // Add a delay to allow for visual checking of values
  delay(500);

}
