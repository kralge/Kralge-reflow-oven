// I/O positions
#define TFT_DC    A3
#define TFT_CS    A1
#define TFT_RST   A0
#define TRIAC_OUT A2
#define SINE_IN   2
#define BUZZER    3
#define SENSOR_CS 6
#define PB_START  7
#define PB_SELECT 8
#define PB_PLUS   9
#define PB_MINUS  10

//EEPROM data positions
#define EEpos_TriacMaxPowerDelay  0
#define EEpos_TriacMinPowerShift  1
#define EEpos_TriacHalfSineShift  2
#define EEpos_TriacTriggerDelay   3
#define EEpos_TempControlKp       4
#define EEpos_TempControlKi       8
#define EEpos_TempControlKd       12
#define EEpos_ProcPreheatRamp     16
#define EEpos_ProcPreheatTemp     17
#define EEpos_ProcFluxActTime     18
#define EEpos_ProcFluxActTemp     19
#define EEpos_ProcReflowRamp      20
#define EEpos_ProcReflowTemp      21
#define EEpos_ProcReflowTime      22
#define EEpos_ProcCoolingRamp     23
#define EEpos_FirstSwitchOn       24

//Default values of the settings, these are loaded after the first switch-on
//The ramp rates are in 0.1 °C/s, so 6 = 0.6 °C/s
#define DEF_TriacMaxPowerDelay  142
#define DEF_TriacMinPowerShift  150
#define DEF_TriacHalfSineShift  155
#define DEF_TriacTriggerDelay   2
#define DEF_TempControlKp       30.0
#define DEF_TempControlKi       0.001
#define DEF_TempControlKd       10.0
#define DEF_ProcPreheatRamp     6
#define DEF_ProcPreheatTemp     150
#define DEF_ProcFluxActTime     100
#define DEF_ProcFluxActTemp     170
#define DEF_ProcReflowRamp      7
#define DEF_ProcReflowTemp      220
#define DEF_ProcReflowTime      30
#define DEF_ProcCoolingRamp     30

//Misc values
#define LongBeepTime  1000            //Long beep time in ms (used when process turns to cooling state)
#define ShortBeepTime 200             //Short beep time in ms (used at every process status change)

#define ColdTemp  40                  //After falling of the temperature under this value we quit the process

#define GraphBottom     210              //The 0°C position of the graph diagram on the screen
#define GraphOriLineC   50               //The density of the orientation lines of the graph. 50 means a line at every 50°C.
#define GraphOriTop     180              //The highest point on the diagram where we put orientation line      

// Parameters for controlling the heater load
byte TriacMaxPowerDelay;              //The specified delay for triggering the triac at beginning of the second half sine wave (*64us) after receiving the sine rising signal
volatile byte TriacMinPowerShift;     //The 180° shift delay to trigger at the end of the second half sine wave (*64us) added to TriacMaxPowerDelay
byte TriacHalfSineShift;              //The 180° shift to trigger at the overnext sine wave (*64us). Should be around 10ms for 50Hz.
byte TriacTriggerDelay;               //The triggering time of the triac (*64us). Value 2 is working fine.
volatile byte TriacActShift;          //The actual shift value by the PID controller
byte LastTriacShift;                  //Used to determine if we need to clear the area on the display when refreshing value
double TriacShiftPIDout;              //The output of the PID controllers, to be converted back to byte.
volatile int TriacTrigger1;           //This is the calculated time step for the first trigger for the first sine wave.
byte OCRAstate;                       //OCRA match interrupt status (0: no interrupt so far, 1: first interrupt executed, 2: second interrupt executed)
byte OCRBstate;                       //OCRB match interrupt status (0: no interrupt so far, 1: first interrupt executed, 2: second interrupt executed)
byte OCdiff;                          //Saved time step difference between the last next OCRB value and the time of sine rising
byte SineRisingPassed;                //Flag to indicate that sine rising has happened
byte OutputPercent;                   //The output power in % (not exactly the power)
byte LastOutputPercent;               //Used to determine if we need to clear display because of change in digit length

// Parameters for PID controls
double TempControlKp;                 //The Kp (proportional) parameter for the PID controller when controlling the temperature value.
double TempControlKi;                 //The Ki (integral) parameter for the PID controller when controlling the temperature value.
double TempControlKd;                 //The Kd (differential) parameter for the PID controller when controlling the temperature value.
double TempAct;                       //The actual temperature read directly from the sensor.
double LastTempAct;                   //Used to determine if we need to clear display because of change in digit length
double TempSet;                       //The current target temperature to be set for the PID controller.
double LastTempSet;                   //Used to determine if we need to clear display because of change in digit length

// Parameters for reflow process
byte ProcPreheatRamp;                 //The preheat ramp rate in tenth of celsius.
byte ProcPreheatTemp;                 //The preheat target temperature.
byte ProcFluxActTime;                 //The flux activation (or soaking) time in seconds.
byte ProcFluxActTemp;                 //The desired target temperature after flux activation time has passed.
byte ProcReflowRamp;                  //Reflow ramp rate in tenth of celsius.
byte ProcReflowTemp;                  //Reflow target temperature.
byte ProcReflowTime;                  //Reflow time in seconds.
byte ProcCoolingRamp;                 //The cooling ramp rate in tenth of celsius.

//Sensor related variables
volatile byte SensorReadCnt;          //The counter counts every 20ms and this is used to trigger sensor reading
const byte SensorReadTime = 25;       //This value determines the number of counts after which the sensor is read. 50 = 1s

//Display related variables
byte DispStat;                        //Display status to check when to build screens 0: startup, 1: prepare screen 1, 2: run screen 1, 3: prepare screen 2, 4: run screen 2 etc.
byte DispPointer;                     //A pointer on screen to show the selectable element
byte newDispPointer;                  //Flag to indicate a new display pointer
byte newDispData;                     //Flag to indicate a new display data
volatile byte DispValuesCnt;          //The counter counts every 20ms and this is used to trigger value refresh on display
const byte DispValuesTime = 40;       //This value determines the number of counts after which we trigger a value refresh on the display. 50 = 1s
double CperPixel;                     //The calculated Y direction scale for graph screen
int GraphXpixel;                      //The stored and cyclically incremented X axis value for drawing the graph
volatile byte GraphDispCnt;           //The counter counts every 20ms and this is used to add new pixels to the diagram
const byte GraphDispTime = 75;        //This value determines the number of counts after which we add new pixels to the diagram. 50 = 1s
volatile byte ButLongPressCnt;        //This will be incremented at every sine rising to give a pulse at long press of buttons
byte ButPlusLongPressed;              //Flag to indicate continuous press of the long pressed plus button
byte ButMinusLongPressed;             //Flag to indicate continuous press of the long pressed minus button

//Process related variables
byte ProcStat;                        //Actual process state
byte OldProcStat;                     //Saved process state to detect state change
unsigned long SavedMillis;            //To make a Setpoint change at every second, the result of millis() is saved here
unsigned long Millis;                 //The value of millis()
double FluxActTempPerSec;             //The calculated increase of temperature during flux activation
byte ElapsedReflowTime;               //Elapsed reflow time in seconds

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

AutoPID TempControl( &TempAct, &TempSet, &TriacShiftPIDout, 0, TriacMinPowerShift, TempControlKp, TempControlKi, TempControlKd );

Switch StartPb = Switch( PB_START );
Switch SelectPb = Switch( PB_SELECT );
Switch PlusPb = Switch( PB_PLUS );
Switch MinusPb = Switch( PB_MINUS );
