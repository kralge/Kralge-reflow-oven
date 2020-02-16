void ReadEEPROM () {
  if( 0xFF == EEPROM[ EEpos_FirstSwitchOn ] ) {
    TriacMaxPowerDelay = DEF_TriacMaxPowerDelay;
    TriacMinPowerShift = DEF_TriacMinPowerShift;
    TriacHalfSineShift = DEF_TriacHalfSineShift;
    TriacTriggerDelay = DEF_TriacTriggerDelay;
    TempControlKp = DEF_TempControlKp;
    TempControlKi = DEF_TempControlKi;
    TempControlKd = DEF_TempControlKd;
    ProcPreheatRamp = DEF_ProcPreheatRamp;
    ProcPreheatTemp = DEF_ProcPreheatTemp;
    ProcFluxActTime = DEF_ProcFluxActTime;
    ProcFluxActTemp = DEF_ProcFluxActTemp;
    ProcReflowRamp = DEF_ProcReflowRamp;
    ProcReflowTemp = DEF_ProcReflowTemp;
    ProcReflowTime = DEF_ProcReflowTime;
    ProcCoolingRamp = DEF_ProcCoolingRamp;
    UpdParamEEPROM();
    UpdProcEEPROM();
    EEPROM[ EEpos_FirstSwitchOn ] = 0xFE;
  } else {
    TriacMaxPowerDelay = EEPROM[ EEpos_TriacMaxPowerDelay ];
    TriacMinPowerShift = EEPROM[ EEpos_TriacMinPowerShift ];
    TriacHalfSineShift = EEPROM[ EEpos_TriacHalfSineShift ];
    TriacTriggerDelay = EEPROM[ EEpos_TriacTriggerDelay ];
    EEPROM.get( EEpos_TempControlKp, TempControlKp );
    EEPROM.get( EEpos_TempControlKi, TempControlKi );
    EEPROM.get( EEpos_TempControlKd, TempControlKd );
    ProcPreheatRamp = EEPROM[ EEpos_ProcPreheatRamp ];
    ProcPreheatTemp = EEPROM[ EEpos_ProcPreheatTemp ];
    ProcFluxActTime = EEPROM[ EEpos_ProcFluxActTime ];
    ProcFluxActTemp = EEPROM[ EEpos_ProcFluxActTemp ];
    ProcReflowRamp = EEPROM[ EEpos_ProcReflowRamp ];
    ProcReflowTemp = EEPROM[ EEpos_ProcReflowTemp ];
    ProcReflowTime = EEPROM[ EEpos_ProcReflowTime ];
    ProcCoolingRamp = EEPROM[ EEpos_ProcCoolingRamp ];
  }
}

void UpdParamEEPROM() {
  EEPROM[ EEpos_TriacMaxPowerDelay ] = TriacMaxPowerDelay;
  EEPROM[ EEpos_TriacMinPowerShift ] = TriacMinPowerShift;
  EEPROM[ EEpos_TriacHalfSineShift ] = TriacHalfSineShift;
  EEPROM[ EEpos_TriacTriggerDelay ] = TriacTriggerDelay;
  EEPROM.put( EEpos_TempControlKp, TempControlKp );
  EEPROM.put( EEpos_TempControlKi, TempControlKi );
  EEPROM.put( EEpos_TempControlKd, TempControlKd );  
}

void UpdProcEEPROM() {
  EEPROM[ EEpos_ProcPreheatRamp ] = ProcPreheatRamp;
  EEPROM[ EEpos_ProcPreheatTemp ] = ProcPreheatTemp;
  EEPROM[ EEpos_ProcFluxActTime ] = ProcFluxActTime;
  EEPROM[ EEpos_ProcFluxActTemp ] = ProcFluxActTemp;
  EEPROM[ EEpos_ProcReflowRamp ] = ProcReflowRamp;
  EEPROM[ EEpos_ProcReflowTemp ] = ProcReflowTemp;
  EEPROM[ EEpos_ProcReflowTime ] = ProcReflowTime;
  EEPROM[ EEpos_ProcCoolingRamp ] = ProcCoolingRamp;
}
