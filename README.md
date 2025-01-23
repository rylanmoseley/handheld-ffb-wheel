# handheld-ffb-wheel
An Arduino Leonardo-based steering wheel controller, in a handheld form factor with force-feedback

Software built using [YukMingLaw/ArduinoJoystickWithFFBLibrary](https://github.com/YukMingLaw/ArduinoJoystickWithFFBLibrary)

## Plans
- 3D printed shell, trigger mechanisms, wheel
- Potentiometers for each of steering, throttle, brake, clutch, and handbrake
- 2d joystick for camera control

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

5 buttons (Analog input):
1. reset - input 1
2. shift up - input 1
3. shift down - input 1

Current measurement for force feedback output (with limiting)

## Software
- 1 motor controller
- 7 axes
- 3 buttons
- 1 led

## Pinout
|Function|Type|Pin|
|-|-|-|
|Wheel motor direction 1|Digital Out|D2
|Wheel motor speed|PWM Out|D3
|Wheel motor direction 2|Digital Out|D4
|Camera left/right|Analog In|A7 (D6)
|Camera up/down|Analog In|A8 (D8)
|Shift Up|Analog In|A9 (D9)
|Shift Down|Analog In|A10 (D10)
|Power/status light|Digital Out|D11
|Reset Button|Analog In|A11 (D12)
|Steering|Analog In|A0
|Throttle|Analog In|A1
|Brake|Analog In|A2
|Clutch|Analog In|A3
|Handbrake|Analog In|A4