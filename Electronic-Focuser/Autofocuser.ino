#include <Stepper.h>
#include "BluetoothSerial.h"
#include "nvs_flash.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif


const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


// initialize bluetooth 
BluetoothSerial SerialBT;


//Define Button with long press feature
#define BUTTON_PIN 13 // Re-Enter Pairing Mode (Short Press), Erase all Connections (Long Press)
#define SHORT_PRESS_DURATION 500
#define LONG_PRESS_DURATION 3000

bool button_pressed = false;
unsigned long buttonPressStartTime = 0;

void setup() {

  // initialize the serial port
  Serial.begin(115200);

  // set speed at 5 rpm
  myStepper.setSpeed(5);

  //Set Pairing/Erase button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  //set bluetooth name
  SerialBT.begin("ELECTRONIC-FOCUSER");
  
}

int calculate_steps(float millimeters){ //calculate, for given millimeters of travel, the necessary steps for the motor 
  return round((stepsPerRevolution * millimeters)/12.5);
}

void loop() {

  if (SerialBT.available()) {

    float distance = SerialBT.parseFloat(); //parses float values from serial input

    if(distance != 0.0){  //If parsed value is different from 0, then the stepper motor moves
      myStepper.step(calculate_steps(distance));
      delay(1000);
    }
    
  }
  delay(20);

  
  //Button Press detection
  if (digitalRead(BUTTON_PIN) == LOW && !button_pressed) {
    buttonPressStartTime = millis();
    button_pressed = true;
  } else if(digitalRead(BUTTON_PIN) == HIGH && button_pressed) {
    unsigned long pressDuration = millis() - buttonPressStartTime;
    button_pressed = false;
    // Short press detected
    if (pressDuration > 50 && pressDuration < SHORT_PRESS_DURATION) {
      SerialBT.println("Short press detected. Re-entering pairing mode...");
      SerialBT.disconnect();
      SerialBT.begin("ELECTRONIC-FOCUSER");
    }
    // Long press detected
    else if (pressDuration >= LONG_PRESS_DURATION) {
      SerialBT.println("Long press detected. Erasing all connections...");
      delay(100);
      SerialBT.disconnect();
      nvs_flash_erase(); // This function erases the NVS partition
      ESP.restart();
    }
  }

}
