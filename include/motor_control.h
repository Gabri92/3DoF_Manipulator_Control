#include <Arduino.h>

// Control flags
bool flag_print = false;
bool flag_pump = false;
bool flag_pump_auto = false;
bool flag_switch = false;
bool flag_com = false;
bool flag_on = false;


// Timing variables
//unsigned long time_now = 0;
unsigned long time_print = 0;
unsigned long time_pump = 0;
unsigned long t_micros_new = 0;
unsigned long t_micros_old = 0;
unsigned long t_micros_control = 0;
unsigned long dt_micros_control = 0;
unsigned long dt_micros = 0;
float dt = 0.01;

// Control variables
double pos_old = 0;
double pos_new = 0;
double pos_targ = 0;
double pos_err = 0;
double pos_dot_int = 0;
double pos_dot = 0;
double pos_dot_avg = 0;
double pos_dot_count = 0;
double pos_dot_err = 0;
double pos_dot_targ = 0;   //impulsi
double pos_dot_err_int = 0;
double dx = 0;

// Actuation variables
float u = 0;
float u_old = 0;
int pwm = 0;
int angle = 0;
int angle_old = 0;
int reading = 0;
float velocity = 0;
int position = 0;
int encoder_conv = 324 * 8 * 4;

// Control law variables
float KP_POS = 0.1;
float KP_POS_DOT = 30;
float KI_POS_DOT = 10;

// KP_POS = 0.1
// KP_POS_DOT = 30
// KI_POS_DOT = 10

float prop = 0;
float integral = 0;

// Functions
void init_setup();
void serialInput();
void keyboardInput();
void controlLoop();
void directionControl();
void Move_CC();
void print();
void emergency_Stop();
