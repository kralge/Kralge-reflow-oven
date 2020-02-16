void SineRisingISR() {
  if( 1 != OCRBstate ) {
    TCNT1 = 0;
    OCR1A = TriacTrigger1;
    OCR1B = TriacTrigger1 + TriacTriggerDelay;
    OCRAstate = 0;  
    OCRBstate = 0;
  } else {
    OCdiff = OCR1B - TCNT1;
    SineRisingPassed = 1;
  }

  SensorReadCnt++;
  DispValuesCnt++;
  GraphDispCnt++;
  ButLongPressCnt++;
}

ISR( TIMER1_COMPA_vect ) {
  if( 1 == OCRAstate ) {
    OCRAstate = 2;
  } else {
    OCRAstate = 1;
  }
  if( TriacActShift != TriacMinPowerShift ) PORTC = PORTC | 0b100;                      //TRIAC_OUT (PORTC2) output ON
}

ISR( TIMER1_COMPB_vect ) {
  if( TriacActShift != 0 ) PORTC = PORTC & 0b11111011;                   //TRIAC_OUT (PORTC2) output OFF
  if( 1 == OCRBstate ) {
    OCRBstate = 2;
  } else {
    OCRBstate = 1;
  }
  if( 1 == OCRBstate ) {
    OCR1A = TriacHalfSineShift;
    OCR1B = TriacHalfSineShift + TriacTriggerDelay;
    TCNT1 = 0;
  } else {
    if( SineRisingPassed ) {
      OCR1A = TriacTrigger1 - OCdiff;
      OCR1B = ( TriacTrigger1 + TriacTriggerDelay ) - OCdiff;
      TCNT1 = 0;
      OCRAstate = 0;
      OCRBstate = 0;
      SineRisingPassed = 0;
    }
  }
}
