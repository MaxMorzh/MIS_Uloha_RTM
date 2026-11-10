#ifndef _FILTER_TYPE_BOOL_H
#define _FILTER_TYPE_BOOL_H

#include <stdbool.h>

// stavy konecneho automatu filtru
typedef enum
{
    S0 = 0, // ustalena log. 0
    S1,     // 1. vzorek log. 1
    S2,     // 2. vzorek log. 1
    S3,     // ustalena log. 1
    S4,     // 1. vzorek log. 0
    S5      // 2. vzorek log. 0
} filterState_t;

typedef struct
{
    filterState_t state; // aktualni stav automatu
    bool output;         // filtrovany vystup
} filterTypeBool_t;

void initFilterTypeBool(filterTypeBool_t *filter, bool initValue);
bool runFilterTypeBool(filterTypeBool_t *filter, bool value);

#endif
