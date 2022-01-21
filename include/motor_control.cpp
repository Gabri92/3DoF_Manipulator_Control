#include "motor_control.h"

void controlLoop()
{
    // position error
    pos_err = pos_targ - pos_new;

    // averaged pos_dot
    pos_dot_avg = pos_dot_int / pos_dot_count;

    // counter restart
    pos_dot_int = 0;
    pos_dot_count = 0;

    // speed error
    pos_dot_err = (pos_err * KP_POS) + pos_dot_targ - pos_dot_avg;

    // control action
    prop = (pos_dot_err) * KP_POS_DOT;         // proportional
    integral = pos_dot_err_int * KI_POS_DOT; // integral

    u = prop + integral;
}

void directionControl()
{
  // direction control
  if (u > 0)
  {
    digitalWrite(PIN_DIRECTION, LOW);
  }
  else if (u < 0)
  {
    digitalWrite(PIN_DIRECTION, HIGH);
  }
}

void Move_CC()
{
  pos_targ = map(angle, 0 , 720, 0, 2*encoder_conv);

  t_micros_new = micros();

  pos_new = myEnc.read();
  //round_perc = (int)((rounds - (int)rounds)*100);
  //pos_new = round_perc * 360/100;

  if (t_micros_new - t_micros_old > 100)
  {
    // sampling time in microsecods
    dt_micros = t_micros_new - t_micros_old;

    t_micros_old = t_micros_new;
    // speed update
    dx = pos_new - pos_old;
    pos_dot = dx / dt_micros;
    // pos_dot counter for averaging
    pos_dot_int = pos_dot_int + pos_dot;
    pos_dot_count++;
    // update old values
    pos_old = pos_new;
  }

  if (t_micros_new - t_micros_control >= 2000)
  {
    // time control update
    dt_micros_control = t_micros_new - t_micros_control;
    t_micros_control = t_micros_new;

    controlLoop();
    directionControl();
    
    if(u > 255)
    {
      u = 255;
      pwm = int(abs(u));
      pos_dot_err_int = pos_dot_err_int;
    }
    else if(u < -255)
    {
      u = 255;
      pwm = int(abs(u));
      pos_dot_err_int = pos_dot_err_int;
    }
    else if(abs(u) > .001)
    {
      pwm = int(abs(u));                                              // PWM conversion
      pos_dot_err_int = pos_dot_err * dt + pos_dot_err_int; // integrate
    }   
  }

  // saturation control
  if (pwm > 255)
  {
    //analogWrite(PIN_ENABLE, 255);
    pwm = 255;
  }
  else if (pwm < 0 || abs(u-u_old) > 50)
  {
    //analogWrite(PIN_ENABLE, 0);
    pwm = 0;
  }
  
  u_old = u;

  // write pwm to motor
  analogWrite(PIN_ENABLE, pwm);
}

void endStrokeInit()
{
    digitalWrite(pin_Joint1,LOW);
    delay(100);
    digitalWrite(pin_Joint2,LOW);
    delay(100);

    while(flag_init_J3 == true)
    {
      digitalWrite(PIN_DIRECTION,HIGH);
      analogWrite(PIN_ENABLE,255);
      if (digitalRead(PIN_INT_J3) == LOW)
      {
        Serial.println("Initialized J3 ...");
        analogWrite(PIN_ENABLE,0);
        myEnc.write(0);
        flag_init_J3 = false;
      }
    }

    angle = 20;
    while(myEnc.read() < angle * (2*encoder_conv)/720)
      {
        Move_CC();
      }
    analogWrite(PIN_ENABLE,0);
    myEnc.write(0);

    while (flag_init_J2 == true)
    {
      Joint2.move(5000);
      //Joint2.setSpeed(600);
      if (digitalRead(PIN_INT_J2) == LOW)
      {
          Serial.println("Initialized J2 ...");
          Joint2.setSpeed(0);
          Joint2.runSpeed();
          flag_init_J2= false;
      }
      Joint2.run();
    }

    Joint2.setCurrentPosition(0);

    Joint2.moveTo(-100);
    while(Joint2.distanceToGo() != 0)
    {
      Joint2.runToPosition();
    }

    while (flag_init_J1== true)
    {
        Joint1.move(-5000);
        //Joint1.setSpeed(-1000);
        if (digitalRead(PIN_INT_J1) == LOW)
        {
            Serial.println("Initialized J1 ...");
            Joint1.setSpeed(0);
            Joint1.runSpeed();
            flag_init_J1= false;
        }
        Joint1.run();
    }

    Joint1.setCurrentPosition(0);

    Joint1.moveTo(147);
    while(Joint1.distanceToGo() != 0)
    {
      Joint1.runToPosition();
    }

    Joint1.setCurrentPosition(0);
    Joint2.setCurrentPosition(0);

    delay(500);

    //attachInterrupt(digitalPinToInterrupt(PIN_INT_J1),emergency_Stop,LOW);
    //attachInterrupt(digitalPinToInterrupt(PIN_INT_J2),emergency_Stop,LOW);
    //attachInterrupt(digitalPinToInterrupt(PIN_INT_J3),emergency_Stop,LOW);
}

void emergency_Stop()
{
  Joint1.stop();
  Joint2.stop();
  analogWrite(PIN_ENABLE,0);
}

void print()
{
  Serial.print(myEnc.read());
  Serial.print("\t");
  Serial.print(pwm);
  Serial.print("\t");
  Serial.print(u_old);
  Serial.print("\t");
  Serial.print(u);
  Serial.print("\t");
  Serial.print(pos_dot_err,5);
  Serial.print("\t");
  Serial.print(pos_dot_err_int,5);
  Serial.print("\t");
  Serial.print(pos_err,5);
  Serial.print("\n");
}