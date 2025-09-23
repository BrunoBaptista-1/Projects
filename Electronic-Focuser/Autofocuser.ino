#include <Stepper.h>
#include "BluetoothSerial.h"
#include "nvs_flash.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif


const int stepsPerRevolution = 2048;  // number of steps per revolution

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

void loop() {

  if (SerialBT.available()) {

    int value = SerialBT.read();

    if(value == '0' ){ //for value 0, the motor does a step backwards
      myStepper.step(-50);
      delay(1000);
    }
    else if(value == '1' ){ //for value 1, the motor does a medium step backwards
      myStepper.step(-250);
      delay(1000);
    }
    else if(value == '2' ){ //for value 2, the motor does a full revolution backwards
      myStepper.step(-stepsPerRevolution);
      delay(1000);
    }


  
    else if(value == '3' ){ //for value 3, the motor does a step forward
      myStepper.step(50);
      delay(1000);
    }
    else if(value == '4' ){ //for value 4, the motor does a medium step forward
      myStepper.step(250);
      delay(1000);
    }
    else if (value == '5'){ //for value 5, the motor does a full revolution forward
      myStepper.step(stepsPerRevolution);
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
