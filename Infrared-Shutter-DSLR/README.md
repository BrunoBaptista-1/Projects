When taking pictures through a telescope, you want to insert as little vibration as possible. In cases of telescopes with smaller focal lengths, which usually results in a greater field of view, such vibrations are less noticeable. 
However, in cases with telescope with high focal lengths (e.g. 1200mm), each movement is amplified and image shifts due to vibrations are also more noticeable, so we want to minimize these occurrences.

Thus, for a simple manual telescope and a mirrorless DSLR camera, the objective was to create a device that, could utilize the DSLR's infrared receiver in its favor, being able to take pictures with a press of a button, without touching the camera or the telescope.

**Build Materials**

- Arduino Nano
- LED Infrared emitter
- Red LED diode (2x)
- Push Button
- Toggle Switch
- 9V Battery and 9V battery holder
- 1k Resistor (3x)
- 330 Ohm Resistor


A simple wiring diagram is shown below, showcasing how it was assembled:
  <img width="380" height="340" alt="DSLR-Shutter-Circuit" src="https://github.com/user-attachments/assets/a3266ac9-dcac-4356-afd1-4cade10a6103" />


In order to create the command pulse to take the photo, we would first need to analyze the commercially available ML-L3 remote shutter, to which will be recreated with the arduino nano. In order to do this, the arduino  needed to generate a 38kHz infrared carrier frequency, which is found in infrared remotes, performed by the "takePicture" Function. This replicates the signal needed for the DSLR to take the picture, with a press of the button.
