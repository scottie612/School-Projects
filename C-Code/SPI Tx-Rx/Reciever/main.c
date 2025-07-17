#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

const eUSCI_SPI_SlaveConfig spiSlaveConfig =
{
 EUSCI_B_SPI_MSB_FIRST,                          // MSB First
 EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,  // Phase
 EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,     // Normal Polarity
 EUSCI_B_SPI_3PIN                               // 3wire mode
};

char RXData;
int i = 0;

void main(void){

    WDT_A_holdTimer();

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);

    SPI_initSlave(EUSCI_B0_BASE, &spiSlaveConfig);
    SPI_enableModule(EUSCI_B0_BASE);
    SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT);

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

        if(RXData == '1'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
            for(i=0;i<175000;i++){};
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);

        }
        else if(RXData == '2'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN0);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN0);
            for(i=0;i<100000;i++){};
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
            for(i=0;i<100000;i++){}
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
            for(i=0;i<100000;i++){}
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN0);
            for(i=0;i<100000;i++){};
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
            for(i=0;i<100000;i++){};
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 |GPIO_PIN2);


        }

        SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);}
    else if(status & EUSCI_B_SPI_TRANSMIT_INTERRUPT){
        SPI_transmitData(EUSCI_B0_BASE, RXData);
        SPI_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);}
}
