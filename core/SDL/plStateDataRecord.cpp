#include "plStateDataRecord.h"

const unsigned char plStateDataRecord::kIOVersion = 6;

plStateDataRecord::plStateDataRecord() : fDescriptor(NULL), fFlags(0) { }

plStateDataRecord::~plStateDataRecord() {
    for (size_t i=0; i<fAllVars.getSize(); i++)
        delete fAllVars[i];
}

void plStateDataRecord::ReadStreamHeader(hsStream* S, plString& name,
                                         int& version, plUoid* objUoid) {
    unsigned short flag = S->readShort();
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

void plStateDataRecord::WriteStreamHeader(hsStream* S, plString name,
                                          int version, plUoid* objUoid) {
    unsigned short flag = 0x8000;
    if (objUoid != NULL)
        flag |= kVolatile;
    S->writeShort(flag);
    S->writeSafeStr(name);
    S->writeShort(version);

    if (flag & kVolatile)
        objUoid->write(S);
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
        fVarsList[idx]->read(S, mgr);
        fVarsList[idx]->setDirty();
    }

    num = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
    all = (num == fSDVarsList.getSize());
    for (size_t i=0; i<num; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fDescriptor->getNumVars());
        else
            idx = i;
        fSDVarsList[idx]->read(S, mgr);
        fSDVarsList[idx]->setDirty();
    }
}

void plStateDataRecord::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fFlags);
    S->writeByte(kIOVersion);

    size_t numDirty = 0;
    for (size_t i=0; i<fVarsList.getSize(); i++) {
        if (!fVarsList[i]->isDefault())
            fVarsList[i]->setDirty();
        if (fVarsList[i]->isDirty())
            numDirty++;
    }
    plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), numDirty);
    bool all = (numDirty == fVarsList.getSize());
    for (size_t i=0; i<fVarsList.getSize(); i++) {
        if (fVarsList[i]->isDirty()) {
            if (!all)
                plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), i);
            fVarsList[i]->write(S, mgr);
        }
    }

    numDirty = 0;
    for (size_t i=0; i<fSDVarsList.getSize(); i++) {
        if (!fSDVarsList[i]->isDefault())
            fSDVarsList[i]->setDirty();
        if (fSDVarsList[i]->isDirty())
            numDirty++;
    }
    plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), numDirty);
    all = (numDirty == fSDVarsList.getSize());
    for (size_t i=0; i<fSDVarsList.getSize(); i++) {
        if (fSDVarsList[i]->isDirty()) {
            if (!all)
                plSDL::VariableLengthWrite(S, fDescriptor->getNumVars(), i);
            fSDVarsList[i]->write(S, mgr);
        }
    }
}

void plStateDataRecord::prcWrite(pfPrcHelper* prc) {
    for (size_t i=0; i<fAllVars.getSize(); i++) {
        prc->startTag("Variable");
        prc->writeParam("Name", fAllVars[i]->getDescriptor()->getName());
        prc->endTag();
        
        for (size_t j=0; j<fAllVars[i]->getCount(); j++) {
            switch (fAllVars[i]->getDescriptor()->getType()) {
            case plVarDescriptor::kNone:
                prc->startTag("None");
                prc->endTag(true);
                break;
            case plVarDescriptor::kInt:
                prc->startTag("Int");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Int(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kFloat:
                prc->startTag("Float");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Float(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kBool:
                prc->startTag("Boolean");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Bool(j) ? "true" : "false");
                prc->endTag(true);
                break;
            case plVarDescriptor::kString:
                prc->startTag("String");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->String(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kKey:
                prc->startTag("Key");
                prc->endTag();
                ((plSimpleStateVariable*)fAllVars[i])->Uoid(j).prcWrite(prc);
                prc->closeTag();
                break;
            case plVarDescriptor::kDouble:
                prc->startTag("Double");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Double(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kByte:
                prc->startTag("Byte");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Byte(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kShort:
                prc->startTag("Short");
                prc->writeParam("Value", ((plSimpleStateVariable*)fAllVars[i])->Short(j));
                prc->endTag(true);
                break;
            case plVarDescriptor::kRGB:
            case plVarDescriptor::kRGBA:
                prc->startTag("Color");
                prc->endTag();
                ((plSimpleStateVariable*)fAllVars[i])->ColorRGBA(j).prcWrite(prc);
                prc->closeTag();
                break;
            case plVarDescriptor::kRGB8:
            case plVarDescriptor::kRGBA8:
                prc->startTag("Color32");
                prc->endTag();
                ((plSimpleStateVariable*)fAllVars[i])->Color32(j).prcWrite(prc);
                prc->closeTag();
                break;
            case plVarDescriptor::kAgeTimeOfDay:
                prc->startTag("AgeTimeOfDay");
                if (!((plSimpleStateVariable*)fAllVars[i])->getTimeStamp().atEpoch()) {
                    prc->endTag();
                    ((plUnifiedTime)((plSimpleStateVariable*)fAllVars[i])->getTimeStamp()).prcWrite(prc);
                    prc->closeTag();
                } else {
                    prc->endTag(true);
                }
                break;
            case plVarDescriptor::kStateDescriptor:
                prc->startTag("SDLRecord");
                prc->writeParam("Value", fAllVars[i]->getDescriptor()->getStateDescType());
                prc->endTag(true);
                break;
            default:
                prc->startTag("Incomplete");
                prc->writeParam("TypeID", fAllVars[i]->getDescriptor()->getType());
            }
        }
        
        prc->closeTag();
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
        plStateVariable* var;
        if (varDesc->getType() == plVarDescriptor::kStateDescriptor) {
            var = new plSDStateVariable();
            ((plSDStateVariable*)var)->setSDVarDescriptor(varDesc->getStateDesc());
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
