void setup() {

  //reading out the parameters from EEPROM
  ReadEEPROM();

  //setup controllers based on the read data
  SetupControllers();

  //setup timer1
  cli();                    //disable global inetrrupts
  TCCR1A = 0b0;             //select normal mode
  TCCR1B = 0b101;           //prescaler to 1024 (64us for each step)
  OCR1A = TriacTrigger1;
  OCR1B = TriacTrigger1 + TriacTriggerDelay;
  TIMSK1 = 0b110;            //enable A and B match timer interrupts
  sei();                     //enable global interrupts

  //setup and initialize I/O and interrupts
  pinMode( TRIAC_OUT, OUTPUT );
  pinMode( FAN_OUT, OUTPUT );
  pinMode( SENSOR_CS, OUTPUT );
  PORTD = PORTD | 0b1000000;            //SENSOR_CS (PORTD6) output ON

  attachInterrupt( digitalPinToInterrupt( SINE_IN ), SineRisingISR, FALLING );

  SPI.begin();

  tft.begin();
  tft.setRotation( 3 );

}

void SetupControllers() {
  TempControl.setGains( TempControlKp, TempControlKi, TempControlKd );
  TempControl.setOutputRange( 0, TriacMinPowerShift );

  TriacTrigger1 = TriacMaxPowerDelay + TriacMinPowerShift;
}
