
#ifndef _MEMORY_TYPE_BOOL_H
#define _MEMORY_TYPE_BOOL_H

#include <stdbool.h>

typedef struct
{
    bool prevValue; // minuly stav vstupu
    bool output;    // zapamatovany vystup
} memoryTypeBool_t;

void initMemoryTypeBool(memoryTypeBool_t *mem, bool initValue);
bool runMemoryTypeBool(memoryTypeBool_t *mem, bool value);

#endif
