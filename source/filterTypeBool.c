#include "filterTypeBool.h"

// nastaveni vychoziho stavu podle vstupu po resetu
void initFilterTypeBool(filterTypeBool_t *filter, bool initValue)
{
    if (initValue == true)
    {
        filter->state = s3;
        filter->output = true;
    }
    else
    {
        filter->state = s0;
        filter->output = false;
    }
}

// filtrace zakmitu (volano kazdou 1 ms)
bool runFilterTypeBool(filterTypeBool_t *filter, bool value)
{
    switch (filter->state)
    {
        case s0: // ustalena 0
        {
            filter->output = false;
            if (value == true)
            {
                filter->state = s1; // prvni 1
            }
            break;
        }
        case s1:
        {
            if (value == true)
            {
                filter->state = s2; // druha 1 za sebou
            }
            else
            {
                filter->state = s0; // zakmit, zpet do s0
            }
            break;
        }
        case s2:
        {
            if (value == true)
            {
                filter->state = s3; // treti 1 -> prechod do ustalene 1
                filter->output = true;
            }
            else
            {
                filter->state = s0; // zakmit, zpet do s0
            }
            break;
        }
        case s3: // ustalena 1
        {
            filter->output = true;
            if (value == false)
            {
                filter->state = s4; // prvni 0
            }
            break;
        }
        case s4:
        {
            if (value == false)
            {
                filter->state = s5; // druha 0 za sebou
            }
            else
            {
                filter->state = s3; // zakmit, zpet do s3
            }
            break;
        }
        case s5:
        {
            if (value == false)
            {
                filter->state = s0; // treti 0 -> prechod do ustalene 0
                filter->output = false;
            }
            else
            {
                filter->state = s3; // zakmit, zpet do s3
            }
            break;
        }
        default:
        {
            filter->state = s0;
            filter->output = false;
            break;
        }
    }

    return filter->output;
}

