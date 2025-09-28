  **Motivation**

A dobsonian telescope is an alt-azimuthal telescope, which in simpler terms translates to up-down, left-right movements. Although this makes controlling the telescope in a very intuitive manner, by pushing/pulling the scope with your hands to a determined position until it reaches the target, this is generally acceptable in lower magnifications. Once you want to observe a target that requires high magnification, say by 300x, every minor adjustment can make your target slip out of view.
Even more so, manual alt-azimuthal telescopes are not designed for astro-photography in mind, since these "hand-made" adjustments result in poor image/video captures due to poor tracking. So, there comes a desire to always maintain a target in frame when taking long exposures photographs, by making the desired target to always stay centered by rotating the telescope in a way that counteracts the earth's rotation. Thus, there comes my attempt at building an equatorial platform.

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
  - 1000uF Capacitor for battery decoupling mechanism

 **Circuit Diagram**
 
  <img width="1200" height="680" alt="EQPlatform-Circuit" src="https://github.com/user-attachments/assets/a53e15a0-4818-447c-bde8-366302c484de" />


  **Procedure**

- To start designing you equatorial platform, you must first calculate the height of the center of gravity (COG) of the whole configuration. We do this, because when the combined COG of the telescope and the platform is precisely aligned with the platform's virtual polar axis, the force required from the stepper motor is at its lowest, since it only needs to supply a small amount of torque necessary to initiate and maintain the slow, steady motion of the Earth's rotation rate. In addition, this will reduce any additional vibrations from the stepper motor when it exerts additional force when driving the platform, since we want to keep these to a minimum, and we also want to keep a constant load throughout the whole tracking duration (if the COG is off-axis, the load might differ at different points of this system).

  - Breaking down the whole construction in smaller components, we have:
    - Optical Tube Assembly - OTA
    - Rockerbox
    - Equatorial Platform (rough estimate)

- In order to determine the COG height, so that the telescope won't tip over and fall when on top of the platform, we must first measure the weight of these components, as well as the COG for each.
  - For the OTA, after measuring it's weight, the COG height of this component is the same height as when this is placed on top of the Rockerbox.
  - Regarding the Rockerbox's COG height, we can approximately measure it by placing the box on it's side, inserting a rolling tube underneath and adjusting its position so that it hardly tips over. Once we've reached this point, we can measure the COG height of this component.
  - Lastly, we need a rough estimate regarding the weight and height of the equatorial platform.


- After obtaining these values, we want to minimize the workload of our stepper motor, so that for a given COG height, we want the torque value to be as close to zero as possible.
  - We can use the following formula, in Excel, where we can change the COG's height to obtain a torque value near 0:
    - Torque = (-COG_Height + OTA_COG_Height)*OTA_Weight + (-COG_Height + Rockerbox_COG_Height)*Rockerbox_Weight + (-COG_Height + Platform_Height)*Platform_Weight     
      <img width="398" height="228" alt="image" src="https://github.com/user-attachments/assets/73e2232a-a994-4cae-88d4-a34aadc3e9ce" />

  **CAD Design**

- Link for CAD Design: https://cad.onshape.com/documents/fc487dd168582be484b07ebc/w/f0959319fd26a467e85e2940/e/d81d08c65cf4e3800adc4ea7?renderMode=0&uiState=68d97b1c6579d91bec6f8a1c

- After determining the COG height, we can start designing the whole structure in CAD, and figure out the circular segments from which the platform will rest upon, which we can then print the result with a 3D printer for later construction:
  
  <img width="895" height="606" alt="image" src="https://github.com/user-attachments/assets/4b7e6db6-7ee6-49df-966f-7cca60d97900" />
    
- Where we define the circular segments, from which our platform will slide upon

  <img width="871" height="673" alt="image" src="https://github.com/user-attachments/assets/0873b6c2-b37f-4931-af0d-b696bcad239e" />
    
- And we also design the remainder of the components for our platform:

  <img width="858" height="316" alt="image" src="https://github.com/user-attachments/assets/42dc65b6-3fc7-47c4-9114-ab1e38b91a61" />


 **Final Design**
 
 After 3D printing the circular segments, we can resort to some woodworking to cut out the plywood to the desired lengths, apply some layers of weather-resistant coating and paint, then proceed to glue the 3D prints in place with epoxy resin, and contain the electronics inside a case, shielded from the elements 

![eq-1](https://github.com/user-attachments/assets/a33559cc-e56b-469a-b295-a68be322b457)
![eq-2](https://github.com/user-attachments/assets/86a68d73-5a15-4989-a44b-4606af4d21b3)
![eq-3](https://github.com/user-attachments/assets/52d116d9-d700-47d7-bc3d-88154c23ee43)
![eq-4](https://github.com/user-attachments/assets/6e2b6ee3-3794-4c23-90c6-80e23f9d329f)


