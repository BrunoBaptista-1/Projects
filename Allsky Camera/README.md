**Motivation**

When travelling to a dark sky site, the manual effort required to align a (manual) dobsonian telescope, tracking deep-sky objects, and conducting visual analysis, means that the observer often loses the ability to immerse himself in viewing the "big picture". Thus, there is a clear need for an automated All-Sky camera, that captures the night's progression. By introducing an automated process that takes snapshots at specified intervals, we are able to produce time lapses of the night sky, which are perfect for capturing auroras, as well as capturing easily-missed meteor showers.



**Materials**

- Raspberry Pi 4 Model B 4GB
- Arducam 120 Degree Ultra Wide Angle CS Lens, 3.2mm Focal Length
- Raspberry Pi HQ Camera
- Heat sink
- Acrylic Dome
- Waterproof Junction Box
- M2.5 Nylon standoffs, nuts and bolts
- Black Matte Paint
- Rubber Flush Pipe Connector
- Acrylic Sheet
- 1/4-20 UNC Threaded Insert
- 20000mAh Powerbank
- Tripod
- Fine Sandpaper
- Velcro
- Epoxy Glue

NAS Storage Integration
- 2 VPN capable routers
- Raspberry Pi 5 8GB
- Dedicated storage (e.g. 1TB)




**Procedures**

- On the top of the junction box, make holes for the Arducam camera lens and acrylic dome
- Lightly sand the exterior of the junction box with fine-grit sandpaper to improve paint adhesion and apply several coats of matte black paint, to minimize light reflections.
- Mount the camera on top of the box, and then cover with the acrylic dome and the rubber flush pipe connector to make a seal 
- Strap two velcro strips on the bottom of a raspberry pi case and on the inside of the junction box
- Cut an acrylic sheet according to the width and length of the junction box, and drill mounting holes (Note: make an extra mounting hole in the middle of the acrylic sheet, for the tripod mount)
- Use the epoxy glue to attach the 1/4-20 UNC Threaded Insert to the acrylic sheet
- Mount the acrylic sheet on the bottom side of the box

  In the end, you would have something similar:

  <img width="747" height="921" alt="Untitled design (1)" src="https://github.com/user-attachments/assets/30cc3be2-6598-4998-94dc-70fc01cc266c" />

![a3ee8742-2a5f-4a26-b131-f56f7be867be](https://github.com/user-attachments/assets/e546b9dd-e0eb-43a2-b3b1-f222c079edd0)




**Network Configuration**

In order to remotely capture snapshots and store them inside a NAS storage, it is required to establish a VPN tunnel between both devices. By using two VPN-capable routers, we implement a site-to-site VPN. This ensures that both devices (Allskyy camera and NAS) are visible to one another, and can exchange traffic. In order to add an additional layer of protection, and exchange data safely, all traffic is sent using the SFTP protocol. All snapshots are replicated locally on the all-sky camera, for extra redundancy. The following image represents a very high-level network topology: 

<img width="872" height="187" alt="Untitled Diagram drawio" src="https://github.com/user-attachments/assets/17f0af98-1720-4b4f-a736-b6a1d57807bc" />




**Outcome**

![image-20250715100151](https://github.com/user-attachments/assets/b3a376ae-06e3-4a4d-9c4a-c2607c2e2a06)



**Final Considerations and Improvements**

- A Power-over-Ethernet module could be implemented, for a more permanent and not-so remote approach (e.g. deploying on the rooftop of a house)
- Adding solar panels along with a battery management system would be ideal for a more permanent and remote solution (e.g. in the middle of a field)
- To remove the camera, the dome must first be removed, which can expose the camera and the on-board computer to water and humidity. To prevent this, it should be designed a dedicated case in CAD software that could easily remove the system (raspberry pi + camera) from below, without removing the acrylic dome.
- The camera lens should be positioned as close to the dome's curvature as possible to reduce lens glare, minimizing distortion and reducing the angle at which light can reflect back into the sensor
- A dew heater should be implemented around the lens in the dome area, along with better insulation, to prevent condensation when placed in humid areas. Note: the heater module should't be too close to the camera module, as excessive heat can generate thermal noise
