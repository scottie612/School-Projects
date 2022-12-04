#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

uint8_t state=0;

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
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        32000,
        TIMER_A_CAPTURECOMPARE_REGISTER_3,
        TIMER_A_OUTPUTMODE_RESET_SET,
        3200
};




int main(void)
{
    /* Stop Watchdog  */

    uint8_t sens0,sens1,sens2,sens3,sens4,sens5,sens6,sens7;
    uint8_t i=0 ;
    bool middle2, left3, right3;

    WDT_A_holdTimer();

    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P9,GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN3);



    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2| GPIO_PIN3| GPIO_PIN5| GPIO_PIN6| GPIO_PIN7); // bumper switches

    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN7| GPIO_PIN6); // left/right motor enable
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN4| GPIO_PIN5); // left/right motor direction

    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high
    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);// set direction forward


    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);


    leftmotor_pwmConfig.dutyCycle = 4000;
    rightmotor_pwmConfig.dutyCycle = 4000;

    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);


    while(1)
    {

        GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN3);
        GPIO_setOutputHighOnPin(GPIO_PORT_P9,GPIO_PIN2);


        GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2 |GPIO_PIN3 |GPIO_PIN4 |GPIO_PIN5 |GPIO_PIN6 |GPIO_PIN7);

        GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2 |GPIO_PIN3 |GPIO_PIN4 |GPIO_PIN5 |GPIO_PIN6 |GPIO_PIN7);

        __delay_cycles(30);

        GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2 |GPIO_PIN3 |GPIO_PIN4 |GPIO_PIN5 |GPIO_PIN6 |GPIO_PIN7); // sensors
        __delay_cycles(3000);

        sens0 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
        sens1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
        sens2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
        sens3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
        sens4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
        sens5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
        sens6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
        sens7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);

       left3= (sens0 || sens1 || sens2);
       middle2= (sens3 || sens4);
       right3= (sens5 || sens6 || sens7);

        for(i=0;i !=10; i++){
            if((middle2==1)&& (left3==0)&& (right3==0)){                                // go strait
                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1); //green high
                GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0 |GPIO_PIN2);

                GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high
                GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);//set both strait
                leftmotor_pwmConfig.dutyCycle = 4000;
                rightmotor_pwmConfig.dutyCycle = 4000;

                Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);
                state=0;

            }else if((middle2==1)&& (left3==1)&& (right3==0)){                                // go left
                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2); //blue high
                GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0 |GPIO_PIN1);

                GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high
                GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);//set both strait
                leftmotor_pwmConfig.dutyCycle = 4000;
                rightmotor_pwmConfig.dutyCycle = 1000;

                Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);
                state=1;
            }else if((middle2==1)&& (left3==0)&& (right3==1)){                                // go right
                GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0); //red high
                GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1 |GPIO_PIN2);

                GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high
                GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4 | GPIO_PIN5);//set both strait
                leftmotor_pwmConfig.dutyCycle = 1000;
                rightmotor_pwmConfig.dutyCycle = 4000;

                Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);
                state=2;
            }else if((middle2==0)&& (left3==0)&& (right3==0)){
                GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2);
                if(state==1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high  //90 DEGREE LEFT
                    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4);
                    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN5);//set left forward and right backward
                    leftmotor_pwmConfig.dutyCycle = 4000;
                    rightmotor_pwmConfig.dutyCycle = 4000;

                    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);


                }else if(state==2){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high  // 90 DEGREE RIGHT
                    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN5);//set right forward and left backward
                    leftmotor_pwmConfig.dutyCycle = 4000;
                    rightmotor_pwmConfig.dutyCycle = 4000;

                    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);

                }else if(state==0){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7 | GPIO_PIN6);// Set enable high  // 90 DEGREE RIGHT
                    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN5); // WHEN LINE WAS STRAIT, STOP WHEN NO BLACK LINE
                    leftmotor_pwmConfig.dutyCycle = 4000;
                    rightmotor_pwmConfig.dutyCycle = 4000;

                    Timer_A_generatePWM(TIMER_A0_BASE, &leftmotor_pwmConfig);
                    Timer_A_generatePWM(TIMER_A0_BASE, &rightmotor_pwmConfig);

                }
            }
        }


        GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN3);
        GPIO_setOutputLowOnPin(GPIO_PORT_P9,GPIO_PIN2);

    }
}




