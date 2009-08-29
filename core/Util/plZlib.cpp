#include "plZlib.h"

bool plZlib::Uncompress(unsigned char** bufIn, unsigned int* bufLenIn, unsigned int bufLenOut, int offset) {
	char* bufOut = new char[bufLenOut];
		
	bool ok = Uncompress((unsigned char*)bufOut, &bufLenOut, *bufIn + offset, *bufLenIn - offset);
	
	return ICopyBuffers(bufIn, bufLenIn, bufOut, bufLenOut, offset, ok);
}

bool plZlib::Uncompress(unsigned char* bufOut, unsigned int* bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn) {
	return uncompress(bufOut, (uLongf*)bufLenOut, bufIn, (uLongf)bufLenIn) == Z_OK;
}

bool plZlib::ICopyBuffers(unsigned char** bufIn, unsigned int* bufLenIn, char* bufOut, unsigned int bufLenOut, int offset, bool ok) {
	if(ok) {
		hsRAMStream* s = new hsRAMStream();
		*bufLenIn = bufLenOut + offset;
		s->resize(*bufLenIn);
		
		s->write(offset, *bufIn);
		s->write(bufLenOut, bufOut);
		
		delete[] *bufIn;
        *bufIn = new unsigned char[*bufLenIn];
		delete[] bufOut;
		
		s->copyTo(*bufIn, *bufLenIn);
        return true;
		
	} else {
		delete[] bufOut;
		return false;
	}
}
