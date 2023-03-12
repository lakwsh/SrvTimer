#include "signature.h"
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <link.h>

#define HEADER_LEN	2
#define LEN_BYTE	0
#define OFF_BYTE	1

static uint pmask = ~(sysconf(_SC_PAGESIZE)-1);

typedef struct{
	const char *name;
	void **base;
} v_data;

int callback(struct dl_phdr_info *info, size_t size, void *data){
	v_data *d = (v_data *)data;
	if(!info->dlpi_name || !strstr(info->dlpi_name, d->name)) return 0;
	*d->base = (void *)info->dlpi_addr;
	return 1;
}

void *find_base(const char *name){
	void *addr = NULL;
	v_data vdata = {name, &addr};
	dl_iterate_phdr(callback, &vdata);
	return addr;
}

void write_signature(void *addr, const void *sign){
	if(!addr || !sign) return;
	uint len = ((unsigned char *)sign)[LEN_BYTE];
	void *src = (void *)((uint)sign+HEADER_LEN);
	void *dst = (void *)((uint)addr+((char *)sign)[OFF_BYTE]);
	void *pa_addr = (void *)((uint)dst&pmask);
	uint size = (uint)dst-(uint)pa_addr+len;
	mlock(pa_addr, size);
	mprotect(pa_addr, size, PROT_READ|PROT_WRITE|PROT_EXEC);
	memcpy(dst, src, len);
	mprotect(pa_addr, size, PROT_READ|PROT_EXEC); // restore
	munlock(pa_addr, size);
}
