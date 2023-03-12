#ifndef _INCLUDE_SIGNATURE_
#define _INCLUDE_SIGNATURE_

void *find_base(const char *name);
void write_signature(void *addr, const void *sign);
#endif //_INCLUDE_SIGNATURE_
