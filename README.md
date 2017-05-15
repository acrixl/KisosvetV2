# KisosvetV2
Smart LED-light for shoting photo, video, and comfort illumination in home)

Read [About](https://github.com/alicepergatta/KisosvetV2/wiki/About)

More documentation [Kisosvet wiki](https://github.com/alicepergatta/KisosvetV2/wiki)

## Main functionality:

- Modular and customizable architecture, you can make owm custom Kisosvet
- 16-bit PWM brightness regulation, without any flickering
- Color temperature regulation, and white color calibration
- Different LED types for full spectre(WW + NW or WW + CW for example)
- Flickering-free power modules and control circuitry schematic
- DC-DC converter based power modules, which can work at different voltage - in car, at home, everywhere with lithium battery pack.
- STM32 microcontroller as a "brain"
- ESP8266 for networking functionality
- User-friendly control from android-application 
- MQTT support for smart home system
- DS18B20 as a temperature sensor for fan control logic
- Temperature & fan control with overheat protection
- Energy efficiency:each PM can be switched on\off, fan on\off + fan PWM, sleep\standby modes for main chips.
- Network control by web-interface or android application
- Wake-up from internal li-ion battery or external duty supply, and power on external PSU - perfect for use wih ATX PSU by pulling down PS_ON pin.
- Measuring power supply\main battery voltage - you exactly know when battery low.

## My KisosvetV2 configuration(which i build for myself):
- WW + NW 10W LED's
- 4 LED's
- 10W step-down based PM's(for 10W LED's, obviously)
- Supply voltage from 11V to 28V
- 80 mm 12V FAN from CPU cooler


## TODO:

- [ ] Implement authorization on ESP8266
- [ ] Enable and configure WWDG for STM32
- [ ] Add 7-seg display for two-factor auth, system info and other features
- [x] Power Modules schematic 
- [x] Reverse voltage protection
- [x] Power rails schematic
- [x] STM32 board pin assigments
- [x] PWM regulation and calibration(for each PM\LED) functionality
- [x] PM on\off
- [x] Main STM32 project code
- [x] Implement full control over UDP, including transmiting data from device to client application
- [x] Build firmware for ESP8266
- [ ] Add MQTT protocol support 
- [x] Make normal CLI over UART for STM32+ESP8266 interconnect
- [x] Add DS18B20 full functionality 
- [x] Add fan PWM level-shifter and configure TIM2 for it
- [x] Write fan control logic and overheat protection
- [ ] Replace linear VREG's for step-down modules, to achieve bettter energy efficiency
- [ ] Get better LDO VREG's
- [x] Write code for ADC(voltage measuring)
- [ ] Write wake-up and sleep functionality code
- [ ] Make a few variants for device case
- [x] Implement CLI syntax
- [x] Develop android application
- [ ] add external antenna for ESP8266
- [ ] Write logic for manual control by encoders and buttons

## Folders & files description

- stm32 - Keil & STM32CubeMX projects
  I'm using C and C++ in this project.
- schematic - Splan schematic project,
  Splan is pretty easy tool for drawing schematic
  * [ ] learn a better software
- schematic-png - Schematic in PNG images
- esp8266 - code for esp8266
- Photos - photos of project realization, currently there are prototype photos
- PCB - PCB layouts for Kisosvet V2 modules
## FAQ

[Full FAQ](https://github.com/alicepergatta/KisosvetV2/wiki/FAQ)

**Q**: Can i build own Kisosvet but with different LED's and PM's?


**A**: Yes! You just need to reconfigure hardware initialization(manually or in STM32CubeMX) add variables for new LED's\PM's, and if your LED's are less or more powerful - you need to change PM's circuitry(replace DC-DC converter for different type, or maximum power)
If you want much bigger LED quantity - you need more powerful microcontrollers, with more timers and more pins.


**Q**: Which DC-DC type converters can be used for PM's?

**A**:  You can use step-up, step-down, and even SEPIC.
Almost all DC-DC converters have same negative feedback voltage control.
Control circuitry, which i made in Kisosvet suitable for any DC-DC converters with negative feedback voltage control)
(maybe you will need rewrite PWM values calculation, it can be inverted)

**Q**: Which LED types can i use?

**A**: Any) It depends on power modules circuitry(DC-DC converter type), and cooling possibilities(heatsink, fan, and thermal grease).

**Q**: How can you describe a typical Kisosvet build configuration?

**A**: I prefear 10W 12V LED's, 4 pieces placed in chess order(like subpixels). This allows me to use lithium battery pack and typical ATX PSU. Also, i made a 10W PM circuit(see schematic) based on cheap step-down converter.
Despite it's cheapness - it's enough powerfull for 10W LED)



