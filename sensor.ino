double ReadSensor() {
  int SensorDataByte;                   //The byte read directly from the sensor
  int SensorDataInt;                    //Two bytes result read from the sensor
    
  PORTD = PORTD & 0b10111111;                           //SENSOR_CS (PORTD6) output OFF (select the sensor on SPI)
  SensorDataByte = SPI.transfer( 0x00 );                //Read in a byte into an int variable
  SensorDataInt = SensorDataByte << 8;                  //Store and shift this data into the upper area of an other int
  SensorDataByte = SPI.transfer( 0x00 );                //Read in the second byte
  SensorDataInt = SensorDataInt | SensorDataByte;       //Store the second byte into the lower area of the int to get the result
  PORTD = PORTD | 0b1000000;                            //SENSOR_CS (PORTD6) output ON (deselect the sensor on SPI)

  return (( SensorDataInt >> 3 ) * 25.0 / 100.0 );          //Calculate the temperature by cutting off the last 3 bits and multiply the result by 0.25°C  
}
