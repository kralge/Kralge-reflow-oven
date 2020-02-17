#include <SPI.h>
#include <AutoPID.h> // https://github.com/r-downing/AutoPID
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <EEPROM.h>
#include <avdweb_Switch.h> // https://github.com/avandalen/avdweb_Switch

#include "ReflowOven.h"

void loop() {

  //Read the temperature sensor when its time
  if( SensorReadTime < SensorReadCnt ) {
    SensorReadCnt = 0;
    TempAct = ReadSensor();
  }

  //Run PID controller
  TempControl.run();
  TriacActShift = TriacMinPowerShift - TriacShiftPIDout;
  TriacTrigger1 = TriacMaxPowerDelay + TriacActShift;
  OutputPercent = ( TriacShiftPIDout / TriacMinPowerShift ) * 100;

  //Take care of the display
  DisplayControl();

  //Take care of button events
  ButtonEvents();

  //Take care of the process
  ReflowProcess();

}
