/*
 * File:
 * Orig:     messengerUSB.c
 * Renabmed: messengerUSBa.c
 * 
 * MPLABX.IDE v5.10, XC32 v3.00, HW: DEP-PIC32-MK
 * 
 * Created:  2024.06.18 
 * Modified: 2024.09.27 
 * 
 * HELP:
 *  Use RTM Monitor (A70)
 *  Set up Command Editor to "Integer" mode
 *  Set up Graphics to "Integer mode 
 *  Send from RTM Command Editor:
 *    1 - Send back integer msg (2 parameters sent from RTM),
 *    0,..7 - Stop TX
 */

/*==== History trace buffer ===================================================

2024.09.27-Tested: Available commands
          -Added: Help in project header
2024.06.18-New: For MIS modification 
-------------------------------------------------------------------------------
2023.03.08-New: Accepts RTM commands:
           0 - Stop TX (2 to 7 also stop),
           1 - Send back integer msg (2 parameters sent from RTM),
2023.03.08-New: Send back received integer parameters from RTM.
2023.03.08-New: essengerUSBa.c.
==== History trace buffer END ================================================*/

//--- Includes ----------------------------------------------------------------
#include <xc.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include "messengerMIS.h"
#include "platformMIS32mk.h"

//--- Constants ---------------------------------------------------------------
#define MSG_MAX 17   // must be divisible by four + 1
#define RTM_RX_INTEGER_MSG_LENGTH 7
#define RTM_TX_INTEGER_MSG_LENGTH 7

enum {TX_STOP, TX_INTEGER_GO, TX_FLOAT_GO};

//--- Global vars -------------------------------------------------------------
unsigned char txMsg[MSG_MAX];
unsigned char rxMsg[MSG_MAX];
signed short txCmdInteger = TX_STOP;

//--- User Functions -----------------------------------------------------------

void serialComA(void) {//-------------------------------------------------------
  static unsigned short cnt40ms = 0;
  static unsigned short cntMAX = 40;
  static bool com = false;
  static unsigned char messageLen = 0;
  static signed short intVar1 = 0;
  static signed short intVar2 = 0;
  static bool ledV4 = 0;

  if (cnt40ms++ == cntMAX) {
    cnt40ms = 0;

    if (getMessageUSB(rxMsg, COM_GO) == true) {
      messageLen = rxMsg[0];

      if ((messageLen EQUAL RTM_RX_INTEGER_MSG_LENGTH) &&
              ((txCmdInteger = bytesToInteger(&rxMsg[1]) EQUAL TX_INTEGER_GO))) {
        // RTM-Editor is not in integer mode
        com = true;
        // Get parameters  send from RTM
        intVar1 = bytesToInteger(&rxMsg[3]);
        intVar2 = bytesToInteger(&rxMsg[5]);
        // Send back variables received from RTM
        txMsg[0] = RTM_TX_INTEGER_MSG_LENGTH;
        integerToBytes(intVar1, &txMsg[1]);
        integerToBytes(intVar2, &txMsg[3]);
      } else {
        com = false;
      }
    }
    if (com == true) {
      sendMessageUSB(txMsg, COM_GO);
      setLedV4(ledV4 ^= 1);
    }
  } // END if (cnt40ms++ == 40)
} // END serialComA()
