
#include "grlib.h"
#include "driverlib.h"
#include <stdint.h>
#include <stdio.h>


// Global Variables
Graphics_Context g_sContext;
uint16_t JoyStickX, JoyStickY;
Timer_B_outputPWMParam MyTimerB;
Timer_A_initUpModeParam MyTimerA;

//Function Headers
//void LCD_init(void);
void ADC_init(void);
void joyStick_init();
void configTimerA(uint16_t,uint16_t);
void myTimerADelay(uint16_t,uint16_t);
void config_PWM(uint16_t,uint16_t);
uint16_t executePattern(uint16_t);

//enumerate motor mode
typedef enum {off, cw, ccw} motorMode;
typedef enum {fast,slow} motorSpeed;
typedef enum {ON,OFF,toggle} LEDmode;


///Define Function Prototypes
void configIO();
void stepMotor();
void justClockwise();
void myMotorController();


uint16_t timerPeriod;
uint8_t phase = 0;
volatile uint8_t PBS1 = 0, PBS2 = 0, JSButton = 0;

void config_mkII(void);
void configIO();
void stepMotor();

const uint16_t YHIGH = 0x8ff, YLOW = 0x3ff;
const uint16_t XHIGH = 0x8fe, XLOW = 0x3fe;

#pragma vector = PORT4_VECTOR
__interrupt void myPBISR(void){
    ADC12_B_startConversion(ADC12_B_BASE,ADC12_B_START_AT_ADC12MEM0,ADC12_B_SEQOFCHANNELS);
    while(ADC12_B_getInterruptStatus(ADC12_B_BASE,0,ADC12_B_IFG1) != ADC12_B_IFG1);   // Wait for conversion
    // Get JoyStickX results IFG is cleared
    JoyStickX = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_0);
    // Get JoyStickY results IFG is cleared
    JoyStickY = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_1);
    // Clear IFG1 explicitly
    ADC12_B_clearInterrupt(ADC12_B_BASE,0,ADC12_B_IFG1);

    myMotorController();

}

void main (void){


    //Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Initialize Joystick
    joyStick_init();

    // Configure mkII
    //config_mkII();
    configIO();

    // Activate Configuration
    PMM_unlockLPM5();

    // Initialize ADC
    ADC_init();

    // Start Conversion
    ADC12_B_startConversion(ADC12_B_BASE,ADC12_B_START_AT_ADC12MEM0,ADC12_B_REPEATED_SEQOFCHANNELS);

    //Configure PBS1 and PBS2 for Interrupts
      GPIO_selectInterruptEdge(GPIO_PORT_P4,GPIO_PIN3, GPIO_HIGH_TO_LOW_TRANSITION);
      GPIO_selectInterruptEdge(GPIO_PORT_P4,GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
      GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN3);//PBS1
      GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);//PBS2
      GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN3);
      GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);

      //enable global interrupts
        __enable_interrupt();

        __low_power_mode_0();

        __no_operation();
}



/* myMotorController function
 * Inputs: none
 * Outputs: none
 * Date: 11/11/2020
 * Based on the two pushbutton inputs the motors functionality is determined
 * and the count direction is changed accordingly
 */

void myMotorController(){
    int start,ii,iii;
    uint16_t stage;
        stage=0;
    motorMode mode;
    motorSpeed speed;
    uint16_t steps=0;
    LEDmode LED1,LED2;

    PBS1 = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN3);
    PBS2 = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN2);
    JSButton = GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN2);



    //regular operation based on Joystick
    if(PBS1 != GPIO_INPUT_PIN_LOW && PBS2 != GPIO_INPUT_PIN_LOW){

              //LED1 OFF and LED2 flashing at 1Hz
              if((JoyStickY <= YHIGH) && (JoyStickY >= YLOW) && (JoyStickX <= XHIGH) && (JoyStickX >= XLOW)){
                 phase=0;
                 mode=off;
                 LED1=OFF;
                 LED2=toggle;
              }else if((JoyStickY >= YHIGH) ){
                  mode=cw;
                  speed=fast;
                  LED1=OFF;
                  LED2=ON;
              }else if(JoyStickY <= YLOW){
                  mode=cw;
                  speed=slow;
                  LED1=OFF;
                  LED2=ON;
              }else if(JoyStickX >= XHIGH){
                  mode=ccw;
                  speed=fast;
                  LED1=ON;
                  LED2=OFF;
              }else if(JoyStickX <= XLOW){
                  mode=ccw;
                  speed=slow;
                  LED1=ON;
                  LED2=OFF;
              }
    }else if(PBS1 != GPIO_INPUT_PIN_LOW && PBS2 == GPIO_INPUT_PIN_LOW){         ////START OF DEBUG MODE
       mode=cw;
       speed=fast;
    }else if(PBS1 != GPIO_INPUT_PIN_LOW && PBS2 == GPIO_INPUT_PIN_LOW){
        mode=ccw;
        speed=slow;
    }
    //pattern mode
    else if(PBS1 == GPIO_INPUT_PIN_LOW && PBS2 == GPIO_INPUT_PIN_LOW){          ////START OF PATTERN MODE
        LED1=ON;
        LED2=ON;
        while(stage!=10){
           for(ii=0;ii<=steps;ii++){
               stepMotor(phase);
               if(phase==0) phase = 7;
               else phase--;
                       myTimerADelay(215,TIMER_A_CLOCKSOURCE_DIVIDER_20);
                   }
                   stage++;
                   steps = executePattern(stage);
                   //k = 100;
                   myTimerADelay(100000,TIMER_A_CLOCKSOURCE_DIVIDER_20);
           }
               stage = 0;
               steps = 0;
    }else if((JSButton==GPIO_INPUT_PIN_LOW) && (JoyStickY <= YHIGH) && (JoyStickY >= YLOW) && (JoyStickX <= XHIGH) && (JoyStickX >= XLOW)){
        LED1=ON;
        LED2=ON;
            while(stage!=10){
                for(iii=0;iii<=steps;iii++){
                    stepMotor(phase);
                    if(phase==0) phase = 7;
                    else phase--;
                    myTimerADelay(215,TIMER_A_CLOCKSOURCE_DIVIDER_20);
                }
                stage++;
                steps = executePattern(stage);
                myTimerADelay(10000,TIMER_A_CLOCKSOURCE_DIVIDER_20);
        }
            stage = 0;
            steps = 0;
        }

    if(mode==ccw){
        if(phase==0)
            phase=7;
        else
            phase--;
    }else if(mode==cw){
        if(phase<7)
            phase++;
        else
            phase=0;
    }else if(mode==off){

    }
    if(LED1==ON){
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }else if(LED1==OFF){
        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
    if(LED2==ON){
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN1);
    }else if(LED2==OFF){
        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN1);
    }else if(LED2==toggle){
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN1);
        myTimerADelay(50000,TIMER_A_CLOCKSOURCE_DIVIDER_20);
    }






    if (speed==fast){
        myTimerADelay(430,TIMER_A_CLOCKSOURCE_DIVIDER_20);
    }else if(speed==slow){
        myTimerADelay(215,TIMER_A_CLOCKSOURCE_DIVIDER_20);
    }else{
        myTimerADelay(430,TIMER_A_CLOCKSOURCE_DIVIDER_20);
    }



    stepMotor(phase);

}

/*configIO function
 * Inputs: none
 * Outputs: none
 * Written by: Alexia Mullings
 * Date: 11/11/2020
 * Configures inputs with pull up resistors and sets all outputs
 * to low
 */
void configIO(){
        //S1 and S2 as inputs with pull-up resistors
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4,GPIO_PIN3);    //S1
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4,GPIO_PIN2);    //S2
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6,GPIO_PIN2);    //JoyStickPushbutton


        // Set LED1 as output
        GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
        GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN1);
        GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2); //mirror

        //RGB
        GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN6);//B
        GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN5);//R
        GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);//G

        //Activate the configuration using PMM_unlockLPM5()
        PMM_unlockLPM5();

        //set to LOW
        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN1);

        //set red, blue, and green low
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);

        PMM_unlockLPM5();


}

/* stepMotor function
 * Inputs: count of sequence
 * Outputs: none
 * Drives using half step
 */

void stepMotor(){
    switch(phase){
        case 0:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;

        case 1:
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 2:
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 3:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 4:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 5:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 6:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 7:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case 8:
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
            }
 }


// joyStick_init
// Configures mkII joysticks to analog inputs on FR599a
// Inputs: none
// Returns: none

void joyStick_init(){

    // JoyStick X
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3, GPIO_PIN3, GPIO_TERNARY_MODULE_FUNCTION);

    // JoyStick Y
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1, GPIO_PIN2, GPIO_TERNARY_MODULE_FUNCTION);

}
// ADC_init
// Configures ADC to use joystick inputs
// Inputs: none
// Returns: none

void ADC_init(){

    //Initialize the ADC12B Module
    /*
    * Base address of ADC12B Module
    * Use internal ADC12B bit as sample/hold signal to start conversion
    * USE MODOSC 5MHZ Digital Oscillator as clock source
    * Use default clock divider/pre-divider of 1
    * Not use internal channel
    */
    ADC12_B_initParam initParam = {0};
    initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
    initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
    initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
    initParam.internalChannelMap = ADC12_B_NOINTCH;
    ADC12_B_init(ADC12_B_BASE, &initParam);

    //Enable the ADC12B module
    ADC12_B_enable(ADC12_B_BASE);

    /*
    * Base address of ADC12B Module
    * For memory buffers 0-7 sample/hold for 64 clock cycles
    * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
    * Enable Multiple Sampling
    */
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
      ADC12_B_CYCLEHOLD_16_CYCLES,
      ADC12_B_CYCLEHOLD_4_CYCLES,
      ADC12_B_MULTIPLESAMPLESENABLE);

    //Configure Memory Buffer
    /*
    * Base address of the ADC12B Module
    * Configure memory buffer 0
    * Map input A1 to memory buffer 0
    * Vref+ = AVcc
    * Vref- = AVss
    * Memory buffer 0 is not the end of a sequence
    */
    //  JoyStickXParam Structure
    ADC12_B_configureMemoryParam joyStickXParam = {0};
    joyStickXParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    joyStickXParam.inputSourceSelect = ADC12_B_INPUT_A2;
    joyStickXParam.refVoltageSourceSelect = ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    joyStickXParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
    joyStickXParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    joyStickXParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    ADC12_B_configureMemory(ADC12_B_BASE, &joyStickXParam);

    //  JoyStickYParam Structure
    ADC12_B_configureMemoryParam joyStickYParam = {0};
    joyStickYParam.memoryBufferControlIndex = ADC12_B_MEMORY_1;
    joyStickYParam.inputSourceSelect = ADC12_B_INPUT_A15;
    joyStickYParam.refVoltageSourceSelect = ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    joyStickYParam.endOfSequence = ADC12_B_ENDOFSEQUENCE;
    joyStickYParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    joyStickYParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    ADC12_B_configureMemory(ADC12_B_BASE, &joyStickYParam);


    // Clear Interrupt
    ADC12_B_clearInterrupt(ADC12_B_BASE,0,ADC12_B_IFG1);

    //Enable memory buffer 1 interrupt
//    ADC12_B_enableInterrupt(ADC12_B_BASE,ADC12_B_IE1,0,0);

}

// configTimerA
// Configuration Parameters for TimerA
// Inputs: delayValue -- number of count cycles
//         clockDividerValue -- clock divider
// Returns: None

void configTimerA(uint16_t delayValue, uint16_t clockDividerValue)
{
    MyTimerA.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    MyTimerA.clockSourceDivider = clockDividerValue;
    MyTimerA.timerPeriod = delayValue;
    MyTimerA.timerClear = TIMER_A_DO_CLEAR;
    MyTimerA.startTimer = false;
}

// myTimerADelay
// Hardware Timer Delay function using polling with Timer A
// Inputs: delayValue -- number of count cycles
//         clockDividerValue -- clock divider
// Returns: none

void myTimerADelay(uint16_t delayValue, uint16_t clockDividerValue)
{

   configTimerA(delayValue,clockDividerValue);  // Configure the timer parameters
   Timer_A_initUpMode(TIMER_A0_BASE,&MyTimerA); // Initialize the timer
   Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);  // Start Timer
   while((TA0CTL&TAIFG) == 0);                   // Wait for TAIFG to become Set
   Timer_A_stop(TIMER_A0_BASE);                  // Stop timer
   Timer_A_clearTimerInterrupt(TIMER_A0_BASE);   // Reset TAIFG to Zero
}

// config_PWM
// Configures PWM Channel TB0.6
// Inputs: timerPeriod -- number of count cycles
//         timerDivider -- clock divider
// Returns: none


void config_PWM(uint16_t timerPeriod, uint16_t timerDivider){

    MyTimerB.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
    MyTimerB.clockSourceDivider = timerDivider;
    MyTimerB.timerPeriod = timerPeriod;
    MyTimerB.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_6;
    MyTimerB.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    MyTimerB.dutyCycle = timerPeriod / 2;
    Timer_B_outputPWM(TIMER_B0_BASE,&MyTimerB);     // Initialize Timer
}
uint16_t executePattern(uint16_t stage){
    uint16_t stepper;
    switch(stage){
        case 0:
            stepper = 0;
            break;
        case 1:
            stepper = 34;
            break;
        case 2:
            stepper = 200;
            break;
        case 3:
            stepper = 100;
            break;
        case 4:
            stepper = 200;
            break;
        case 5:
            stepper = 136;
            break;
        case 6:
            stepper = 200;
            break;
        case 7:
            stepper = 266;
            break;
        case 8:
            stepper = 300;
            break;
        case 9:
            stepper = 366;
            break;
    }
    return stepper;
}
