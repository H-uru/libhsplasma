#ifndef _HSELFSTREAM_H
#define _HSELFSTREAM_H

#include "hsStream.h"

class hsElfStream : private hsStream {
private:
    void decipher(unsigned char* v, int size, unsigned char hint);
    void encipher(unsigned char* v, unsigned char hint);

protected:
    unsigned char hint;

public:
    hsElfStream();
    virtual ~hsElfStream();
    
    virtual plString readLine();
    virtual void writeLine(const plString& ln);
};

#endif

