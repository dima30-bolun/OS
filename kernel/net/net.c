#include <stdint.h>
#include <string.h>
uint16_t bolun_inet_checksum(const void *data,unsigned len){ const uint8_t *p=data; uint32_t sum=0; while(len>1){ sum+=((uint16_t)p[0]<<8)|p[1]; p+=2; len-=2; } if(len) sum+=(uint16_t)p[0]<<8; while(sum>>16) sum=(sum&0xffff)+(sum>>16); return (uint16_t)~sum; }
int bolun_dns_query_name(const char *host,unsigned char *out,unsigned cap){ unsigned w=0,start=0; for(unsigned i=0;;i++){ if(host[i]=='.'||host[i]==0){ unsigned n=i-start; if(w+1+n>=cap) return -1; out[w++]=(unsigned char)n; memcpy(out+w,host+start,n); w+=n; start=i+1; if(host[i]==0){ if(w>=cap) return -1; out[w++]=0; return (int)w; } } } }
