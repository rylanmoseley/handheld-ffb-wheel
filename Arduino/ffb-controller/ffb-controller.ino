#include <Joystick.h>
#include "DigitalWriteFast.h"

#define ENCODER_MAX_VALUE 1023
#define ENCODER_HALF_VALUE 511
#define ENCODER_MIN_VALUE 0

int32_t forces[2] = { 0 };
Gains gains[2];
EffectParams effectparams[2];

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   7, 0,                  // Button Count, Hat Switch Count
                   true, true, true,      // X, Y, and Z
                   true, true, false,     //  Rx, Ry, and Rz
                   false, false,          // rudder and throttle
                   false, false, false);  // accelerator, brake, and steering

volatile long value = 0;
int32_t g_force = 0;

unsigned long upshiftDebounceTime = 0;
unsigned long downshiftDebounceTime = 0;

unsigned int ffbSlot = 0;

int lastUpshiftState = LOW;
int lastDownshiftState = LOW;

int upshift = LOW;
int downshift = LOW;

unsigned long debounceDelay = 50;  // ms

void setup() {
  Serial.begin(115200);

  gains[0].totalGain = 50;
  gains[0].springGain = 80;
  gains[1].totalGain = 50;
  gains[1].springGain = 80;

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
  TCCR3A = 0;  //set TCCR1A 0
  TCCR3B = 0;  //set TCCR1B 0
  TCNT3 = 0;   //counter init
  OCR3A = 399;
  TCCR3B |= (1 << WGM32);  //open CTC mode
  TCCR3B |= (1 << CS31);   //set CS11 1(8-fold Prescaler)
  TIMSK3 |= (1 << OCIE3A);
  sei();
}

ISR(TIMER3_COMPA_vect) {
  Joystick.getUSBPID();
}

void loop() {
  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));
  Joystick.setZAxis(analogRead(A2));
  Joystick.setRxAxis(analogRead(A3));
  Joystick.setRyAxis(analogRead(A4));

  signed int x = analogRead(A7) - ENCODER_HALF_VALUE;
  signed int y = analogRead(A8) - ENCODER_HALF_VALUE;

  signed int x1 = x > 0 ? x : 0;
  signed int x2 = x < 0 ? abs(x) : 0;

  signed int y1 = y > 0 ? y : 0;
  signed int y2 = y < 0 ? abs(y) : 0;

  Joystick.setButton(3, millis() % ENCODER_HALF_VALUE < x1 && x1 > 100);
  Joystick.setButton(4, millis() % ENCODER_HALF_VALUE < x2 && x2 > 100);
  Joystick.setButton(5, millis() % ENCODER_HALF_VALUE < y1 && y1 > 100);
  Joystick.setButton(6, millis() % ENCODER_HALF_VALUE < y2 && y2 > 100);

  effectparams[ffbSlot].springMaxPosition = ENCODER_MAX_VALUE;
  effectparams[ffbSlot].springPosition = analogRead(A0);

  Joystick.setEffectParams(effectparams);
  Joystick.getForce(forces);

  int upshiftRead = digitalRead(A9);
  int downshiftRead = digitalRead(A10);

  if (upshiftRead != lastUpshiftState) {
    upshiftDebounceTime = millis();
  }
  if (downshiftRead != lastDownshiftState) {
    downshiftDebounceTime = millis();
  }

  if ((millis() - upshiftDebounceTime) > debounceDelay) {
    upshift = upshiftRead;
  }
  if ((millis() - downshiftDebounceTime) > debounceDelay) {
    downshift = downshiftRead;
  }

  Joystick.setButton(0, digitalRead(A11));
  Joystick.setButton(1, upshift);
  Joystick.setButton(2, downshift);

  lastUpshiftState = upshiftRead;
  lastDownshiftState = downshiftRead;

  // status light
  digitalWrite(11, HIGH);

  if (abs(forces[0]) < abs(forces[1])) {
    ffbSlot = 1;
  } else {
    ffbSlot = 0;
  }

  // adds a 1-unit zone in which the motor will stop at either edge
  // the >/<s may need swapped depending on orientation
  if (forces[ffbSlot] > 0 && analogRead(A0) < ENCODER_MAX_VALUE) {
    analogWrite(3, abs(forces[ffbSlot]));
    digitalWrite(13, LOW);
  } else if (analogRead(A0) > ENCODER_MIN_VALUE) {
    analogWrite(13, abs(forces[ffbSlot]));
    digitalWrite(3, LOW);
  } else {
    digitalWrite(3, LOW);
    digitalWrite(12, LOW);
  }
}
