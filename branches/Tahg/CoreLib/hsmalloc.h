void * MemAlloc(unsigned int, unsigned int, const char *, int);

inline void * __cdecl operator new(unsigned int bytes) { return MemAlloc(bytes, 0, __FILE__, __LINE__); }
