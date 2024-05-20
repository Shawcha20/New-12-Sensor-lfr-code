void line_follow_right()
{
 
  int pos=0;
  int y=0;
  side='r';
  while(1)
  {
        byte r=push(3);
        if(r>0)
        {motor(0,0);
          break;
        }
   reading();
      if(sum>8 && sum<12 && digitalvalue[0]==1 && digitalvalue[11]==1)
   {
    uint32_t timer = millis();
    while ((digitalvalue[11] || digitalvalue[0]) && sum < 12) {
      reading();
      if (millis() - timer > i_timer) {
        i_mode = !i_mode;
        digitalWrite(led, i_mode);
        cross = 's'; //to avoid any unnecessary sharp turns
        break;
      }
    }
    flag = 'l'; //specific guided turn for Y section
   }
    if(sum==0)
    {
      Serial.print("flag: ");
      Serial.println(flag);
      if(flag!='s'){
      flag=='l'? (motor(-14*spl, 14*spr)):(motor(14*spl, -14*spr));
      while(digitalvalue[4]!=1 &&digitalvalue[5]!=1&&digitalvalue[6]!=1)reading();
      flag='s';
      }
      else if( flag=='s' && pos>-8 && pos<8)
      {
      //motor(0,0);delay(20);
        m3=millis();
        // code for u turn 
        while(sum==0){
          reading();
        if(millis()-m3 >u_turndelay)
        { 
          side=='l'? (motor(-14*spl, 14*spr)):(motor(14*spl, -14*spr));
           while(digitalvalue[4]!=1 &&digitalvalue[5]!=1 &&digitalvalue[6]!=1)reading();
           pos=0;
           break;
        }
        }
      }
    }
    if (sum == 3 || sum == 2||sum==1) {
      Serial.print("cross: ");
      Serial.println(cross);
      if(cross!='s')
      {
        cross=='l'? (motor(-14*spl, 14*spr)):(motor(14*spl, -14*spr));

        while(digitalvalue[4]+digitalvalue[5]+digitalvalue[6]+digitalvalue[7]>0 )reading();  // it is a crucial loop for maze
         while(digitalvalue[4]==0 &&digitalvalue[5]==0&&digitalvalue[6]==0)reading();
         cross='s';   
      }
      // straight
      if (digitalsum == 0b000011100000) {
        if (pos != 0) {
          (pos >0) ? motor(-17 * spl, 17 * spr) : motor(17 * spl, -17 * spr);
          (pos >0) ?delay(pos*6): delay(-pos*6);
          pos = 0;
        }
        motor(23 * spl, 23 * spr);
      }
      // right side portion
      else if (digitalsum == 0b000001100000) {//1
        motor(23 * spl, 22 * spr);
       if(pos<1) pos = 1;
      } else if (digitalsum == 0b000001110000) {//2
        motor(23 * spl, 20 * spr);
        if(pos<2)pos = 2;
      } else if (digitalsum == 0b000000110000) {//3
        motor(23 * spl, 18 * spr);
        if(pos<3)pos = 3;
      } else if (digitalsum == 0b000000111000) { //4
        motor(23 * spl, 16 * spr);
        if(pos<4)pos = 4;
      } else if (digitalsum == 0b000000011000) { //5
        motor(23 * spl, 14 * spr);
        if(pos<5)pos = 5;
      } else if (digitalsum == 0b000000011100) { //6
        motor(23 * spl, 12 * spr);
        if(pos<6)pos = 6;
      } else if (digitalsum == 0b000000001100) { //7
        motor(23 * spl, 10 * spr);
        if(pos<7)pos = 7;
      }
      else if (digitalsum == 0b000000001110) { //8
        motor(23 * spl, 8 * spr);
        if(pos<8)pos = 8;
      }
        else if (digitalsum == 0b000000000110) { //9
        motor(23 * spl, 6 * spr);
        if(pos<9)pos = 9;
      }
       else if (digitalsum == 0b000000000111) { //10
        motor(23 * spl, 4 * spr);
        if(pos<10)pos = 10;
      }
       else if (digitalsum == 0b000000000011) { //11
        motor(23 * spl, 2* spr);
        if(pos<11)pos = 11;
      }
       else if (digitalsum == 0b000000000001) { //12
        motor(23 * spl, 0* spr);
        if(pos<12)pos = 12;
      }
      // left side portion
      else if (digitalsum == 0b000011000000 ) { //1
        motor(18 * spl, 23 * spr);
        if(pos>-1)pos = -1;
      } else if (digitalsum == 0b000111000000) { //2
        motor(16 * spl, 23 * spr);
        if(pos>-2)pos = -2;
      } else if (digitalsum == 0b000110000000) { //3
        motor(14 * spl, 23 * spr);
        if(pos>-3)pos = -3;
      } else if (digitalsum == 0b001110000000) { //4
        motor(12 * spl, 23 * spr);
        if(pos>-4)pos = -4;
      } else if (digitalsum == 0b001100000000) { //5
        motor(10 * spl, 23 * spr);
        if(pos>-5)pos = -5;
      } else if (digitalsum == 0b011100000000) { //6
        motor(8 * spl, 23 * spr);
        if(pos>-6)pos = -6;
      } else if (digitalsum == 0b011000000000) { //7
        motor(6 * spl, 23 * spr);
        if(pos>-7)pos = -7;
      }
      else if (digitalsum == 0b111000000000) { //8
        motor(4 * spl, 23 * spr);
        if(pos>-7)pos = -8;
      }
      else if (digitalsum == 0b110000000000) { //9
        motor(2 * spl, 23 * spr);
        if(pos>-7)pos = -9;
      }
      else if (digitalsum == 0b100000000000) { //10
        motor(0 * spl, 23 * spr); 
        if(pos>-7)pos = -10;
      }
    } 
    else if(sum==8||sum==7|| sum==6)
    {
      if(digitalvalue[11]==1 && digitalvalue[10]==1 && digitalvalue[0]==0 && digitalvalue[1]==0 && digitalvalue[6]+digitalvalue[5]+digitalvalue[4]>0)
      {
        flag='r';
        if(side =='r')
        {
        while(digitalvalue[11]==1  && digitalvalue[0]==0)reading();
        if(digitalvalue[0]==0)
        {
          delay(turn_delay); //robot will go some distance forward for good turning
          reading();
          if(sum!=0) // if
          {
            cross='r';
          }
        }
        }
      }
      else if(digitalvalue[0]==1 && digitalvalue[1]==1 && digitalvalue[11]==0 && digitalvalue[10]==0&& (digitalvalue[6] +digitalvalue[5]+digitalvalue[4]>0))
      {
        flag='l';
        if(side=='l')
        {
         while(digitalvalue[11]==0 && digitalvalue[0]==1)reading();
        if(digitalvalue[11]==0)
        {
          delay(turn_delay);
          reading();
          if(sum!=0)cross='l';
        }
        }
      }
      m1= millis();
    }
    m2= millis();
     if(m2-m1>500)flag='s';
    else if(sum==12)
    {
     delay(100);
     reading();
     if(sum==12){
      motor(0,0);
     while(sum==12)
     reading();
     delay(1000);
     }
     else if(sum!=0)   //if cross section detected
     {
      cross='s';
     }
     else if(sum==0)
    {
      flag=side;
      m1= millis();
    }
    }
}
}
