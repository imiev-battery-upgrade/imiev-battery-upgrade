// Arduino Due - Displays all traffic found on either canbus port
// By Thibaut Viard/Wilfredo Molina/Collin Kidder 2013-2014

// Modified by Paul Dove/ David Cecil to make a CAN bridge between ECU and BMU in 2012 Mitsubishi i-MiEV
// Reads all traffic on CAN0 and forwards it to CAN1 (and in the reverse direction)
// but modifies Soc1, SoC2 and Capacity values first PID 0x374 Bytes [0], [1], and [6].
// Required libraries

#include "variant.h"
#include <due_can.h>
#include <SPI.h>
// #include <SdFat.h> not used uncomment if using SD shield
// const int chipSelect = 4; //not used scared for SD card on Ethernet shield

// Leave defined if you use Due native port, comment if using programming port
// #define Serial SerialUSB

// SdFat sd;//Not used at this time
// SdFile myFile;// scared in for writing to SD card using Ethernet shield

// Global variables
// float volts;       //Average cell voltage
float remAh1 = 0; // Capacity remaining in battery based on coulomb counting
float remAh2 = 0; // Capacity remaining in battery based either on battery voltage or coulomb counting
float capAh = 90; // Battery Capacity
float SoC1;       // State of Charge based on coulomb counting
float SoC2;       // State of Charge based either on battery voltage or coulomb counting
// long presTime;             //Time in milliseconds
// float step;                //Current interval
// long prevTime = millis();  //Time since last current calculation
int flag = 0;  // power up flag
long centiSec; // Timer amps between -1 and 1
int j = 0;     // Counter for valid data
byte vMax = 0;
byte vMin = 0;
byte b41 = 0;
byte b51 = 0;
byte b61 = 0;
byte b71 = 0;
byte b42 = 0;
byte b52 = 0;
byte b62 = 0;
byte b72 = 0;
byte b43 = 0;
byte b53 = 0;
byte b63 = 0;
byte b73 = 0;
byte b44 = 0;
byte b54 = 0;
byte b64 = 0;
byte b74 = 0;

void setup()
{

  Serial.begin(115200); // Initialize Serial port on Arduino 115,200 Baud

  // Initialize CAN0 and CAN1, Set the proper baud rates here

  Can0.begin(CAN_BPS_500K);
  Can1.begin(CAN_BPS_500K);

  // Begin looking for data on Can0 and Can1

  Can0.watchFor(); // class CANRaw instance watchfor()
  Can1.watchFor(); // class CANRaw instance watchfor()
}

// subroutine to store SoC based on voltage of the battery
// This is a series of straight lines connecting SoCs along a low current voltage v SoC curve
// measured by Paul on a NCM cell.
// 2.750
// 3.000 1.021   4.082   -11.2255
// 3.468  16.697  33.497  -99.471
// 3.606 34.933  132.143 -441.573
// 3.721 56.001  183.199 -625.684
// 3.809 63.852  89.213  -275.962
// 3.921 78.535  131.098 -435.500
// 3.997 86.137  100.031 -313.686
// 4.099 100.000 135.913 -457.106
// 4.2   113.727 135.913 -457.106

void storeSoC2()
{
  float volts = (vMin + 210.0) / 100.0; // Compute the lowest cell voltage
  if (volts < 2.75)
  {
    SoC2 = 0.0;
    return;
  }
  else if (volts < 3.0)
  {
    SoC2 = 4.082 * volts - 11.2255;
    return;
  }
  else if (volts < 3.468)
  {
    SoC2 = 33.497 * volts - 99.471;
    return;
  }
  else if (volts < 3.606)
  {
    SoC2 = 132.143 * volts - 441.573;
    return;
  }
  else if (volts < 3.721)
  {
    SoC2 = 183.199 * volts - 625.684;
    return;
  }
  else if (volts < 3.809)
  {
    SoC2 = 89.213 * volts - 275.962;
    return;
  }
  else if (volts < 3.921)
  {
    SoC2 = 131.098 * volts - 435.5;
    return;
  }
  else if (volts < 3.997)
  {
    SoC2 = 100.031 * volts - 313.686;
    return;
  }
  else if (volts < 4.2)
  {
    SoC2 = 135.913 * volts - 457.106;
    return;
  }
  else
  {
    SoC2 = 113.727;
    return;
  }
}

void loop()
{ // Main program loop

  CAN_FRAME incoming; // capture can frames

  if (Can0.available() > 0)
  { // if there is an incoming frame read it
    Can0.read(incoming);

    if (incoming.id == 0x373)
    { // save BMU reported max and min cell voltages and compute the amps to and from the battery and the accumulated amphours in the battery

      if (incoming.data.byte[0] > 65 && incoming.data.byte[0] < 210)
      {
        vMax = incoming.data.byte[0];
      } // update vMax and vMin to good data between 2.75 and 4.2
      if (incoming.data.byte[1] > 65 && incoming.data.byte[1] < 210)
      {
        vMin = incoming.data.byte[1];
      }

      // byte vh = incoming.data.byte[4];
      // byte vl = incoming.data.byte[5];
      // volts = (vh * 256 + vl) / 880.0;  //the average cell voltage from 3.05v to 4.1v. 88 is the number of cells
      // in a car with only 80 cells change 88 to 80

      if (flag == 0)
      { // check to see if this is a new power up
        if (j == 20)
        {                                  // wait 20 0x373 frames until CMU is providing good data
          storeSoC2();                     // get battery SoC based on voltage
          remAh1 = (SoC2 / 100.0) * capAh; // calculate the start remaining Ah in the battery based on voltage
          remAh2 = (SoC2 / 100.0) * capAh; // calculate the start remaining Ah in the battery based on voltage
          flag = 1;
        }
        j = j + 1;
      }

      byte ah = incoming.data.byte[2]; // store current bytes and calculate battery current
      byte al = incoming.data.byte[3];
      float amps = (ah * 256 + al - 32700) / 100.0; // Use 32700 not 32768 32700 is the calibrated value
      float Ah = amps / 360000.0;                   // Amphours to or from the battery in the 0.01 sec between 0x373 frames

      // presTime = millis();  //calculate the interval between 0x373 frames for amp hour calculation
      // step = (presTime - prevTime) / 1000.0 / 3600.0;
      // prevTime = presTime;

      remAh1 = remAh1 + Ah; // update remaining amp hours based on Ah in or out of battery
      remAh2 = remAh2 + Ah; // update remaining amp hours based on Ah in or out of battery
      if (amps > -1.0 && amps < 1.0)
      { // store centiSec elapsed while the amps are > -1 and < 1
        centiSec += 1;
      }
      else
      {
        centiSec = 0;
      }

      incoming.data.byte[0] = vMax;
      incoming.data.byte[1] = vMin;

      Can1.sendFrame(incoming); // send the minimum corrected cell voltage

      // end 0x373
    }
    else if (incoming.id == 0x374)
    {

      incoming.data.byte[6] = 2 * capAh; // modify to 2 x the capacity

      SoC1 = 100.0 * remAh1 / capAh;
      if (centiSec > 60000)
      {                                  // when battery current has been low for long enough (60000 centiSec = 10 min.) for battery voltage to settle
        storeSoC2();                     // gets SoC based on lowest cell voltage
        remAh2 = (SoC2 / 100.0) * capAh; // correct remaining capacity based on voltage
      }
      else
      {                                // current has not been low, long enough to use the SoC based on voltage
        SoC2 = 100.0 * remAh2 / capAh; // correct SoC bsed on the remaining Ah
      }

      // Serial.print("remAh = ");Serial.println(remAh);
      // Serial.print("volts = ");Serial.println(volts);

      incoming.data.byte[0] = 2 * SoC1 + 10; // modify data coming from BMU
      incoming.data.byte[1] = 2 * SoC2 + 10;

      Can1.sendFrame(incoming); // send the corrected SoCs and the correct 100% capacity to the ECU

      // end 0x374
    }
    else
      Can1.sendFrame(incoming); // send any captured frame from BMU other than 0x373, 0x374, 0x5A1 and 6E1-6E4 to ECU .
  }

  if (Can1.available() > 0)
  { // look for messages from ECU and forward to BMU
    Can1.read(incoming);
    Can0.sendFrame(incoming);
  }

} // end main program loop
