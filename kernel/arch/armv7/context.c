#include "bolun/kernel.h"
#include <string.h>
void armv7_switch(armv7_context_t *from, const armv7_context_t *to){ if(from && to) memcpy(from,to,sizeof(*from)); }
