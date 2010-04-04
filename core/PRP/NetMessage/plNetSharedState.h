#ifndef _PLNETSHAREDSTATE_H
#define _PLNETSHAREDSTATE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllStruct plGenericType {
public:
    enum Type {
        kInt, kFloat, kBool, kString, kByte, kAny, kUint, kDouble, kNone = 0xFF
    };

    union {
        int fInt;
        unsigned int fUint;
        float fFloat;
        double fDouble;
        bool fBool;
        signed char fByte;
    };
    plString fString;
    unsigned char fType;

public:
    plGenericType();

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
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plString getName() const { return fName; }
    const plGenericType& getValue() const { return fValue; }

    void setName(const plString& name) { fName = name; }
    void setValue(const plGenericType& value) { fValue = value; }

    plGenericType::Type getType() const { return (plGenericType::Type)fValue.fType; }
    int getInt() const { return fValue.fInt; }
    unsigned int getUint() const { return fValue.fUint; }
    float getFloat() const { return fValue.fFloat; }
    double getDouble() const { return fValue.fDouble; }
    bool getBool() const { return fValue.fBool; }
    signed char getByte() const { return fValue.fByte; }
    plString getString() const { return fValue.fString; }
};


DllClass plNetSharedState {
private:
    plString fName;
    hsTArray<plGenericVar> fVars;
    bool fServerMayDelete;

public:
    plNetSharedState();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plString getName() const { return fName; }
    bool getServerMayDelete() const { return fServerMayDelete; }

    void setName(const plString& name) { fName = name; }
    void setServerMayDelete(bool may) { fServerMayDelete = may; }

    const hsTArray<plGenericVar>& getVars() const { return fVars; }
    hsTArray<plGenericVar>& getVars() { return fVars; }
    void addVar(const plGenericVar& var) { fVars.append(var); }
    void delVar(size_t idx) { fVars.remove(idx); }
    void clearVars() { fVars.clear(); }
};

#endif
