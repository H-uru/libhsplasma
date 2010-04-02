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
    static void WriteStreamHeader(hsStream* S, plString name, int version,
                                  plUoid* objUoid);
    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    /*void prcParse(const pfPrcTag* tag);*/ //Zrax'll kill me >.>

    plStateDescriptor* getDescriptor() const { return fDescriptor; }
    void setDescriptor(plStateDescriptor* desc);

    size_t getNumVars() const { return fAllVars.getSize(); }
    plStateVariable* get(size_t idx) const { return fAllVars[idx]; }
    plStateVariable* get(plString& name) const;
};

#endif
