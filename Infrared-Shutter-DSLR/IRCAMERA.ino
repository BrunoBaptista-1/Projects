#include <IRremote.h>

// Define LED and button Pins
const int pinIRLED = 10; // pin connected to the Infrared LED
const int buttonPin = 4; // Pin connected to the button that will trigger the shutter
const int ledPin = 8; // Replace with the actual pin you connect the LED to
const int powerLED = 13; //Pin connected to LED that indicates power level

void pulseON(int pulseTime) {
  unsigned long endPulse = micros() + pulseTime;        // create the microseconds to pulse for
  while( micros() < endPulse) {
    digitalWrite(pinIRLED, HIGH);                       // turn IR LED on
    delayMicroseconds(13);                              // half the clock cycle for 38Khz (26.32×10-6s) - coresponding to the 'on' part of signal wave
    digitalWrite(pinIRLED, LOW);                        // turn IR off
    delayMicroseconds(13);                              // delay for the other half of the cycle to generate wave/ oscillation
  }

}

void pulseOFF(unsigned long startDelay) {
  unsigned long endDelay = micros() + startDelay;       // create the microseconds to delay for
  while(micros() < endDelay);
}

void takePicture() {
  for (int i=0; i < 2; i++) {
    pulseON(2000);                                      // pulse for 2000 uS 
    pulseOFF(27850);                                    // turn pulse off for 27850 us
    pulseON(390);                                       // and so on
    pulseOFF(1580);
    pulseON(410);
    pulseOFF(3580);
    pulseON(400);
    pulseOFF(63200);
  }                                                     // loop the signal twice.
}

void setup() {
  pinMode(pinIRLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(powerLED, OUTPUT);

  // Print a message to the serial monitor
  Serial.begin(9600);
  Serial.println("Nikon ML-L3 Remote Control Emulator");
}

void loop() {
  digitalWrite(powerLED, HIGH);
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);

    // Send the Nikon ML-L3 remote code
    takePicture();

    // Wait for a moment to avoid multiple triggers from a single button press
    delay(1000);
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }
}

