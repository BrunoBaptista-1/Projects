A dobsonian telescope is an alt-azimuthal telescope, which in simpler terms translates to up-down, left-right movements. Although this makes controlling the telescope in a very intuitive manner, by pushing/pulling the scope with your hands to a determined position until it reaches the target, this is generally acceptable in lower magnifications. Once you want to observe a target that requires high magnification, say by 300x, every minor adjustment can make your target slip out of view.
Even more so, manual alt-azimuthal telescopes are not designed for astro-photography, since these "hand-made" adjustments result in burred images due to poor tracking. So, there comes a desire to always maintain a target in frame when taking long exposures photographs, by making the desired target to always stay centered by rotating the telescope in a way that counteracts the earth's rotation. Thus, there comes my attempt at building an equatorial platform.

The principle behind it is somewhat simple. This platform consists of two parts, a top board and a ground board, where the first will rest upon. It's axis of rotation is parallel to the earth's polar axis, thus being equatorially mounted. From where I usually perform observations, I have set the pivoting axis to a 40 degrees, since these locations stay approximately within the 40 degrees latitude.



**Platform Materials**
- 15mm Plywood
- ASA Filament, for the North and South Segments and for the roller bearing supports
- Nema 17 Stepper Motor L=39mm Gear Ratio 50:1 High Precision Planetary Gearbox
- 8mm to 8mm Shaft coupler
- TMC2209 stepper motor driver
- 8mm solid stainless steel tubes
- 12V 7A Battery Unit
- Round Spirit Leveler, for adjusting the platform by rotating its rubberized feet
- Compass for Polar Alignment
- In the black box, there is an Arduino Uno connected to the stepper motor driver, which everything is powered through a single battery unit
  - 6 Functional Buttons: "Manual Start/Stop" button, "Enter/Apply Settings" button, Decrease and Increase speed increment buttons (Adjusting speed in order of magnitudes of 1, 10 or 100) , and for the final two buttons I can increase or lower the speed being applied.
  - LCD Display, from which I can observe the tracking status, and see the configured speed being applied.
  - A switch for powering on/off the LCD backlight, so I can observe without light emission from the display.
  - Another switch for powering on/off a 5V dc Fan, for cooling the arduino and the stepper motor driver inside.
  - End stop in front of the box, where the top platform will hit and thus ending the tracking process, coming to a stop so it can be manually reset and begin tracking.
  - A battery percentage indicator
  - 220nF Capacitor for battery decoupling mechanism
 


![eq-1](https://github.com/user-attachments/assets/a33559cc-e56b-469a-b295-a68be322b457)
![eq-2](https://github.com/user-attachments/assets/86a68d73-5a15-4989-a44b-4606af4d21b3)
![eq-3](https://github.com/user-attachments/assets/52d116d9-d700-47d7-bc3d-88154c23ee43)
![eq-4](https://github.com/user-attachments/assets/6e2b6ee3-3794-4c23-90c6-80e23f9d329f)


