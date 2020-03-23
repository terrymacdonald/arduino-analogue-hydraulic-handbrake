// ===================================
// Analogue Hydraulic Handbrake for Arduino Zero
// by Terry MacDonald
// ===================================
// Connect the +5V cable from the pressure sensor to the Arduino Zero VIN pin
// Connect the ground cable from the pressure sensor to the Arduino Zero GND pin
// Connect the signal cable from the pressure sensor to the Arduino Zero A0 pin
// NOTE - If your Arduino Zero has 3.3V Analogue inputs, then you will need a
//        resistive divider to the pressure sensor signal cable to step
//        the 5V output to 3.3V that the Arduino input needs. Without this
//        you could fry your Arduino! See the Step-down level section here:
//        https://hackaday.com/2016/12/05/taking-it-to-another-level-making-3-3v-and-5v-logic-communicate-with-level-shifters/

// Uses a modified version of Matthew Heironimous' ArduinoJoystickLibrary
// changed to work with many more Arduino devices including the Arduino Zero 
// (see the original at https://github.com/MHeironimus/ArduinoJoystickLibrary)
#include <JoystickZero.h>

// This sets the Analogue pin to read from the Arduino
const int pinConnectedToSensor = A0;

// This sets the resolution of the Arduino, which is the number of digital
// values that the analogue signal will be converted into.
// A 10-bit Analogue resolution gives you 1024 different levels
// A 12-bit Analogue resolution gives you 4096 different levels
const int numBitsAnalogueResolution = 12;
const int maxAnalogueValue = pow(2,numBitsAnalogueResolution)-1;

// This controls the debug mode so you get informative messages in the Serial Monitor
// Change the debug value below to true to get debug messages
// Change the debug value below to false to stop getting debug messages
const bool debug = false;

// This counts the loops so we show debug messages on the Serial Monitor every 10 loops
// just to make sure we don't scroll too many times!
int loopCounter = 0;

// Set the features of the Joystick that we want
// This will customise what USB data is sent to the computer.
// With a handbrake, we ONLY want the Brake Axis....
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0, 0, false, false, false, false, false, false, false, false, false, true, false);

void setup() {
  
  if (debug) {
    // Wait for the SerialUSB library to be available
    while (!SerialUSB);
    // Start the Serial USB so we report what we're doing
    SerialUSB.begin(115200);
    SerialUSB.println("Joystick starting");
    
    // Set the chosen Arduino pin to Input mode (we don't need pullup resistors)
    SerialUSB.print("Setting signal input pin to ");
    SerialUSB.println(pinConnectedToSensor);
  }
  pinMode(pinConnectedToSensor, INPUT); 
  
  // Change the Analogue Read Resolution to the chosen analogue resolution
  if (debug) {
    SerialUSB.print("Setting analogue resolution to ");
    SerialUSB.print(numBitsAnalogueResolution);
    SerialUSB.println("-bits");
  }
  analogReadResolution(numBitsAnalogueResolution);

  // Start the Joystick emulation
  Joystick.begin(true);

  // Set the Joystick library Brake Max range using the chosen analogue resolution
  if (debug) {
    SerialUSB.print("Setting brake range to 0 <-> ");
    SerialUSB.println(maxAnalogueValue);
  }
  Joystick.setBrakeRange(0,maxAnalogueValue);
}

void loop() {
  // Read the value from the sensor
  int readValue = analogRead(pinConnectedToSensor);

  // Describe what we're doing into the Serial Monitor
  if (debug) {
    if (loopCounter % 2 == 0) {
      SerialUSB.print("PIN ");
      SerialUSB.print(pinConnectedToSensor);
      SerialUSB.print(" set to ");
      SerialUSB.println(readValue);
    }
    loopCounter++;
  }

  // Update the computer with the current Brake value.
  Joystick.setBrake(readValue);

  // Delay for 50 microseconds to try and smooth out the signals
  delay(50);
}
