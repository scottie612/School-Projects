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

    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN7| GPIO_PIN6); // left/right motor enable
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN4| GPIO_PIN5); // left/right motor direction

    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable off
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);// set direction forward 0 for forward, 1 for reverse


    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);


    leftmotor_pwmConfig.dutyCycle = 6000;
    rightmotor_pwmConfig.dutyCycle = 6000;

    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);



    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn on
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
    for(i=0;i<1000000;i++);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn on
    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
    for(i=0;i<2000000;i++);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6); //turn on
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);
    for(i=0;i<1000000;i++);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);
}
