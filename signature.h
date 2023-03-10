#ifndef _INCLUDE_SIGNATURE_
#define _INCLUDE_SIGNATURE_

void *get_func(void *addr, const char *func);
void *find_base(const char *name);
void write_signature(void *addr, const void *sign);
#endif //_INCLUDE_SIGNATURE_
