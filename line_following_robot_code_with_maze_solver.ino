//#include<U8g2lib.h>
#include<EEPROM.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire display;
#include <Encoder.h>
#include <NewPing.h>
Encoder myEnc(7, 5);
// sonar sensors
#define TRIGGER_PIN  15  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PINl  19  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PINl     23
#define TRIGGER_PINr  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PINr     13
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonarf(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarl(TRIGGER_PINl, ECHO_PINl, MAX_DISTANCE);
NewPing sonarr(TRIGGER_PINr, ECHO_PINr, MAX_DISTANCE);
unsigned long tf, tr, tl = 0; // Stores the last time the sonar was read.
int sf, sl, sr;
int obstacle_limit = 15;
int wall_limit = 20;
int initial = 1;
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0,/*clock*/A5, /*data=*/A4, /*reset=*/U8X8_PIN_NONE);
//-----------------motor Setup-------------------
#define ENB 4  // Enable pin for Motor A
#define IN3 42   // Control pin 1 for Motor A
#define IN4 40  // Control pin 2 for Motor A
#define ENA 2  // Enable pin for Motor A
#define IN2 46   // Control pin 1 for Motor A
#define IN1 44  // Control pin 2 for Motor A
#define spl 5
#define spr 5
#define u_turndelay 100
#define turn_delay 30
#define turn90_delay 180
#define node_delay 100
#define stop_timer 200
uint32_t m1, m2, m3;
#define i_timer 150


//maze and turns 
char cross = 's';
char side = 'r';
bool lastClk = HIGH;
long oldPosition = 0;
//-----inverse line follow----
bool i_mode=0;

//-----------------mux setup----------------------
const int s0 = 29;
const int s1 = 31;
const int s2 = 27;
const int s3 = 25;
const int input = A2;
byte check_status = 0;
int analogvalue[12];
int digitalvalue[12];
int base[12] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
int digitalsum;
int sum;
#define led 13
//-----------------mux setup ends----------------
// ----------------TURN-------------------------
char flag;
const int sw = 3; //input pull up switch
//time
#define forward 100
#define turn_t 100
int maximum[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int minimum[12] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
int mid[12];
void setup()
{

  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(System5x7);
  //  oled.invertDisplay(true);
  display.displayRemap(1);
  homescreen();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(input, INPUT);
  // pinMode(left,INPUT);
  // pinMode(right,INPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
 
  for (int i = 0; i < 12; i++)
  {
    mid[i] = EEPROM.read(i) * 4;
    Serial.println(mid[i]);
    maximum[i] = EEPROM.read(i + 12) * 4;
    minimum[i] = EEPROM.read(i + 24) * 4;
  }
    tf = tr = tl = millis();
}
void loop()
{
  byte r = push(3);
  if (r) {
    if (r == 1) {
      r = menu();
      Serial.println(r);
      if (r == 1) {
        calibration();
      }
      else if (r == 2) {

        while (1)
        { show_value();
          byte r = push(3);
          if (r > 0)
          {
            break;
          }
        }
      }
      else if (r == 3)
      {
        line_following();
        line_follow_left();
      }
      else if (r == 4)
      {
        line_following();
        line_follow_right();
      }
      else if (r == 5) {
        sonar_show();
       
        while (1) {
          
           show_sonar();
           delay(200);
          byte r = push(3);
          if (r > 0)
          {
            break;
          }
        }
      }
      else if (r == 6)
      {
        line_obstacle_avoiding() ;
        line_follow_obstacle();
      }
            else if (r == 7)
      {
        while(1)
        {
 //         bluetooth();
          byte r = push(3);
          if (r > 0)
          {
            break;
          }
        }
      }
    }
    homescreen();

  }
}


String menu_list(byte a) {
  if (a == 1)       return "Calibration         ";
  else if (a == 2)  return "Check Sensor        ";
  else if (a == 3)  return "Line follow left     ";
   else if (a == 4)  return "Line Follow right   ";
  else if (a == 5)  return "Sonar check         ";
  else if (a == 6)  return "Line Follow obstacle";
  else if (a == 7)  return "Bluetooth          ";
  else if (a == 8)  return "menu seven        ";
  else if (a == 9)  return "menu eight        ";
  else if (a == 10)  return "menu nine         ";
  else if (a == 11) return "menu ten          ";
  else if (a == 12) return "menu eleven       ";
}


byte menu() {
  display.set1X();
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 12;
  bool u_flag = 0, d_flag = 0;
  while (1) {
    if (temp != ind) {
      temp = ind;
      for (byte i = 0; i < 8 ; i++) {
        (i == ind - base) ? display.setInvertMode(1) : display.setInvertMode(0);
        text(String(i + base) + ") " + menu_list(i + base), 0, i);
      }
    }

    byte enc = encRead();
    if (enc) {
      if (enc == 1) {
        ind++;
        if (ind > limit) {
          ind = 1;
          base = ind;
          peak = base + 7;
        }
        else if (ind > peak) {
          peak = ind;
          base = peak - 7;
        }
      }

      else {
        ind--;
        if (ind < 1) {
          ind = limit;
          peak = ind;
          base = peak - 7;
        }
        else if (ind < base) {
          base = ind;
          peak = base + 7;
        }
      }
    }

    byte r = push(sw);
    if (r) {
      if (r == 1) return ind;
      else return 0;
    }
  }
}
void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}
