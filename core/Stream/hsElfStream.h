#ifndef _HSELFSTREAM_H
#define _HSELFSTREAM_H

#include "hsStream.h"

DllClass hsElfStream : public hsFileStream {
private:
    void decipher(unsigned char* v, int size, unsigned char hint);
    void encipher(unsigned char* v, int size, unsigned char hint);

protected:
    unsigned char hint;

public:
    hsElfStream();

    virtual plString readLine();
    virtual void writeLine(const plString& ln);
};

#endif

