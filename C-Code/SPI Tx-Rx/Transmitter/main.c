#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

const eUSCI_SPI_MasterConfig spiMasterConfig =
{
 EUSCI_B_SPI_CLOCKSOURCE_SMCLK,  // SMCLK Clock Source
 3000000,                        // SMCLK = DCO = 3MHZ
 1000000,                        // SPICLK = 1MHZ
 EUSCI_B_SPI_MSB_FIRST,          // MSB First
 EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
 EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
 EUSCI_B_SPI_3PIN                // 3Wire SPI Mode
};

char TXData[10] = "RGBBGRBGGR";
char RXData;
int i = 0;
bool pin4=false, pin1=false;

void main(void){

    WDT_A_holdTimer();

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);


    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);



    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1| GPIO_PIN4);

    SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
    SPI_enableModule(EUSCI_B0_BASE);
    SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT);

    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableInterrupt(INT_EUSCIB0);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();

    PCM_setPowerState(PCM_LPM0_LDO_VCORE1);
}

void EUSCIB0_IRQHandler(void){
    uint32_t status = SPI_getEnabledInterruptStatus(EUSCI_B0_BASE);
    SPI_clearInterruptFlag(EUSCI_B0_BASE, status);

    if(status & EUSCI_B_SPI_RECEIVE_INTERRUPT){
        RXData = SPI_receiveData(EUSCI_B0_BASE);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);}
    else if(status & EUSCI_B_SPI_TRANSMIT_INTERRUPT){
       if(pin1){
           pin1=false;
           SPI_transmitData(EUSCI_B0_BASE, '1');
           SPI_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
           GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
           GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
           for(i=0;i<175000;i++){};
           GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
           GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
       }
       if(pin4){
           pin4=false;
           SPI_transmitData(EUSCI_B0_BASE, '2');
           SPI_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
       }
    }
}

void PORT1_IRQHandler(void){
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if(status & GPIO_PIN1){
        pin1=true;
        SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);



    }if(status & GPIO_PIN4){
        pin4=true;
        SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);

    }




}
