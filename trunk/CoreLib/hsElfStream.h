#ifndef _HSELFSTREAM_H
#define _HSELFSTREAM_H

#include "hsStream.h"

class hsElfStream : private hsStream {
private:
    void decipher(char* v, int size, char key);
    void encipher(char* v, int size, char key);

public:
    hsElfStream();
    virtual ~hsElfStream();
    
    virtual char* readLine();
    virtual void writeLine(const char* ln);
};

#endif

