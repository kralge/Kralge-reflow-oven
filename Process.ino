void ReflowProcess() {

    switch( ProcStat ) {
    case 0:
      ProcStat = 1;
    case 1:                                                                 //STOPPED
      TempSet = 0;
      break;
    case 2:                                                                 //PREHEATING
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        if( TempSet < (double)ProcPreheatTemp ) TempSet = TempSet + ( ProcPreheatRamp / 10.0 );
        SavedMillis = Millis;
      }
      if( TempAct >= (double)ProcPreheatTemp ) {
        FluxActTempPerSec = ( ProcFluxActTemp - ProcPreheatTemp ) / (double)ProcFluxActTime;
        ProcStat = 3;
      }
      break;
    case 3:                                                                //SOAKING
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        if( TempSet < (double)ProcFluxActTemp ) TempSet = TempSet + FluxActTempPerSec;
        SavedMillis = Millis;
      }
      if( TempAct >= (double)ProcFluxActTemp ) {
        ProcStat = 4;
      }
      break;
    case 4:                                                               //REFLOW HEAT
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        if( TempSet < (double)ProcReflowTemp ) TempSet = TempSet + ( ProcReflowRamp / 10.0 );
        SavedMillis = Millis;
      }
      if( TempAct >= (double)ProcReflowTemp ) {
        ElapsedReflowTime = 0;
        ProcStat = 5;
      }
      break;
    case 5:                                                               //REFLOW
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        ElapsedReflowTime++;
        if( ElapsedReflowTime >= ProcReflowTime ) {
          ProcStat = 6;
        }
        SavedMillis = Millis;
      }
      break;
    case 6:                                                               //REFLOW COOL
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        if( TempSet > (double)ProcFluxActTemp ) TempSet = TempSet - ( ProcReflowRamp / 10.0 );
        SavedMillis = Millis;
      }
      if( TempAct <= (double)ProcFluxActTemp ) {
        ProcStat = 7;
      }
      break;
    case 7:                                                               //COOLING
      Millis = millis();
      if( Millis >= ( SavedMillis + 1000 )) {
        if( TempSet > ( ProcCoolingRamp / 10.0 )) TempSet = TempSet - ( ProcCoolingRamp / 10.0 );
        SavedMillis = Millis;
      }
      if( TempAct <= (double)ColdTemp ) {
        ProcStat = 1;
      }
      break;
  }
}
