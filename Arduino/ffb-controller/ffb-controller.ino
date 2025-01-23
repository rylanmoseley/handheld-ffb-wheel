#include <Joystick.h>
#include "DigitalWriteFast.h"

#define ENCODER_MAX_VALUE 1023
#define ENCODER_MIN_VALUE 0

int32_t forces[2]={0};
Gains gains[2];
EffectParams effectparams[2];

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  3, 1,                  // Button Count, Hat Switch Count
  true, true, true,     // X, Y, and Z
  true, true, false,   //  Rx, Ry, and Rz
  false, false,          // rudder and throttle
  false, false, false);    // accelerator, brake, and steering

volatile long value = 0;
int32_t g_force = 0;

void setup() {
  Serial.begin(115200);

  gains[0].totalGain = 50;
  gains[0].springGain = 80;

  Joystick.setXAxisRange(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE);
  Joystick.setYAxisRange(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE);
  Joystick.setZAxisRange(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE);
  Joystick.setRxAxisRange(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE);
  Joystick.setRyAxisRange(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE);
  Joystick.setGains(gains);
  Joystick.begin(true);

  // PWM and Digital outputs
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);

  // Analog Inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  
  cli();
  TCCR3A = 0; //set TCCR1A 0
  TCCR3B = 0; //set TCCR1B 0
  TCNT3  = 0; //counter init
  OCR3A = 399;
  TCCR3B |= (1 << WGM32); //open CTC mode
  TCCR3B |= (1 << CS31); //set CS11 1(8-fold Prescaler)
  TIMSK3 |= (1 << OCIE3A);
  sei();
  
}

ISR(TIMER3_COMPA_vect){
  Joystick.getUSBPID();
}

void loop() {
  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));
  Joystick.setZAxis(analogRead(A2));
  Joystick.setRxAxis(analogRead(A3));
  Joystick.setRyAxis(analogRead(A4));
  
  int x = analogRead(A7);
  int y = analogRead(A8);
  if (x > 400 || y > 400) { // TODO set this with the actual Pots
    Joystick.setHatSwitch(0, atan2(y, x));
  } else {
    Joystick.setHatSwitch(0, -1);
  }

  effectparams[0].springMaxPosition = ENCODER_MAX_VALUE;
  effectparams[0].springPosition = analogRead(A0);

  Joystick.setEffectParams(effectparams);
  Joystick.getForce(forces);

  Joystick.setButton(0, analogRead(A11) > 1000);
  Joystick.setButton(1, analogRead(A9) > 1000);
  Joystick.setButton(2, analogRead(A10) > 1000);

  // status light
  digitalWrite(11, HIGH);
  
  if (forces[0] > 0) {
    analogWrite(3, abs(forces[0]));
    digitalWrite(13, LOW);
  } else {
    analogWrite(13, abs(forces[0]));
    digitalWrite(3, LOW);
  }
}