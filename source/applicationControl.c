
/*
 * File:    applicationControl.c (For MIS)
 * j.z.
 *  
 * MPLABX.IDE v5.10, XC32 v3.00, HW: DEP-PIC32-MK
 * 
 * Created:  2024.06.16
 * Modified: 2024.08.12
 * 
 */

/*==== History trace buffer ===================================================

2024.08.12-Replaced: #include "platformDEP32mk.h" by platformMIS32mk.h
2024.08.09-Mldified: Source code cleaned up.
2024.06.16-New: applicationControl.c TEMPLATE for students MIS 
-------------------------------------------------------------------------------

2023.02.10-New: applicationControl.c TEMPLATE for students DEP 
==== History trace buffer END ================================================*/

//--- Includes ----------------------------------------------------------------
#include <xc.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include "platformMIS32mk.h"
#include "filterTypeBool.h"
#include "memoryTypeBool.h"
#include "messengerMIS.h"

//-- latform Function prototypes are in "platrformDEP32mk" ---------------------

//--- User function prototypes -------------------------------------------------


//--- Macros ------------------------------------------------------------------


//--- Constants ---------------------------------------------------------------
#define DELAY_ms  500
#define MSG_MAX 17
//--- New variable types ------------------------------------------------------

//--- Global vars -------------------------------------------------------------
filterTypeBool_t filterS1, filterS2, filterS3, filterS9A, filterS9B;
memoryTypeBool_t memS1, memS2, memS3;

unsigned char txMsg[MSG_MAX];
unsigned char rxMsg[MSG_MAX];
//--- External vars -----------------------------------------------------------

//---- Functions --------------------------------------------------------------

void configApplication(void){//------------------------------------------------
  //--- User defined functions ---
    int i;

    // inicializace filtru podle aktualniho stavu vstupu
    initFilterTypeBool(&filterS1, getButtonS1());
    initFilterTypeBool(&filterS2, getButtonS2());
    initFilterTypeBool(&filterS3, getButtonS3());
    initFilterTypeBool(&filterS9A, getCoderChannelA());
    initFilterTypeBool(&filterS9B, getCoderChannelB());

    // na zacatku LED V1, V2 a V3 zhasnute
    initMemoryTypeBool(&memS1, false);
    initMemoryTypeBool(&memS2, false);
    initMemoryTypeBool(&memS3, false);

    // nulovani komunikacnich poli
    for (i = 0; i < MSG_MAX; i++)
    {
        txMsg[i] = 0;
        rxMsg[i] = 0;
    }
}// configApplication() END 

//===>>>> Call it every 1ms <<<<===

void runApplication(void) {//--------------------------------------------------
    bool s9a, s9b;
    bool s1, s2, s3;
    bool outS1, outS2, outS3;

    // filtrace stop koderu S9 a zobrazeni na LED V10, V11
    s9a = runFilterTypeBool(&filterS9A, getCoderChannelA());
    s9b = runFilterTypeBool(&filterS9B, getCoderChannelB());
    setCoderLedA(s9a);
    setCoderLedB(s9b);

    // tlacitko S1 -> filtr -> pamet -> LED V1
    s1 = runFilterTypeBool(&filterS1, getButtonS1());
    outS1 = runMemoryTypeBool(&memS1, s1);
    setLedV1(outS1);

    // tlacitko S2 -> filtr -> pamet -> LED V2
    s2 = runFilterTypeBool(&filterS2, getButtonS2());
    outS2 = runMemoryTypeBool(&memS2, s2);
    setLedV2(outS2);

    // tlacitko S3 -> filtr -> pamet -> LED V3
    s3 = runFilterTypeBool(&filterS3, getButtonS3());
    outS3 = runMemoryTypeBool(&memS3, s3);
    setLedV3(outS3);
}// runApplication() END)

//--- applicationControl.c file END -------------------------------------------


