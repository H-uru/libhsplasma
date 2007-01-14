#ifndef _PLSTRING_H
#define _PLSTRING_H

#include "../NucleusLib/pnFactory/plCreatable.h"
#include "../CoreLib/hsStream.h"

class plString : public plCreatable {
private:
    char* str;  // Yes, I like C-style strings, ok?

public:
    plString(PlasmaVer pv = pvUnknown);
    plString(plString * init, PlasmaVer pv = pvUnknown);
    plString(const char* init, PlasmaVer pv = pvUnknown);
    ~plString();

    const char* value();
    void set(const char* value);

    int length();

    void read(hsStream * S);
    void write(hsStream * S);
};

#endif

