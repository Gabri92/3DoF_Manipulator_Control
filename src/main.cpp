/**
 * @file main.cpp
 * @author Gabriele Baldi (gabriele.baldi.92@gmail.com)
 * @brief 
 * 
 * Control software of a 3 DoF manipulator. The control of a vacuum pump, mounted
 * at the end effector, and the communication with a cartesian manipulator are 
 * implemented within the code
 * 
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <init_setup_manipulator.cpp>
#include <motor_control.cpp>
#include <input.cpp>

void setup()
{
  init_setup();
  endStrokeInit();
}

void loop()
{ 
  //while (Serial1.available() == 0){}
  serialInput();
  keyboardInput();
  
  unsigned long time_now = millis();

  // Automatic print 
  if(time_now - time_print > 50 && flag_print == true)
  {
    print();
    time_print = time_now;
  }
  // Automatic pump activation
  if (flag_pump_auto == true && (time_now - time_pump) >= 20000 )
  {
    digitalWrite(PIN_PUMP,HIGH);
    delay(1000);
    digitalWrite(PIN_PUMP,LOW);
    time_pump = time_now;
  }
}