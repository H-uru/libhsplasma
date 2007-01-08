#ifndef _PLSTRING_H
#define _PLSTRING_H

#include "../plCreatable.h"
#include "../CoreLib/hsStream.h"

class plString : public plCreatable {
private:
    char* str;  // Yes, I like C-style strings, ok?

public:
    plString();
    plString(plString * init);
    plString(const char* init);
    ~plString();

    const char* value();
    void set(const char* value);

    int length();

    void read(hsStream * S);
    void write(hsStream * S);
};

#endif

