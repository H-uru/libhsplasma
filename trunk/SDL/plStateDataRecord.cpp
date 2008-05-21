#include "plStateDataRecord.h"

const unsigned char plStateDataRecord::kIOVersion = 6;

plStateDataRecord::plStateDataRecord() : fDescriptor(NULL), fFlags(0) { }

plStateDataRecord::~plStateDataRecord() {
    for (size_t i=0; i<fVarsList.getSize(); i++)
        delete fVarsList[i];
    for (size_t i=0; i<fSDVarsList.getSize(); i++)
        delete fSDVarsList[i];
}

void plStateDataRecord::ReadStreamHeader(hsStream* S, plString& name,
                                         int& version, plUoid* objUoid) {
    unsigned int flag = S->readShort();
    if (!(flag & 0x8000)) {
        name = "";
        return;
    }
    name = S->readSafeStr();
    version = S->readShort();

    if (flag & kVolatile) {
        if (objUoid == NULL) {
            plUoid tmp;
            tmp.read(S);
        } else {
            objUoid->read(S);
        }
    }
}

void plStateDataRecord::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readShort();
    if (S->readByte() != kIOVersion || fDescriptor == NULL)
        throw hsBadParamException(__FILE__, __LINE__);

    size_t num = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
    bool all = (num == fVarsList.getSize());
    for (size_t i=0; i<num; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
        else
            idx = i;

        if (idx < fVarsList.getSize())
            fVarsList[i]->read(S, mgr);
    }
    
    num = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
    all = (num == fSDVarsList.getSize());
    for (size_t i=0; i<num; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
        else
            idx = i;

        if (idx < fSDVarsList.getSize())
            fSDVarsList[i]->read(S, mgr);
    }
}

void plStateDataRecord::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fFlags);
    S->writeByte(kIOVersion);

    throw hsNotImplementedException(__FILE__, __LINE__, "Incomplete");
}

void plStateDataRecord::setDescriptor(plStateDescriptor* desc) {
    fDescriptor = desc;

    for (size_t i=0; i<fVarsList.getSize(); i++)
        delete fVarsList[i];
    for (size_t i=0; i<fSDVarsList.getSize(); i++)
        delete fSDVarsList[i];
    fVarsList.clear();
    fSDVarsList.clear();

    for (size_t i=0; i<fDescriptor->getNumVars(); i++) {
        plVarDescriptor* varDesc = fDescriptor->get(i);
        plStateVariable* var;
        if (varDesc->getType() == plVarDescriptor::kStateDescriptor) {
            var = new plSDStateVariable();
            fSDVarsList.append(var);
        } else {
            var = new plSimpleStateVariable();
            fVarsList.append(var);
        }
        var->setDescriptor(varDesc);
        fAllVars.append(var);
    }
}

plStateVariable* plStateDataRecord::get(size_t idx) const {
    return fAllVars[idx];
}

plStateVariable* plStateDataRecord::get(plString& name) const {
    for (size_t i=0; i<fAllVars.getSize(); i++)
        if (fAllVars[i]->getDescriptor()->getName() == name)
            return fAllVars[i];
    return NULL;
}

size_t plStateDataRecord::getNumVars() const {
    return fAllVars.getSize();
}
