# handheld-ffb-wheel
An Arduino Leonardo-based steering wheel controller, in a handheld form factor with force-feedback

Software built using [YukMingLaw/ArduinoJoystickWithFFBLibrary](https://github.com/YukMingLaw/ArduinoJoystickWithFFBLibrary)

## Plans
- 3D printed shell, trigger mechanisms, wheel
- Potentiometers for each of steering, throttle, brake, clutch, and handbrake
- 2d joystick for camera control

## Parts
- Arduino Leonardo
- A random dc motor I had laying around
- [DRV8871 DC Motor Driver](https://www.adafruit.com/product/3190#tutorials)
- 4x 330 Ohm Resistors
- 1 LED
- [12V DC Power Supply, with barrel jack cut off](https://www.adafruit.com/product/798)
- [USB C to USB Micro cable](https://www.adafruit.com/product/3878)
- [5x 10k Potentiometer](https://www.adafruit.com/product/562)
- [3x Tactile Button Switch (this is a pack of 20, you only need 3)](https://www.adafruit.com/product/367#tutorials)
- [2 Axis Joystick](https://www.adafruit.com/product/245)

## Layout
1 motor (PWM output):
1. feedback motor on the wheel - direction, speed

1 LED (PWM/Digital output):
1. power/status - Digital

5 pots (Analog input):
1. main steering
2. throttle
3. brake
4. clutch
5. handbrake

1 joystick (2x analog input):
1. camera controls on 2 axis joystick

3 buttons (Analog input):
1. reset
2. shift up
3. shift down

## Pinout
|Function|Type|Pin|
|-|-|-|
|Wheel motor output 1|PWM Out|D3
|Camera left/right|Analog In|A7 (D6)
|Camera up/down|Analog In|A8 (D8)
|Shift Up|Analog In|A9 (D9)
|Shift Down|Analog In|A10 (D10)
|Power/status light|Digital Out|D11
|Reset Button|Analog In|A11 (D12)
|Wheel motor output 2|PWM Out|D13
|Steering|Analog In|A0
|Throttle|Analog In|A1
|Brake|Analog In|A2
|Clutch|Analog In|A3
|Handbrake|Analog In|A4

![image](https://github.com/user-attachments/assets/5b287fa2-1910-443b-b6c6-acd5bc2f8bd9)



