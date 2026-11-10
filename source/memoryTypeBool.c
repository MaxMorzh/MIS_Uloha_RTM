#include "memoryTypeBool.h"

// inicializace pameti po resetu
void initMemoryTypeBool(memoryTypeBool_t *mem, bool initValue)
{
    mem->prevValue = false;
    mem->output = initValue;
}

// zmena vystupu pri stisku tlacitka (nabezna hrana 0 -> 1)
bool runMemoryTypeBool(memoryTypeBool_t *mem, bool value)
{
    if (value == true && mem->prevValue == false)
    {
        mem->output = !mem->output; // negace minule hodnoty
    }

    mem->prevValue = value; // ulozeni stavu pro dalsi krok
    return mem->output;
}
