#include <stdlib.h>
void ErrorFatal(int, const char *, const char *,...);
void * MemAlloc(unsigned int bytes, unsigned int flags, const char * file, int line) { //429-478
	void * addr = (flags & 2) ? calloc(bytes, 1) : malloc(bytes);
	if(!addr)
	{
		ErrorFatal(__LINE__, __FILE__, "Out of memory");
	}
	return addr;
}