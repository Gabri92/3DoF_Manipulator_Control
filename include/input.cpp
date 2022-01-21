void serialInput()
{
  if (Serial1.available() > 0)
  {
    byte serial_data = Serial1.read();
    switch (serial_data)
    {
      case 'h':
      digitalWrite(pin_Joint1,LOW);
      digitalWrite(pin_Joint2,LOW);
      // Avvia la move e si gira verso il rack
      // Estende la slitta e porta la ventosa sul rack dei vetrini
      angle = 350;
      while(myEnc.read() <= angle * ((2*encoder_conv)/720))
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      Joint2.moveTo(150);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      // Attiva lo switch e la pompa
      digitalWrite(PIN_SWITCH,HIGH);
      digitalWrite(PIN_PUMP,HIGH);
      delay(1000);
      // Disattiva temporaneamente la pompa ed imposta l'attivazione periodica automatica 
      digitalWrite(PIN_PUMP,LOW);
      flag_pump_auto = true;
      // Alza il secondo giunto per favorire i movimenti del robot
      Joint2.moveTo(-30);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      // Ritrae la slitta
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      // Porta il giunto 1 in configurazione iniziale
      Joint1.moveTo(1600);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.run();
      }  
      // Abbassa il giunto 2
      Joint2.moveTo(600);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      Serial1.print('1');
      break;

    case '1':
      // Estende la slitta
      angle = 300;
      while(myEnc.read() <= angle * ((2*encoder_conv)/720))
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      break;

    case '2':
      // Ritrae la slitta
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      // Riporta il robot alla configurazione iniziale
      break;
    
    case 'i':
      // Robot initialization
      flag_pump_auto = false;
      digitalWrite(PIN_PUMP,LOW);    
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      Joint2.moveTo(-30);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      Joint1.moveTo(0);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.run();
      }
      Joint2.moveTo(0);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }

      digitalWrite(pin_Joint1,HIGH);
      digitalWrite(pin_Joint2,HIGH);
      break;
    }
  }
}

void keyboardInput()
{
  if (Serial.available() > 0)
  {
    byte serial_data = Serial.read();
    switch (serial_data)
    {
    case 'o':
      flag_on = !flag_on;
      if(flag_on == true)
      {
        Serial.println("Motors ON");
        digitalWrite(pin_Joint1,LOW);
        digitalWrite(pin_Joint2,LOW);
      }
      else
      {
        Serial.println("Motors OFF");
        digitalWrite(pin_Joint1,HIGH);
        digitalWrite(pin_Joint2,HIGH);
      }
      break;
     
    case 'p':
      // Pump activation
      flag_pump_auto = !flag_pump_auto;
      if (flag_pump_auto)
      {
        Serial.println("Pompa attivata");
        flag_pump_auto = true;
      }
      else 
      {
        Serial.println("Pompa disattivata");
        flag_pump_auto = false;
      }
      break;

    case 's':
      // Switch activation
      flag_switch = !flag_switch;
      if (flag_switch)
      {
        digitalWrite(PIN_SWITCH,HIGH);
      }
      else digitalWrite(PIN_SWITCH,LOW);
      break;

    case 'a':
      digitalWrite(pin_Joint1,LOW);
      // Move joint 1 from keyboard
      Serial.println("Insert J1 angle: ");
      reading = Serial.parseInt();
      Joint1.moveTo(reading);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.runToPosition();
      }
      Serial.println("Move completed");
      break;
    
    case 'b':
      digitalWrite(pin_Joint2,LOW);
      // Move joint 1 from keyboard
      Serial.println("Insert J2 angle: ");
      reading = Serial.parseInt();
      Joint2.moveTo(reading);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.runToPosition();
      }
      Serial.println("Move completed");
      break;

    case 'c':
      digitalWrite(pin_Joint2,LOW);
      // Move joint 3 from keyboard
      Serial.println("Insert J3 angle: ");
      angle = Serial.parseInt();
  
      Serial.print("Moving Joint at ");
      Serial.print(angle);
      Serial.println(" degree...");

      if (angle < angle_old)
      {
        while(myEnc.read() > angle * (2*encoder_conv)/720)
        {
          Move_CC();
        }
        analogWrite(PIN_ENABLE,0);
      }
      else if (angle >= angle_old)
      {
        while(myEnc.read() < angle * (2*encoder_conv)/720)
        {
          Move_CC();
        }
        analogWrite(PIN_ENABLE,0);
      }
      angle_old = angle;
      break;

  case 'h':
      digitalWrite(pin_Joint1,LOW);
      digitalWrite(pin_Joint2,LOW);
      // Avvia la move e si gira verso il rack
      // Estende la slitta e porta la ventosa sul rack dei vetrini
      angle = 270;
      while(myEnc.read() <= angle * ((2*encoder_conv)/720))
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      Joint2.moveTo(-50);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      // Attiva lo switch e la pompa
      digitalWrite(PIN_SWITCH,HIGH);
      digitalWrite(PIN_PUMP,HIGH);
      delay(1000);
      // Disattiva temporaneamente la pompa ed imposta l'attivazione periodica automatica 
      digitalWrite(PIN_PUMP,LOW);
      flag_pump_auto = true;
      // Alza il secondo giunto per favorire i movimenti del robot
      Joint2.moveTo(0);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      // Ritrae la slitta
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      // Porta il giunto 1 in configurazione iniziale
      Joint1.moveTo(1600);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.run();
      }  
      // Abbassa il giunto 2
      Joint2.moveTo(-560);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }

      //Serial1.print('1');
      break;

    case '1':
      // Estende la slitta
      angle = 300;
      while(myEnc.read() <= angle * ((2*encoder_conv)/720))
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      break;

    case '2':
      // Ritrae la slitta
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      // Riporta il robot alla configurazione iniziale
      break;

      case '3':
      // Restituisce il vetrino col tessuto
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      Joint2.moveTo(0);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      Joint1.moveTo(800);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.run();
      }  
      break;
    
    case 'i':
      // Robot initialization
      flag_pump_auto = false;
      digitalWrite(PIN_PUMP,LOW);    
      angle = 0;
      while(myEnc.read() >= 10)
      {
          Move_CC();
      }
      analogWrite(PIN_ENABLE,0);
      Joint2.moveTo(-30);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }
      Joint1.moveTo(0);
      while(Joint1.distanceToGo() != 0)
      {
        Joint1.run();
      }
      Joint2.moveTo(0);
      while(Joint2.distanceToGo() != 0)
      {
        Joint2.run();
      }

      digitalWrite(pin_Joint1,HIGH);
      digitalWrite(pin_Joint2,HIGH);
      break;

      case 'r':
        // Print current position 
        Serial.print("Current X position: ");
        Serial.println(Joint1.currentPosition());
        Serial.print("Current Y position: ");
        Serial.println(Joint2.currentPosition());
        flag_print = !flag_print;
        break;


    case 'u':
        // Active communication
        flag_pump_auto = !flag_pump_auto;
        break;
    }
  }
}