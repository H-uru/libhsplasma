#include "plStateDataRecord.h"

const unsigned char plStateDataRecord::kIOVersion = 6;

plStateDataRecord::plStateDataRecord() : fDescriptor(NULL), fFlags(0) { }

plStateDataRecord::~plStateDataRecord() {
    for (size_t i=0; i<fAllVars.getSize(); i++)
        delete fAllVars[i];
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

    for (size_t i=0; i<fDescriptor->getNumVars(); i++)
        fAllVars[i]->SetFromDefault();

    size_t num = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
    bool all = (num == fVarsList.getSize());
    for (size_t i=0; i<num; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
        else
            idx = i;
        fVarsList[idx].fVariable->read(S, mgr);
    }

    num = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
    all = (num == fSDVarsList.getSize());
    for (size_t i=0; i<num; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
        else
            idx = i;
        fSDVarsList[idx].fVariable->read(S, mgr);
    }
}

void plStateDataRecord::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fFlags);
    S->writeByte(kIOVersion);

    plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), fVarsList.getSize());
    bool all = (fDescriptor->getNumVars() == fVarsList.getSize());
    for (size_t i=0; i<fVarsList.getSize(); i++) {
        if (!all)
            plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), fVarsList[i].fOffset);
        fVarsList[i].fVariable->write(S, mgr);
    }

    plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), fSDVarsList.getSize());
    all = (fDescriptor->getNumVars() == fSDVarsList.getSize());
    for (size_t i=0; i<fSDVarsList.getSize(); i++) {
        if (!all)
            plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), fSDVarsList[i].fOffset);
        fSDVarsList[i].fVariable->write(S, mgr);
    }
}

void plStateDataRecord::setDescriptor(plStateDescriptor* desc) {
    fDescriptor = desc;

    for (size_t i=0; i<fAllVars.getSize(); i++)
        delete fAllVars[i];
    fVarsList.clear();
    fSDVarsList.clear();
    fAllVars.clear();

    for (size_t i=0; i<fDescriptor->getNumVars(); i++) {
        plVarDescriptor* varDesc = fDescriptor->get(i);
        OffsetVar var;
        var.fOffset = i;
        if (varDesc->getType() == plVarDescriptor::kStateDescriptor) {
            var.fVariable = new plSDStateVariable();
            ((plSDStateVariable*)var.fVariable)->setSDVarDescriptor(varDesc->getStateDesc());
            fSDVarsList.append(var);
        } else {
            var.fVariable = new plSimpleStateVariable();
            fVarsList.append(var);
        }
        var.fVariable->setDescriptor(varDesc);
        fAllVars.append(var.fVariable);
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
