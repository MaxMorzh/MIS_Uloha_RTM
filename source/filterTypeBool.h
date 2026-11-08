
#ifndef _FILTER_TYPE_BOOL_H
#define _FILTER_TYPE_BOOL_H

#include <stdbool.h>

// stavy automatu filtru
enum {s0, s1, s2, s3, s4, s5};

typedef struct
{
    char state;  // aktualni stav (s0 az s5)
    bool output; // vystup filtru
} filterTypeBool_t;

void initFilterTypeBool(filterTypeBool_t *filter, bool initValue);
bool runFilterTypeBool(filterTypeBool_t *filter, bool value);

#endif

