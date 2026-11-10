#include "filterTypeBool.h"

// inicializace filtru podle pocatecni hodnoty vstupu
void initFilterTypeBool(filterTypeBool_t *filter, bool initValue)
{
    if (initValue == true)
    {
        filter->state = S3;
        filter->output = true;
    }
    else
    {
        filter->state = S0;
        filter->output = false;
    }
}

// filtr zakmitu - zmena vystupu po 3 shodnych vzorcich
bool runFilterTypeBool(filterTypeBool_t *filter, bool value)
{
    switch (filter->state)
    {
        case S0: // ustalena log. 0
        {
            filter->output = false;
            if (value == true)
            {
                filter->state = S1;
            }
            else
            {
                filter->state = S0;
            }
            break;
        }
        case S1: // 1x log. 1
        {
            if (value == true)
            {
                filter->state = S2;
            }
            else
            {
                filter->state = S0; // zakmit -> zpet do S0
            }
            break;
        }
        case S2: // 2x log. 1
        {
            if (value == true)
            {
                filter->state = S3;
                filter->output = true; // 3x log. 1 -> vystup 1
            }
            else
            {
                filter->state = S0; // zakmit -> zpet do S0
            }
            break;
        }
        case S3: // ustalena log. 1
        {
            filter->output = true;
            if (value == false)
            {
                filter->state = S4;
            }
            else
            {
                filter->state = S3;
            }
            break;
        }
        case S4: // 1x log. 0
        {
            if (value == false)
            {
                filter->state = S5;
            }
            else
            {
                filter->state = S3; // zakmit -> zpet do S3
            }
            break;
        }
        case S5: // 2x log. 0
        {
            if (value == false)
            {
                filter->state = S0;
                filter->output = false; // 3x log. 0 -> vystup 0
            }
            else
            {
                filter->state = S3; // zakmit -> zpet do S3
            }
            break;
        }
        default:
        {
            filter->state = S0;
            filter->output = false;
            break;
        }
    }

    return filter->output;
}
