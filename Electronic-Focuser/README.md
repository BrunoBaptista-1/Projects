When performing visual observations on a telescope, after inserting your desired eyepiece, you generally adjust a focuser's knobs, rotating them up or down, in order to reach focus. This is especially intuitive to adjust when putting your eye close to the eyepiece, but in situations where you want to perform remote adjustments or doing small adjustments when using a camera for fine-tuning the focus, a slight erratic hand movement can slightly remove your desired target out of frame. 
Thus, a desire to create an electric focuser was created, one that could be controlled through a serial terminal via a Bluetooth connection.

By repurposing a powerbank's 18650 Li-Ion battery pack, this could be used to power an ESP32 and also deliver power to a stepper motor driver at the same time. Since I would still like to revert back to fully-manual focusing adjustments, I had to figure out a way to implement a non-permanent solution by creating an adapter to the existing focuser, that could connect to the stepper motor. I figured that, having previously created a removable Tube-Ring in older projects, I could implement a motor outer casing that could attach to it, and could attach a timing belt and pulley system to perform adjustments to the focuser.

Regarding it's electronic features, I would like to be able to charge the battery pack through a type-C connector without opening the case, thus creating a permanent solution. Given that the battery pack's output voltage varies depending on battery capacity, i.e. the voltage is not stable for power delivery, I would also need an additional circuit to deliver a stable output voltage. Regarding it's remote control capabilities, the chosen ESP32 has built-in Bluetooth, so this device was ideal for this purpose. However, since I would like to keep the case as contained (unopened) as possible, I would also need a way to be able to implement a pairing feature, and a way to erase existing connections, so it could pair with new devices.  

**Materials**
- 18650 Li-Ion battery pack (2x, connected in parallel)
- 28byj-48 stepper motor
- 28byj-48 stepper motor driver
- ESP32
- TC4056 Type-C USB-C 5V 1A 18650 Lithium Battery Charger Board with Dual Protection Functions
- MT3608 DC-DC Power Adapter Step Up Module
- Timing belt with pulleys (20 teeth, 5mm)

Case Design:

<img width="553" height="533" alt="Focuser-1" src="https://github.com/user-attachments/assets/30638623-3ab5-40f7-ba5b-cc4ea2e6bbc4" />

<img width="631" height="533" alt="Focuser-2" src="https://github.com/user-attachments/assets/cab684a6-f7f3-4cfb-ad11-c3fe63353751" />

<img width="631" height="533" alt="Focuser-3" src="https://github.com/user-attachments/assets/3771f7c8-a99e-46fc-947d-4c85355eeb0a" />


Focuser Adapter Design:

<img width="660" height="437" alt="Focuser-Adapter-1" src="https://github.com/user-attachments/assets/fdc9f29b-6e10-4e9c-916e-0bc878feb34a" />

<img width="660" height="406" alt="Focuser-Adapter-2" src="https://github.com/user-attachments/assets/fb3717ff-76c8-4cc9-8410-b5e6c906aced" />



Regarding the design of this adapter, since there were no mounting holes, I had to devise a way to connect to the existing focuser wheel. Thus, this "revolver-style" adapter was made, where bolts could be screwed from one side to the other, providing stability and could easily be removable


Electronic Circuit Diagram:
<img width="1020" height="320" alt="circuit" src="https://github.com/user-attachments/assets/3b803f7f-7f0f-476a-bb69-b70ebdf473fd" />



Final Result:

![Focuser-Final-1](https://github.com/user-attachments/assets/31406a1b-c3e8-4c03-92c5-0e930acca3f8)


![Focuser-Final-2](https://github.com/user-attachments/assets/e61dba87-2f47-43ac-97f5-34a2ba95cecb)



**Future Improvements**

Instead of recurring to a timing belt system, a 5mm to 5mm coupler would be the ideal choice, since it would also be easily removable and it would not rely on belt tensioning for better surface adhesion.
Regarding this improvement, no perpendicular forces would be applied to the rotational axis of the stepper motor, such is the case with the belt tensioning system, thus reducing wear and improving longevity.
For this, It would need a complete design overhaul for both the electronic focuser case, and for the tube ring section that locks the electronics in place, lowering the rotational axis to its ideal height.  

An additional improvement could be the addition of an external temperature sensor, regarding temperature compensation during observations, given by the thermal expansion of the Optical Tube Assembly, more specifically its mirrors and metal components, which result in image degradation caused by shifting the focus out of position.
