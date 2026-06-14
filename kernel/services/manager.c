#include "bolun/kernel.h"
#include <string.h>
int bolun_service_register(const char *name,int owner_pid){ if(!name||owner_pid<=0||owner_pid>=BOLUN_MAX_PROCESSES) return -1; for(int i=0;i<BOLUN_MAX_SERVICES;i++){ bolun_service_t *s=&g_kernel.services[i]; if(s->name&&strcmp(s->name,name)==0){ s->owner_pid=owner_pid; return i; } if(!s->name){ s->name=name; s->owner_pid=owner_pid; s->running=false; return i; }} return -2; }
int bolun_service_set_running(const char *name,bool running){ if(!name) return -1; for(int i=0;i<BOLUN_MAX_SERVICES;i++) if(g_kernel.services[i].name&&strcmp(g_kernel.services[i].name,name)==0){ g_kernel.services[i].running=running; return 0; } return -2; }
