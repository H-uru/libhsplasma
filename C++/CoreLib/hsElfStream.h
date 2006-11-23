#ifndef _HSELFSTREAM_H
#define _HSELFSTREAM_H

#include "hsStream.h"

class hsElfStream : private hsStream {
private:
    void decipher(char* v, int size, char key);

public:
    hsElfStream(const char* file, FileMode mode);
    ~hsElfStream();

    const char* readLine();
    void writeLine(const char* ln);
};

#endif

