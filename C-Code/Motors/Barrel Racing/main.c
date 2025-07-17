#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

Timer_A_PWMConfig leftmotor_pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        32000,
        TIMER_A_CAPTURECOMPARE_REGISTER_4,
        TIMER_A_OUTPUTMODE_RESET_SET,
        3200
};
Timer_A_PWMConfig rightmotor_pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_3,
        32000,
        TIMER_A_CAPTURECOMPARE_REGISTER_3,
        TIMER_A_OUTPUTMODE_RESET_SET,
        3200
};
int main(void)
{
    /* Stop Watchdog  */
    WDT_A_holdTimer();
    uint32_t i=0;
    volatile uint8_t PBS1 = 0, PBS2 = 0;

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN1 | GPIO_PIN4);

    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN7| GPIO_PIN6); // left/right motor enable
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN4| GPIO_PIN5); // left/right motor direction

    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable off
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);// set direction forward 0 for forward, 1 for reverse


    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);


    leftmotor_pwmConfig.dutyCycle = 12000;
    rightmotor_pwmConfig.dutyCycle = 12350;

    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);

    while(1){
    PBS1=GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1);
    PBS2=GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4);
    if(PBS2 == GPIO_INPUT_PIN_LOW){
        for(i=0;i<620000;i++);              // 3 s delay

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<1350000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn RIGHT
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
        for(i=0;i<101000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<550000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn RIGHT
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
        for(i=0;i<34000;i++)

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<1350000;i++);

        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);
    }else if(PBS1 == GPIO_INPUT_PIN_LOW){
        for(i=0;i<420000;i++);          // delay 2s

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<1350000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn left
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
        for(i=0;i<101000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<550000;i++);

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn Left
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
        for(i=0;i<35000;i++)

        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn STRAIT
        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
        for(i=0;i<1350000;i++);

        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);
    }
}
}

