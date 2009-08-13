#ifndef _PLNETSHAREDSTATE_H
#define _PLNETSHAREDSTATE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plGenericType {
public:
    enum Type {
        kInt, kFloat, kBool, kString, kByte, kAny, kUInt, kDouble, kNone = 0xFF
    };

private:
    union {
        int fInt;
        unsigned int fUInt;
        float fFloat;
        double fDouble;
        bool fBool;
        signed char fByte;
    };
    plString fString;
    unsigned char fType;

public:
    plGenericType();
    ~plGenericType();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plGenericVar {
private:
    plString fName;
    plGenericType fValue;

public:
    plGenericVar();
    ~plGenericVar();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plNetSharedState {
private:
    plString fName;
    hsTArray<plGenericVar> fVars;
    bool fServerMayDelete;

public:
    plNetSharedState();
    ~plNetSharedState();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
