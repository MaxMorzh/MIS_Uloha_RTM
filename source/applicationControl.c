
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

//-- latform Function prototypes are in "platrformDEP32mk" ---------------------

//--- User function prototypes -------------------------------------------------


//--- Macros ------------------------------------------------------------------


//--- Constants ---------------------------------------------------------------
#define DELAY_ms  500

//--- New variable types ------------------------------------------------------

//--- Global vars -------------------------------------------------------------
filterTypeBool_t filterS9A, filterS9B;
filterTypeBool_t filterS1, filterS2;
memoryTypeBool_t memS1, memS2;
//--- External vars -----------------------------------------------------------

//---- Functions --------------------------------------------------------------

void configApplication(void){//------------------------------------------------
  //--- User defined functions ---
  // inicializace filtru podle aktualniho stavu vstupu
    initFilterTypeBool(&filterS9A, getCoderChannelA());
    initFilterTypeBool(&filterS9B, getCoderChannelB());
    initFilterTypeBool(&filterS1, getButtonS1());
    initFilterTypeBool(&filterS2, getButtonS2());

    // na zacatku LED V1 a V2 zhasnute
    initMemoryTypeBool(&memS1, false);
    initMemoryTypeBool(&memS2, false);
  
}// configApplication() END 

//===>>>> Call it every 1ms <<<<===

void runApplication(void) {//--------------------------------------------------
    bool s9a, s9b;
    bool s1, s2;

    // filtrace stop koderu S9 a zobrazeni na LED V10, V11
    s9a = runFilterTypeBool(&filterS9A, getCoderChannelA());
    s9b = runFilterTypeBool(&filterS9B, getCoderChannelB());
    setCoderLedA(s9a);
    setCoderLedB(s9b);

    // tlacitko S1 -> filtr -> pamet -> LED V1
    s1 = runFilterTypeBool(&filterS1, getButtonS1());
    setLedV1(runMemoryTypeBool(&memS1, s1));

    // tlacitko S2 -> filtr -> pamet -> LED V2
    s2 = runFilterTypeBool(&filterS2, getButtonS2());
    setLedV2(runMemoryTypeBool(&memS2, s2));
}// runApplication() END)

//--- applicationControl.c file END -------------------------------------------


