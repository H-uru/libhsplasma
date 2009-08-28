#include "plZlib.h"

bool plZlib::Uncompress(unsigned char* bufIn, unsigned int bufLenIn, unsigned char* bufOut, unsigned int* bufLenOut) {
	return uncompress(bufOut, (uLongf*)bufLenOut, bufIn, (uLongf)bufLenIn) == Z_OK;
}
