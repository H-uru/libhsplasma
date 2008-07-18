#ifndef _PLSTATEDATARECORD_H
#define _PLSTATEDATARECORD_H

#include "plSDLMgr.h"
#include "plStateVariable.h"

DllClass plStateDataRecord {
public:
    enum Flags {
        kVolatile = 0x1
    };

protected:
    static const unsigned char kIOVersion;

    plStateDescriptor* fDescriptor;
    plUoid fAssocObject;
    hsTArray<plStateVariable*> fVarsList, fSDVarsList;
    hsTArray<plStateVariable*> fAllVars;
    unsigned int fFlags;

public:
    plStateDataRecord();
    ~plStateDataRecord();

    static void ReadStreamHeader(hsStream* S, plString& name, int& version,
                                 plUoid* objUoid);

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    
    void setDescriptor(plStateDescriptor* desc);

    plStateVariable* get(size_t idx) const;
    plStateVariable* get(plString& name) const;
    size_t getNumVars() const;
};

#endif
