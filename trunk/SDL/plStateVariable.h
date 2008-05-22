#ifndef _PLSTATEVARIABLE_H
#define _PLSTATEVARIABLE_H

#include "plStateDescriptor.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Math/hsMatrix44.h"
#include "Sys/hsColor.h"
#include "Sys/plUnifiedTime.h"
#include "PRP/plCreatable.h"

DllClass plStateVarNotificationInfo {
protected:
    plString fHintString;

public:
    plStateVarNotificationInfo();
    ~plStateVarNotificationInfo();

    void read(hsStream* S);
    void write(hsStream* S);
};

DllClass plStateVariable {
protected:
    unsigned char fContents;
    plStateVarNotificationInfo fNotificationInfo;
    plVarDescriptor* fDescriptor;
    size_t fCount;

public:
    plStateVariable();
    virtual ~plStateVariable();

    virtual void setDescriptor(plVarDescriptor* desc) = 0;
    plVarDescriptor* getDescriptor() const;
    size_t getCount() const;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};

DllClass plSDStateVariable : public plStateVariable {
protected:
    hsTArray<class plStateDataRecord*> fDataRecList;

public:
    plSDStateVariable();
    virtual ~plSDStateVariable();

    virtual void setDescriptor(plVarDescriptor* desc);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};

DllClass plSimpleStateVariable : public plStateVariable {
protected:
    union {
        int* fInt;
        unsigned int* fUint;
        short* fShort;
        unsigned char* fByte;
        signed char* fChar;
        float* fFloat;
        double* fDouble;
        bool* fBool;
        plUoid* fUoid;
        plCreatable** fCreatable;
        plString* fString;
        plUnifiedTime* fTime;
        hsVector3* fVector;
        hsQuat* fQuat;
        hsColorRGBA* fColorRGBA;
        hsColor32* fColor32;
        hsMatrix44* fMatrix;
    };
    plUnifiedTime fTimeStamp;

public:
    plSimpleStateVariable();
    virtual ~plSimpleStateVariable();

    virtual void setDescriptor(plVarDescriptor* desc);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

    void SetFromDefault();

    int& Int(size_t idx);
    unsigned int& Uint(size_t idx);
    short& Short(size_t idx);
    unsigned char& Byte(size_t idx);
    signed char& Char(size_t idx);
    float& Float(size_t idx);
    double& Double(size_t idx);
    bool& Bool(size_t idx);
    plUoid& Uoid(size_t idx);
    plCreatable*& Creatable(size_t idx);
    plString& String(size_t idx);
    plUnifiedTime& Time(size_t idx);
    hsVector3& Vector(size_t idx);
    hsQuat& Quat(size_t idx);
    hsColorRGBA& ColorRGBA(size_t idx);
    hsColor32& Color32(size_t idx);
    hsMatrix44& Matrix(size_t idx);

protected:
    void IReadData(hsStream* S, plResManager* mgr, size_t idx);
    void IWriteData(hsStream* S, plResManager* mgr, size_t idx);
};

#endif
