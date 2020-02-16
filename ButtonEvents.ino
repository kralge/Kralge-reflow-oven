void ButtonEvents() {

  StartPb.poll();
  SelectPb.poll();
  PlusPb.poll();
  MinusPb.poll();

  if( StartPb.pushed() ) {
    switch ( DispStat ) {
      case 2:                                     //Main screen is active
        switch ( DispPointer ) {
          case 1:                                   //START
            if( 1 == ProcStat ) {
              ProcStat = 2;
              TempSet = TempAct;
              SavedMillis = millis();
            }
            break;
          case 2:                                   //STOP
            ProcStat = 1;
            break;
          case 3:                                   //Settings
            DispStat = 3;
            break;
          case 4:                                   //Graph
            DispStat = 7;
            break;
        }
        break;
      case 4:                                     //Settings screen is active
        switch ( DispPointer ) {
          case 1:                                   //Back to main
            UpdProcEEPROM();
            DispStat = 1;
            break;
          case 2:                                   //Control parameters
            UpdProcEEPROM();
            DispStat = 5;
            break;
        }
        break;
      case 6:                                     //Control parameter screen is active
        switch ( DispPointer ) {
          case 1:                                   //Back to main
            UpdParamEEPROM();
            SetupControllers();
            DispStat = 1;
            break;
        }
        break;
      case 8:                                     //Graph screen is active
        DispStat = 1;
        break;
    }
  }
  
  if( SelectPb.pushed() ) {
    switch ( DispStat ) {
      case 2:                                   //Main screen is active
        if( 3 < DispPointer ) DispPointer = 1; else DispPointer++;
        newDispPointer = 1;
        break;
      case 4:                                   //Settings screen is active
        if( 9 < DispPointer ) DispPointer = 1; else DispPointer++;
        newDispPointer = 1;
        break;
      case 6:                                   //Parameter screen is active
        if( 7 < DispPointer ) DispPointer = 1; else DispPointer++;
        newDispPointer = 1;
        break;
    }
  }

  if( PlusPb.pushed() ) {
    switch ( DispStat ) {
      case 4:                                   //Settings screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 3:                                  //preheat ramp
            if( 255 > ProcPreheatRamp ) ProcPreheatRamp++;
            break;
          case 4:                                  //preheat temp
            if( 255 > ProcPreheatTemp ) ProcPreheatTemp++;
            break;
          case 5:                                  //flux activation time
            if( 255 > ProcFluxActTime ) ProcFluxActTime++;
            break;
          case 6:                                  //flux activation target temp
            if( 255 > ProcFluxActTemp ) ProcFluxActTemp++;
            break;
          case 7:                                  //reflow ramp
            if( 255 > ProcReflowRamp ) ProcReflowRamp++;
            break;
          case 8:                                  //reflow temp
            if( 255 > ProcReflowTemp ) ProcReflowTemp++;
            break;
          case 9:                                  //reflow time
            if( 255 > ProcReflowTime ) ProcReflowTime++;
            break;
          case 10:                                  //cooling ramp
            if( 255 > ProcCoolingRamp ) ProcCoolingRamp++;
            break;
          default:
            newDispData = 0;
        }
        break;
      case 6:                                   //Parameter screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 2:                                  //Triac max power delay
            if( 255 > TriacMaxPowerDelay ) TriacMaxPowerDelay++;
            break;
          case 3:                                   //Triac min power shift
            if( 255 > TriacMinPowerShift ) TriacMinPowerShift++;
            break;
          case 4:                                   //Triac half sine shift
            if( 255 > TriacHalfSineShift ) TriacHalfSineShift++;
            break;
          case 5:                                   //Triac trigger delay
            if( 255 > TriacTriggerDelay ) TriacTriggerDelay++;
            break;
          case 6:                                   //PID controller Kp
            TempControlKp = TempControlKp + 0.01;
            break;
          case 7:                                   //PID controller Ki
            TempControlKi = TempControlKi + 0.001;
            break;
          case 8:                                   //PID controller Kd
            TempControlKd = TempControlKd + 0.01;
            break;
          default:
            newDispData = 0;
        }
        break;
    }
  }

  if( PlusPb.longPress() ) ButPlusLongPressed = 1;
  if( ! PlusPb.on() ) ButPlusLongPressed = 0;

  if( ButPlusLongPressed && ( 25 < ButLongPressCnt )) {
    ButLongPressCnt = 0;
    switch ( DispStat ) {
      case 4:                                   //Settings screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 3:                                  //preheat ramp
            if( 245 > ProcPreheatRamp ) ProcPreheatRamp = ProcPreheatRamp + 10;
            break;
          case 4:                                  //preheat temp
            if( 245 > ProcPreheatTemp ) ProcPreheatTemp = ProcPreheatTemp + 10;
            break;
          case 5:                                  //flux activation time
            if( 245 > ProcFluxActTime ) ProcFluxActTime = ProcFluxActTime + 10;
            break;
          case 6:                                  //flux activation target temp
            if( 245 > ProcFluxActTemp ) ProcFluxActTemp = ProcFluxActTemp + 10;
            break;
          case 7:                                  //reflow ramp
            if( 245 > ProcReflowRamp ) ProcReflowRamp = ProcReflowRamp + 10;
            break;
          case 8:                                  //reflow temp
            if( 245 > ProcReflowTemp ) ProcReflowTemp = ProcReflowTemp + 10;
            break;
          case 9:                                  //reflow time
            if( 245 > ProcReflowTime ) ProcReflowTime = ProcReflowTime + 10;
            break;
          case 10:                                  //cooling ramp
            if( 245 > ProcCoolingRamp ) ProcCoolingRamp = ProcCoolingRamp + 10;
            break;
          default:
            newDispData = 0;
        }
        break;
      case 6:                                   //Parameter screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 2:                                  //Triac max power delay
            if( 245 > TriacMaxPowerDelay ) TriacMaxPowerDelay = TriacMaxPowerDelay + 10;
            break;
          case 3:                                   //Triac min power shift
            if( 245 > TriacMinPowerShift ) TriacMinPowerShift = TriacMinPowerShift + 10;
            break;
          case 4:                                   //Triac half sine shift
            if( 245 > TriacHalfSineShift ) TriacHalfSineShift = TriacHalfSineShift + 10;
            break;
          case 5:                                   //Triac trigger delay
            if( 245 > TriacTriggerDelay ) TriacTriggerDelay = TriacTriggerDelay + 10;
            break;
          case 6:                                   //PID controller Kp
            TempControlKp = TempControlKp + 0.1;
            break;
          case 7:                                   //PID controller Ki
            TempControlKi = TempControlKi + 0.01;
            break;
          case 8:                                   //PID controller Kd
            TempControlKd = TempControlKd + 0.1;
            break;
          default:
            newDispData = 0;
        }
        break;
    }
  }

  if( MinusPb.pushed() ) {
    switch ( DispStat ) {
      case 4:                                   //screen 2 is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 3:                                  //preheat ramp
            if( 0 < ProcPreheatRamp ) ProcPreheatRamp--;
            break;
          case 4:                                  //preheat temp
            if( 0 < ProcPreheatTemp ) ProcPreheatTemp--;
            break;
          case 5:                                  //flux activation time
            if( 0 < ProcFluxActTime ) ProcFluxActTime--;
            break;
          case 6:                                  //flux activation target temp
            if( 0 < ProcFluxActTemp ) ProcFluxActTemp--;
            break;
          case 7:                                  //reflow ramp
            if( 0 < ProcReflowRamp ) ProcReflowRamp--;
            break;
          case 8:                                  //reflow temp
            if( 0 < ProcReflowTemp ) ProcReflowTemp--;
            break;
          case 9:                                  //reflow time
            if( 0 < ProcReflowTime ) ProcReflowTime--;
            break;
          case 10:                                  //cooling ramp
            if( 0 < ProcCoolingRamp ) ProcCoolingRamp--;
            break;
          default:
            newDispData = 0;
        }
        break;
      case 6:                                   //Parameter screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 2:                                  //Triac max power delay
            if( 0 < TriacMaxPowerDelay ) TriacMaxPowerDelay--;
            break;
          case 3:                                   //Triac min power shift
            if( 0 < TriacMinPowerShift ) TriacMinPowerShift--;
            break;
          case 4:                                   //Triac half sine shift
            if( 0 < TriacHalfSineShift ) TriacHalfSineShift--;
            break;
          case 5:                                   //Triac trigger delay
            if( 0 < TriacTriggerDelay ) TriacTriggerDelay--;
            break;
          case 6:                                   //PID controller Kp
            if( 0 < TempControlKp ) TempControlKp = TempControlKp - 0.01;
            break;
          case 7:                                   //PID controller Ki
            if( 0.0 < TempControlKi ) TempControlKi = TempControlKi - 0.001;
            break;
          case 8:                                   //PID controller Kd
            if( 0.0 < TempControlKd ) TempControlKd = TempControlKd - 0.01;
            break;
          default:
            newDispData = 0;
        }
        break;
    }
  }

  if( MinusPb.longPress() ) ButMinusLongPressed = 1;
  if( ! MinusPb.on() ) ButMinusLongPressed = 0;

  if( ButMinusLongPressed && ( 25 < ButLongPressCnt )) {
    ButLongPressCnt = 0;
    switch ( DispStat ) {
      case 4:                                   //screen 2 is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 3:                                  //preheat ramp
            if( 10 < ProcPreheatRamp ) ProcPreheatRamp = ProcPreheatRamp - 10;
            break;
          case 4:                                  //preheat temp
            if( 10 < ProcPreheatTemp ) ProcPreheatTemp = ProcPreheatTemp - 10;
            break;
          case 5:                                  //flux activation time
            if( 10 < ProcFluxActTime ) ProcFluxActTime = ProcFluxActTime - 10;
            break;
          case 6:                                  //flux activation target temp
            if( 10 < ProcFluxActTemp ) ProcFluxActTemp = ProcFluxActTemp - 10;
            break;
          case 7:                                  //reflow ramp
            if( 10 < ProcReflowRamp ) ProcReflowRamp = ProcReflowRamp - 10;
            break;
          case 8:                                  //reflow temp
            if( 10 < ProcReflowTemp ) ProcReflowTemp = ProcReflowTemp - 10;
            break;
          case 9:                                  //reflow time
            if( 10 < ProcReflowTime ) ProcReflowTime = ProcReflowTime - 10;
            break;
          case 10:                                  //cooling ramp
            if( 10 < ProcCoolingRamp ) ProcCoolingRamp = ProcCoolingRamp - 10;
            break;
          default:
            newDispData = 0;
        }
        break;
      case 6:                                   //Parameter screen is active
        newDispData = 1;
        switch ( DispPointer ) {
          case 2:                                  //Triac max power delay
            if( 10 < TriacMaxPowerDelay ) TriacMaxPowerDelay = TriacMaxPowerDelay - 10;
            break;
          case 3:                                   //Triac min power shift
            if( 10 < TriacMinPowerShift ) TriacMinPowerShift = TriacMinPowerShift - 10;
            break;
          case 4:                                   //Triac half sine shift
            if( 10 < TriacHalfSineShift ) TriacHalfSineShift = TriacHalfSineShift - 10;
            break;
          case 5:                                   //Triac trigger delay
            if( 10 < TriacTriggerDelay ) TriacTriggerDelay = TriacTriggerDelay - 10;
            break;
          case 6:                                   //PID controller Kp
            if( 0.1 < TempControlKp ) TempControlKp = TempControlKp - 0.1;
            break;
          case 7:                                   //PID controller Ki
            if( 0.01 < TempControlKi ) TempControlKi = TempControlKi - 0.01;
            break;
          case 8:                                   //PID controller Kd
            if( 0.1 < TempControlKd ) TempControlKd = TempControlKd - 0.1;
            break;
          default:
            newDispData = 0;
        }
        break;
    }
  }

}
