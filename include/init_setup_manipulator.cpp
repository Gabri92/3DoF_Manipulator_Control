#include <AccelStepper.h>
#include <Encoder.h>

/////////////////////////
// DC MOTOR & PNEUMATICS
#define PIN_ENCODER_A 10
#define PIN_ENCODER_B 11
#define PIN_ENABLE 9
#define PIN_DIRECTION 8
//#define PIN_J1 12
//#define PIN_J2 13
#define PIN_PUMP 6
#define PIN_SWITCH 7
/////////////////////////

/////////////////////////
// STEPPER VARIABLES
#define pin_Joint1 41
#define pin_Joint2 39
#define stepPin1  23
#define dirPin1 25
#define stepPin2 27
#define dirPin2 29
/////////////////////////

/////////////////////////
// INTERRUPTS
int PIN_INT_J1 = 51;
int PIN_INT_J2 = 52;
int PIN_INT_J3 = 53;
// Initialization flags
bool flag_init_J1 = true;
bool flag_init_J2 = true;
bool flag_init_J3 = true;
/////////////////////////

int Joint_1_speed = 800;
int Joint_2_speed = 800;

AccelStepper Joint1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper Joint2(AccelStepper::DRIVER, stepPin2, dirPin2);

// Encoder Library Variables
Encoder myEnc(PIN_ENCODER_B, PIN_ENCODER_A);

void init_setup()
{
    // DC motor init
    pinMode(PIN_ENABLE, OUTPUT);
    pinMode(PIN_DIRECTION, OUTPUT);

    // Pump and switch init
    pinMode(PIN_PUMP, OUTPUT);
    pinMode(PIN_SWITCH,OUTPUT);
    digitalWrite(PIN_SWITCH,HIGH);

    // Stepper init
    pinMode(pin_Joint1,OUTPUT);
    pinMode(pin_Joint2,OUTPUT); 
    digitalWrite(pin_Joint1,HIGH);
    digitalWrite(pin_Joint2,HIGH);

    // Interrupt
    pinMode(PIN_INT_J1, INPUT_PULLUP); // pin di interrupt
    pinMode(PIN_INT_J2, INPUT_PULLUP); // pin di interrupt
    pinMode(PIN_INT_J3, INPUT_PULLUP); // pin di interrupt
    //digitalWrite(PIN_INT_J1,HIGH);
    //digitalWrite(PIN_INT_J2,HIGH);
    //digitalWrite(PIN_INT_J3,HIGH);

    // stepper limit init
    // Set the maximum steps per second:
    Joint1.setMaxSpeed(800);  //30000 //1300 200x step motor max speed 1200 24 V
    Joint2.setMaxSpeed(800); //400 step motor max speed 1600 24 V

    // Set the maximum acceleration in steps per second^2:
    Joint1.setAcceleration(4000); // 4000
    Joint2.setAcceleration(4000);

    Serial.setTimeout(3000);
    Serial.begin(115200);
    Serial1.begin(9600);
}
