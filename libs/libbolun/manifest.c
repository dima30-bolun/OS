#include <string.h>
int bolun_manifest_has_capability(const char *manifest,const char *cap){ return manifest&&cap&&strstr(manifest,cap)!=0; }
int bolun_xap_is_valid(const unsigned char *buf,unsigned len){ return len>4&&buf[0]=='P'&&buf[1]=='K'; }
int bolun_pe_is_arm(const unsigned char *buf,unsigned len){ if(len<0x40||buf[0]!='M'||buf[1]!='Z') return 0; unsigned pe=buf[0x3c]|(buf[0x3d]<<8); return pe+5<len&&buf[pe]=='P'&&buf[pe+1]=='E'&&buf[pe+4]==0x1c&&buf[pe+5]==0x01; }
