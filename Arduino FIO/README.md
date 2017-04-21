#Getting Started:
Device: https://www.sparkfun.com/products/11520


#Summary
The FIO is an unsupported device by Arduino. That being said, sparkfun created a new version of the FIO which they sell as Arduino FIOv3.

This device has:
  - A battery port and management circuit.
  - A xBee port for quick Zigbee Integration.
  - Built in circuit for programming the Arduino, instead of the old FTDI
  - Lots of I/O ports.

However, the device does not have continued support. The following is required to get a working environment for developing for the FIOv3

#Instructions

## 1 Setup the board URL in Arduino
    a) Open arduino and go to preferences
    b) copy and paste the following into " Additional Boards Manager URLs"

    https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json

    c) Close preferences and open boards manager from Tools->Boards->Boards Manager.
    d) Search for sparkfun and install the library that pops up first.
## 2 Fix the Library for the Board
    a) Find the directory for your hardware. On mac this is in

        ~/Library/Arduino15/packages

    b) Download the boards.txt file and variants folder located in the libraries folder on this repo
    c) Copy them into the sparkfun folder replacing the exisiting documents. On Mac this is at

        ~/Library/Arduino15/packages/hardware/avr/1.1.5/

## 3 Setup IDE
    a) Open the IDE and select "Sparkfun Fio v3" as your device.
    b) Follow instructions in the appropriate folder to move folder with Zigbee, RFID, etc.

## 4 Sources
  - https://github.com/helgames/SF32u4_boards
  - https://www.sparkfun.com/products/11520
