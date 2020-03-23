# arduino-analogue-hydraulic-handbrake
This repository houses the Arduino sketch an library required to connect an Arduino-based Hydraulic Handbrake as an analogue brake. 

It includes a copy of the JoystickZero Arduino library that allows various Arduino boards to appear as a Joystick or Gamepad. The following devices should be compatible with the JoystickZero library, but only the Arduino Zero has been tested by me:

Arduino AVR Boards (Uno, Uno Wifi, Nano, Mega, Leonardo and more)
Arduino SAM Boards (Due)
Arduino SAMD Boards (Zero, MKR)
The code in the JoystickZero library is largely based on Matthew Heironimus code from https://github.com/MHeironimus/ArduinoJoystickLibrary, with the primary difference between the two being that the JoystickZero library is built using the native HID library, rather than the custom DynamicHID library Matthew developed and used. This change allows the JoystickZero library to work with many different Arduinos, and yet still benefit from the amazing dynamic HID profiles that Matthew created.

The Joystick Library should work with all the Arduino versions supported by the AVR, SAM and SAMD cores. To see a list of those devices, Open the Arduino IDE, select the Tools menu, then Boards, then Boards Manager, and look at the list of boards under the AVR, SAM and SAMD cores.

# How to Use
## Install and prepare the Arduino IDE
1. You need to install the Arduino IDE if you haven't already. You can do that from https://www.arduino.cc/en/Main/Software.
2. Open the Arduino IDE.
3. Select the Tools menu, then Boards, then Boards Manager...
4. Depending on the Arduino you have, you need to install the Arduino Core for your board into the Arduino IDE:
   - Arduino AVR Boards (Uno, Uno Wifi, Nano, Mega, Leonardo and more)
   - Arduino SAM Boards (Due)
   - Arduino SAMD Boards (Zero, MKR)
   - To install an Arduino Core click on the booard core, then click the Install button. 
   - The board core will be downloaded, and will show up in the list of boards available under Tools > Board.

## Install JoystickZero into the IDE
1. Using your file manager, copy the JoystickZero folder into your IDE libraries directory. On Windows 10 this is typically at `C:\Program Files (x86)\Arduino\libraries`. On Linux machines, this is typically `$HOME/Arduino/libraries`.
2. Start (or restart) the Arduino IDE. 
3. Click on the Sketch menu item, then select Include Library, and check that you can see the JoystickZero library listed under the Contributed Libraries section of the menu.
4. The library is ready to be used!

## Connect your Arduino IDE to the Arduino board

1. Plug in your Arduino to the computer running the Arduino IDE. This will typically be using a USB cable, but may not be.
2. Click on Tools menu, then Port, then select the COM Port that your Arduino has used to connect to your computer. The COM Port needs to be correct, so that the Arduino IDE can talk to the Arduino board. If the Port is set incorrectly, the rest of the instructions cannot be performed.
3. Check the port is set correctly by showing the Board information. This can be done by clicking on Tools menu, then Get Board Info. You should see the Vendor ID, Product ID and Serial number of the Arduino board you're using. If you don't get that, then check the Arduino is plugged in, and that you have selected the correct port.

## Upload the Analogue_Hydraulic_Handbrake.ino sketch
The Analogue_Hydraulic_Handbrake.ino sketch was developed for use in an Analogue Hydraulic Handbrake, and was developed on an Arduino Zero, so it

* turns off all features except the Brake
* Changes the Brake to a 12-bit resolution as the Arduino Zero supported it

I actually tested this on a NANO-ARM (Arduino Zero compatible board in an Arduino Nano form factor!) and it worked perfectly! You can find out more about the Arduino NANO-ARM here: https://wiki.protoneer.co.nz/NANO-ARM. 

Please note that you *will* need to change the `const int numBitsAnalogueResolution = 12;` line to `const int numBitsAnalogueResolution = 10;` if your Arduino board only handles 10-bit resolution on the Analogue inputs. I was lucky that the Arduino Zero I used supported 12-bits resolution.

1. Open the Analogue_Hydraulic_Handbrake.ino from the Analogue_Hydraulic_Handbrake folder.
1. Click checkmark button in the toolbar to compile and verify the code you write.
2. Click the right facing arrow button to compile and upload the sketch
3. You should see a message in the log window at the bottom of the screen telling you the upload has worked and that the Verify was successful. It should also say that the CPU was reset (i.e. the Arduino was rebooted).

## Change the driver (for Windows)
For Windows computers the Arduino will still keep it's original name hich is shows up. This is due to the Windows device driver still recognising that it is an Arduino. But now (thanks to our changes) the Arduino is acting like a Joystick. You will need to change the driver associated with the device in order for Windows to now treat it like a Joystick.

1. Type 'Device Manager' into the search bar, and press enter
2. Device manager will open.
3. Click on the 'Ports (COM & LPT)' section
4. There will be a Arduino Port listed there with a Error symbol over it. That is the Arduino trying to talk Joystick when Windows thinks it's an Arduino! We need to tell Windows it's a Joystick now.
5. Right-click on the Arduino port entry, and select 'Update driver'
6. Click on 'Browse my computer for driver software'
7. Click on 'Let me pick from a list of available drivers on my computer'
8. Select 'USB Input Device' from the list (DO NOT pick the Arduino devices, as we want Windows to talk Joystick, not Arduino!)

The device should now be listed within the 'Devices and Printers' section of the Control Panel. You can check by:

1. Open up Windows Settings
2. Click on the 'Devices and printers' link in the right hand side of the window.

You should see your new Arduino Joystick listed there as it's original name (e.g. min was listed as 'Arduino Zero').

## Test!
Now it's time to test! The new Arduino Joystick should turn up in your list of USB devices. What you see depends on whether its a Windows system, Mac or Linux.

For Windows computers you can test with the Game controller settings.

1. Open up Windows Settings
2. Click on the 'Devices and printers' link in the right hand side of the window.
3. Right click on the Arduino Joystick you want to change, and click on 'Game controller settings'
4. Select the Arduino from the list and click 'Properties'
5. You should now be able to press all your buttons, and you should see Windows understand them, and show you movement on the test window (Note what you see on the test window depends on what features and functions you use from the JoystickZero library).

If your movements are all odd, you may need to calibrate you joystick.

## Calibrate!
You may need to calibrate the device if the range of motion isn't being fully detected, or the pedals aren't working. For Windows computers you can calibrate with the Game controller settings window.

1. Open up Windows Settings
2. Click on the 'Devices and printers' link in the right hand side of the window.
3. Right click on the Arduino Joystick you want to change, and click on 'Game controller settings'
4. Select the Arduino from the list and click 'Properties'
5. Click on the Settings tab
6. Click on the 'Calibrate' button
7. Follow the calibration wizard to calibrate each of the JoystickZero features you've enabled in your Sketch.

And now enjoy your AWESOME Arduino Analogue Hydraulic Handbrake!

# If you want to tweak the sketch
If you want to modify the sketch that I've made feel free! I'd recommend checking the [JoyStickZero README](https://github.com/terrymacdonald/arduino-joystick-zero/blob/master/README.md) as it lists how you can change the JoystickZero library to modify things!

As a quick synopsis, the joystick or gamepad can have the following features:

* Buttons (default: 32)
* Up to 2 Hat Switches
* X, Y, and/or Z Axis (up to 16-bit precision)
* X, Y, and/or Z Axis Rotation (up to 16-bit precision)
* Rudder (up to 16-bit precision)
* Throttle (up to 16-bit precision)
* Accelerator (up to 16-bit precision)
* Brake (up to 16-bit precision)
* Steering (up to 16-bit precision)

JoystickZero is HEAVILY based on Matthew Heironimus's amazing Joystick code from https://github.com/MHeironimus/ArduinoJoystickLibrary, with tweaks to (hopefully) make it more compatible with more devices.
