/* XDC Module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/drivers/SPI.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
/* Example/Board Header files */
#include "Board.h"
#include <stdbool.h>

bool loop = true;

SPI_Handle spiHandle;
SPI_Params spiParams;
SPI_Transaction spiTransaction;
/* Pin driver handles */
static PIN_Handle pinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State pinState;

PIN_Config pinTable[] = {
Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,
IOID_30 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
PIN_TERMINATE };

void delay_s(int dly) {

    while (dly > 0) {
        __delay_cycles(48000000);
        dly--;

    }
}
void delay_ms(int dly) {

    while (dly > 0) {
        __delay_cycles(48000);
        dly--;

    }
}
#define c 0x01
Char myTaskStack[1024];
Task_Struct myTaskStruct;

Void taskFxn(UArg arg0, UArg arg1) {
  System_printf("Start SPI task\n");

  SPI_Params_init(&spiParams);
  spiParams.transferMode = SPI_MODE_BLOCKING;
  spiParams.transferTimeout = SPI_WAIT_FOREVER;
  spiParams.transferCallbackFxn = NULL;
  spiParams.mode = SPI_MASTER;
  spiParams.bitRate = 4000000;
  spiParams.dataSize = 6;
  spiHandle = SPI_open(0, &spiParams);
  
  while (loop) {

    PIN_setOutputValue(pinHandle, Board_LED0, 1);
    delay_ms(2000);
    PIN_setOutputValue(pinHandle, Board_LED0, 0);
    delay_ms(2000);

    uint8_t transmitBuffer[1];

    transmitBuffer[0] = c;

    spiTransaction.count = 1;
    spiTransaction.txBuf = transmitBuffer;
    spiTransaction.rxBuf = NULL;

    SPI_transfer(spiHandle, &spiTransaction);

  }
}

// ======== SETUP ========
void setup(){
    BIOS_start();

  System_printf("Start Setup\n");
  /* Call board init functions */
  //Board_initGeneral(); 
  Board_initSPI();
  pinHandle = PIN_open(&pinState, pinTable);
  if (!pinHandle) {
    System_abort("Error initializing board LED pins\n");
  }

  /* Configure task. */
  Task_Params taskParams;
  Task_Params_init(&taskParams);
  taskParams.stack = myTaskStack;
  taskParams.stackSize = sizeof(myTaskStack);
  Task_construct(&myTaskStruct, taskFxn, &taskParams, NULL);

  System_printf("End Setup\n");
}

/*
 *  ======== main ========
 */
Int main() {
    Board_initGeneral();
    System_printf("in the main\n");
    System_flush();
    setup();

  // to enable interrupts and start the scheduler and kick BIOS into gear.
  BIOS_start();

  // this should never be called
  return (0);
}
