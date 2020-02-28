void DisplayControl() {

  switch ( DispStat ) {
    case 0:
      DispStat = 1;
    case 1:                                                     //main screen preparation
      Screen1Setup();
      DispStat = 2;
    case 2:                                                     //main screen running
      if( newDispPointer ) {
        switch ( DispPointer ) {
          case 1:
            TFTelement( 1, 1 );
            TFTelement( 4, 0 );
            break;
          case 2:
            TFTelement( 2, 1 );
            TFTelement( 1, 0 );
            break;
          case 3:
            TFTelement( 3, 1 );
            TFTelement( 2, 0 );
            break;
          case 4:
            TFTelement( 4, 1 );
            TFTelement( 3, 0 );
            break;
        }
        newDispPointer = 0;
      }
      break;
    case 3:                                                     //settings screen preparation
      Screen2Setup();
      DispStat = 4;
    case 4:                                                     //settings screen running
      if( newDispPointer ) {
        switch ( DispPointer ) {
          case 1:
            TFTelement( 10, 1 );
            TFTelement( 19, 0 );
            break;
          case 2:
            TFTelement( 11, 1 );
            TFTelement( 10, 0 );
            break;
          case 3:
            TFTelement( 12, 1 );
            TFTelement( 11, 0 );
            break;
          case 4:
            TFTelement( 13, 1 );
            TFTelement( 12, 0 );
            break;
          case 5:
            TFTelement( 14, 1 );
            TFTelement( 13, 0 );
            break;
          case 6:
            TFTelement( 15, 1 );
            TFTelement( 14, 0 );
            break;
          case 7:
            TFTelement( 16, 1 );
            TFTelement( 15, 0 );
            break;
          case 8:
            TFTelement( 17, 1 );
            TFTelement( 16, 0 );
            break;
          case 9:
            TFTelement( 18, 1 );
            TFTelement( 17, 0 );
            break;
          case 10:
            TFTelement( 19, 1 );
            TFTelement( 18, 0 );
            break;
        }
        newDispPointer = 0;
      }
      if( newDispData ) {
        if( 3 <= DispPointer ) TFTelement(( 9 + DispPointer ), 2 );
        newDispData = 0;
      }
      break;
    case 5:                                                     //control parameter screen preparation
      Screen3Setup();
      DispStat = 6;
    case 6:                                                     //control parameter screen running
      if( newDispPointer ) {
        switch ( DispPointer ) {
          case 1:
            TFTelement( 30, 1 );
            TFTelement( 37, 0 );
            break;
          case 2:
            TFTelement( 31, 1 );
            TFTelement( 30, 0 );
            break;
          case 3:
            TFTelement( 32, 1 );
            TFTelement( 31, 0 );
            break;
          case 4:
            TFTelement( 33, 1 );
            TFTelement( 32, 0 );
            break;
          case 5:
            TFTelement( 34, 1 );
            TFTelement( 33, 0 );
            break;
          case 6:
            TFTelement( 35, 1 );
            TFTelement( 34, 0 );
            break;
          case 7:
            TFTelement( 36, 1 );
            TFTelement( 35, 0 );
            break;
          case 8:
            TFTelement( 37, 1 );
            TFTelement( 36, 0 );
            break;
        }
        newDispPointer = 0;
      }
      if( newDispData ) {
        if( 2 <= DispPointer ) TFTelement(( 29 + DispPointer ), 2 );
        newDispData = 0;
      }
      break;
    case 7:
      Screen4Setup();
      DispStat = 8;
    case 8:
      break;
  }
  if( DispValuesTime < DispValuesCnt ) {
    DispValuesCnt = 0;
    if( 2 == DispStat ) {
      tft.setTextSize( 3 );
      tft.setTextColor( ILI9341_YELLOW, ILI9341_BLACK );
      if( DigitNoD( LastTempAct ) != DigitNoD( TempAct )) {
        tft.setCursor( 60, 0 ); tft.print( "      " );
      }
      tft.setCursor( 60, 0 ); tft.print( TempAct );
      LastTempAct = TempAct;
      if( DigitNoD( LastTempSet ) != DigitNoD( TempSet )) {
        tft.setCursor( 230, 0 ); tft.print( "   " );
      }
      tft.setCursor( 230, 0 ); tft.print( TempSet, 0 );
      LastTempSet = TempSet;
      if( DigitNoB( LastTriacShift ) != DigitNoB( TriacActShift )) {
        tft.setCursor( 160, 38 ); tft.print( "   " ); 
      }
      tft.setCursor( 160, 38 ); tft.print( TriacActShift );
      LastTriacShift = TriacActShift;
    }
    if( 8 == DispStat ) {
      tft.setTextSize( 2 );
      tft.setTextColor( ILI9341_YELLOW, ILI9341_BLACK );
      if( DigitNoD( LastTempAct ) != DigitNoD( TempAct )) {
        tft.setCursor( 30, 220 ); tft.print( "      " );
      }
      tft.setCursor( 30, 220 ); tft.print( TempAct );
      LastTempAct = TempAct;
      if( DigitNoD( LastTempSet ) != DigitNoD( TempSet )) {
        tft.setCursor( 145, 220 ); tft.print( "   " );
      }
      tft.setCursor( 145, 220 ); tft.print( TempSet, 0 );
      LastTempSet = TempSet;
      if( DigitNoB( LastOutputPercent ) != DigitNoB( OutputPercent )) {
        tft.setCursor( 255, 220 ); tft.print( "   " ); 
      }
      tft.setCursor( 255, 220 ); tft.print( OutputPercent );
      LastOutputPercent = OutputPercent;
    }
  }
  if( GraphDispTime < GraphDispCnt ) {
    GraphDispCnt = 0;
    if( 8 == DispStat ) {
      tft.drawPixel( GraphXpixel, ( GraphBottom - ( TempSet / CperPixel )), ILI9341_BLUE );
      tft.drawPixel( GraphXpixel, ( GraphBottom - ( TempAct / CperPixel )), ILI9341_RED );
      GraphXpixel++;
      if( 319 < GraphXpixel ) GraphXpixel = 0;
    }
  }
  if( ProcStat != OldProcStat ) {
    OldProcStat = ProcStat;
    if( 7 == ProcStat ) {                     //switch to COOLING
      tone( BUZZER, 2400, LongBeepTime );
    } else {
      tone( BUZZER, 2400, ShortBeepTime );
    }
    if(( 2 == DispStat ) || ( 8 == DispStat )) TFTprocStat( DispStat );
    if( 1 < ProcStat ) {                      // switch on circulating fan (D5) when process is active
      PORTD = PORTD | 0b100000;
    } else {
      PORTD = PORTD & 0b11011111;
    }
  }
}

byte DigitNoB( byte Value ) {
  if( 10 > Value ) return 1;
  else if ( 100 > Value ) return 2;
  else return 3;
}

byte DigitNoD( double Value ) {
  if( 10.0 > Value ) return 1;
  else if ( 100.0 > Value ) return 2;
  else return 3;
}

void TFTelement( byte ElementNo, byte Highlight ) {                       //Highlight 0: clear highlight, 1: highlight, 2: clear space and highlight

  tft.setTextSize( 2 );
  if( 1 == Highlight ) tft.setTextColor( ILI9341_NAVY, ILI9341_GREEN );
    else tft.setTextColor( ILI9341_WHITE, ILI9341_BLACK );

  switch ( ElementNo ) {
    case 1:
      tft.setCursor( 0, 220 ); tft.print( "START" );
      break;
    case 2:
      tft.setCursor( 80, 220 ); tft.print( "STOP" );
      break;
    case 3:
      tft.setCursor( 140, 220 ); tft.print( "Settings" );
      break;
    case 4:
      tft.setCursor( 255, 220 ); tft.print( "Graph" );
      break;
    case 10:
    case 30:
      tft.setCursor( 0, 220 ); tft.print( "Back to Main" );
      break;
    case 11:
      tft.setCursor( 180, 220 ); tft.print( "Cntrl param" );
      break;
    case 12:
      tft.setCursor( 240, 20 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 20 );
      }
      tft.print(( (double)ProcPreheatRamp / 10 ), 1 );
      break;
    case 13:
      tft.setCursor( 240, 40 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 40 );
      }
      tft.print( ProcPreheatTemp );
      break;
    case 14:
      tft.setCursor( 240, 60 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 60 );
      }
      tft.print( ProcFluxActTime );
      break;
    case 15:
      tft.setCursor( 240, 80 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 80 );
      }
      tft.print( ProcFluxActTemp );
      break;
    case 16:
      tft.setCursor( 240, 100 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 100 );
      }
      tft.print(( (double)ProcReflowRamp / 10 ), 1 );
      break;
    case 17:
      tft.setCursor( 240, 120 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 120 );
      }
      tft.print( ProcReflowTemp );
      break;
    case 18:
      tft.setCursor( 240, 140 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 140 );
      }
      tft.print( ProcReflowTime );
      break;
    case 19:
      tft.setCursor( 240, 160 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 160 );
      }
      tft.print(( (double)ProcCoolingRamp / 10 ), 1 );
      break;
    case 31:
      tft.setCursor( 240, 20 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 20 );
      }
      tft.print( TriacMaxPowerDelay );
      break;
    case 32:
      tft.setCursor( 240, 40 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 40 );
      }
      tft.print( TriacMinPowerShift );
      break;
    case 33:
      tft.setCursor( 240, 60 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 60 );
      }
      tft.print( TriacHalfSineShift );
      break;
    case 34:
      tft.setCursor( 240, 80 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 80 );
      }
      tft.print( TriacTriggerDelay );
      break;
    case 35:
      tft.setCursor( 240, 100 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 100 );
      }
      tft.print( TempControlKp, 2 );
      break;
    case 36:
      tft.setCursor( 240, 120 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 120 );
      }
      tft.print( TempControlKi, 3 );
      break;
    case 37:
      tft.setCursor( 240, 140 );
      if( 2 == Highlight ) {
        TFTclear();
        tft.setCursor( 240, 140 );
      }
      tft.print( TempControlKd, 2 );
      break;
  }
}

void TFTclear() {
  tft.print( "      " );
  tft.setTextColor( ILI9341_NAVY, ILI9341_GREEN );  
}

void TFTprocStat( byte DispStat ) {
  if( 2 == DispStat ) {  
    tft.setTextSize( 3 );
    tft.setCursor( 110, 70 );
  } else {
    tft.setTextSize( 2 );
    tft.setCursor( 0, 0 );    
  }
  tft.setTextColor( ILI9341_YELLOW, ILI9341_BLACK );
  switch( ProcStat ) {
    case 1:
      tft.print( "STOPPED    " );
      break;
    case 2:
      tft.print( "PREHEATING " );
      break;
    case 3:
      tft.print( "SOAKING    " );
      break;
    case 4:
      tft.print( "REFLOW HEAT" );
      break;
    case 5:
      tft.print( "REFLOW     " );
      break;
    case 6:
      tft.print( "REFLOW COOL" );
      break;
    case 7:
      tft.print( "COOLING    " );
      break;
  }  
}

void Screen1Setup () {
  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_WHITE );

  tft.setTextSize( 3 ); tft.setCursor( 0, 0 ); tft.print( (char)247 ); tft.print( "C:" );
  tft.setTextSize( 2 ); tft.setCursor( 180, 0 ); tft.print( "Set:" );
  tft.setTextSize( 2 ); tft.setCursor( 0, 40 ); tft.print( "Phase shift:" );
  tft.setCursor( 0, 75 ); tft.print( "Process:" ); TFTprocStat( 2 );

  tft.setTextSize( 1 ); tft.setCursor( 0, 110 );
  tft.print( "Preheat ramp rate: " ); tft.println(( (double)ProcPreheatRamp / 10 ), 1 );
  tft.print( "Preheat target temp: " ); tft.println( ProcPreheatTemp );
  tft.print( "Flux activation time: " ); tft.println( ProcFluxActTime );
  tft.print( "Flux activation target temp: " ); tft.println( ProcFluxActTemp );
  tft.print( "Reflow ramp rate: " ); tft.println(( (double)ProcReflowRamp / 10 ), 1 );
  tft.print( "Reflow target temp: " ); tft.println( ProcReflowTemp );
  tft.print( "Reflow time: " ); tft.println( ProcReflowTime );
  tft.print( "Cooling ramp rate: " ); tft.println(( (double)ProcCoolingRamp / 10 ), 1 );

  TFTelement( 1, 1 );
  TFTelement( 2, 0 );
  TFTelement( 3, 0 );
  TFTelement( 4, 0 );
  DispPointer = 1;
}

void Screen2Setup () {
  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_WHITE );

  tft.setTextSize( 2 );
  tft.setCursor( 0, 20 ); tft.print( "Preheat ramp rate:" );
  tft.setCursor( 0, 40 ); tft.print( "Preheat targ temp:" );
  tft.setCursor( 0, 60 ); tft.print( "Flux act time:" );
  tft.setCursor( 0, 80 ); tft.print( "Flux act targ temp:" );
  tft.setCursor( 0, 100 ); tft.print( "Reflow ramp rate:" );
  tft.setCursor( 0, 120 ); tft.print( "Reflow target temp:" );
  tft.setCursor( 0, 140 ); tft.print( "Reflow time:" );
  tft.setCursor( 0, 160 ); tft.print( "Cooling ramp rate:" );

  TFTelement( 12, 0 );
  TFTelement( 13, 0 );
  TFTelement( 14, 0 );
  TFTelement( 15, 0 );
  TFTelement( 16, 0 );
  TFTelement( 17, 0 );
  TFTelement( 18, 0 );
  TFTelement( 19, 0 );

  TFTelement( 11, 0 );
  TFTelement( 10, 1 );
  DispPointer = 1;
}

void Screen3Setup () {
  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_WHITE );

  tft.setTextSize( 2 );
  tft.setCursor( 0, 20 ); tft.print( "Triac max pwr delay:" );
  tft.setCursor( 0, 40 ); tft.print( "Triac min pwr shift:" );
  tft.setCursor( 0, 60 ); tft.print( "Triac half sin shft:" );
  tft.setCursor( 0, 80 ); tft.print( "Triac trigger delay:" );
  tft.setCursor( 0, 100 ); tft.print( "PID control Kp:" );
  tft.setCursor( 0, 120 ); tft.print( "PID control Ki:" );
  tft.setCursor( 0, 140 ); tft.print( "PID control Kd:" );

  TFTelement( 31, 0 );
  TFTelement( 32, 0 );
  TFTelement( 33, 0 );
  TFTelement( 34, 0 );
  TFTelement( 35, 0 );
  TFTelement( 36, 0 );
  TFTelement( 37, 0 );

  TFTelement( 30, 1 );
  DispPointer = 1;
}

void Screen4Setup () {
  int OriLineY = 0;

  tft.fillScreen( ILI9341_BLACK );
  CperPixel = ( ProcReflowTemp + 20.0 ) / GraphOriTop;
  while( OriLineY < GraphOriTop ) {
    tft.drawLine( 0, ( GraphBottom - OriLineY ), 319, ( GraphBottom - OriLineY ), ILI9341_DARKGREY );
    OriLineY = OriLineY + ( GraphOriLineC / CperPixel );
  }
  GraphXpixel = 0;

  tft.setTextSize( 2 ); tft.setTextColor( ILI9341_WHITE );
  tft.setCursor( 0, 220 ); tft.print( (char)247 ); tft.print( "C" );
  tft.setCursor( 120, 220 ); tft.print( "S:" );
  tft.setCursor( 300, 220 ); tft.print( "%" );
  TFTprocStat( 8 );
}
