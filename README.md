# handheld-ffb-wheel

## Layout
5 motors (PWM output):
1. feedback motor on the wheel - direction, speed
2. haptic motor on the throttle
3. haptic motor on the brake
4. haptic motor on the clutch
5. haptic model on the shell

2 LEDs (PWM/Digital output):
1. power/status - Digital
2. current limiter indicator - PWM

5 pots (Analog input):
1. main steering
2. throttle
3. brake
4. clutch
5. handbrake

5 buttons (Analog input):
1. reset - input 1
2. shift up - input 1
3. shift down - input 1
4. camera left - input 2
5. camera right - input 2

Current measurement for force feedback output (with limiting)

## Pinout
|Function|Type|Pin|
|-|-|-|
|Wheel motor direction 1|Digital Out|D2
|Wheel motor speed|PWM Out|D3
|Wheel motor direction 2|Digital Out|D4
|Throttle haptic output|PWM Out|D5
|Brake haptic output|PWM Out|D6
|Current limit light|Digital Out|D7
|Camera left/right|Analog In|A8 (D8)
|Clutch haptic output|PWM Out|D9
|Shell haptic output|PWM Out|D10
|Power/status light|Digital Out|D11
|Reset/shift up/shift down|Analog In|A11 (D12)
|Steering|Analog In|A0
|Throttle|Analog In|A1
|Brake|Analog In|A2
|Clutch|Analog In|A3
|Handbrake|Analog In|A4
|Feedback current measurement|Analog In|A5

## Shopping List
- Arduino Leonardo
- DC motor
- [Motor controllers - pack of 4](https://www.amazon.com/HiLetgo-Controller-Stepper-H-Bridge-Mega2560/dp/B07BK1QL5T?source=ps-sl-shoppingads-lpcontext&ref_=fplfs&psc=1&smid=A30QSGOJR8LMXA&gQT=2)
- [Power supply x2](https://www.adafruit.com/product/798)
- [USB C to Micro USB cable](https://www.adafruit.com/product/3878)
- [10k Linear Pot x5](https://www.adafruit.com/product/562)
- LEDs x2
- Haptic Motors x4 - TODO
- [Button - pack of 20](https://www.adafruit.com/product/367)