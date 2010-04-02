#ifndef _PLSERVERGUID_H
#define _PLSERVERGUID_H

#include "../PlasmaDefs.h"
#include "../Stream/hsStream.h"

DllClass plServerGuid {
protected:
    unsigned char fGuid[8];

public:
    plServerGuid();
    plServerGuid(const plServerGuid& init);
    plServerGuid& operator=(const plServerGuid& other);
    bool operator==(const plServerGuid& other);
    bool operator!=(const plServerGuid& other) { return !operator==(other); }

    unsigned char operator[](size_t idx) const { return fGuid[idx]; }
    unsigned char& operator[](size_t idx) { return fGuid[idx]; }
    plString toString() const;
    static plServerGuid FromString(const plString& str);

    void read(hsStream* S);
    void write(hsStream* S);
};

#endif
