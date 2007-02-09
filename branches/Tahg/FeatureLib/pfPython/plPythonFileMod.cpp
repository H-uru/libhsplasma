#include "plPythonFileMod.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

/* plPythonParameter */
plPythonParameter::plPythonParameter(PlasmaVer pv) : ID(0), valueType(kNone) { }

plPythonParameter::~plPythonParameter() {
    if (valueType == kString || valueType == kAnimationName)
        delete[] strValue;
}

void plPythonParameter::read(hsStream* S) {
    if (valueType == kString || valueType == kAnimationName)
        delete[] strValue;
    ID = S->readInt();
    valueType = S->readInt();
    if (valueType >= kNone) return;

    int size = 0;
    switch (valueType) {
    case kInt:
        intValue = S->readInt();
        return;
    case kBoolean:
        boolValue = (S->readInt() != 0);
        return;
    case kFloat:
        floatValue = S->readFloat();
        return;
    case kString:
    case kAnimationName:
        size = S->readInt();
        if (size == 0) {
            strValue = NULL;
            return;
        }
        strValue = new char[size+1];
        S->read(size, strValue);
        strValue[size] = 0;
        return;
    default:
        objKey = plResManager::inst->readKey(S);
        return;
    }
}

void plPythonParameter::write(hsStream* S) {
    S->writeInt(ID);
    S->writeInt(valueType);
    if (valueType >= kNone) return;

    int lb = 0, size = 0;
    switch (valueType) {
    case kInt:
        S->writeInt(intValue);
        return;
    case kBoolean:
        if (boolValue) lb = 1;
        S->writeInt(lb);
        return;
    case kFloat:
        S->writeFloat(floatValue);
        return;
    case kString:
    case kAnimationName:
        size = strlen(strValue);
        S->writeInt(size);
        S->write(size, strValue);
        return;
    default:
        plResManager::inst->writeKey(S, objKey);
        return;
    }
}


/* plPythonFileMod */
plPythonFileMod::plPythonFileMod(PlasmaVer pv) : pythonFile(NULL) { }

plPythonFileMod::~plPythonFileMod() {
    if (pythonFile != NULL)
        delete[] pythonFile;
    for (int i=0; i<receivers.getSize(); i++)
        receivers[i]->UnRef();
}

short plPythonFileMod::ClassIndex() {
    return (ver == pvEoa ? 0x0088 : 0x00A2);
}

void plPythonFileMod::read(hsStream* S) {
    plMultiModifier::read(S);
    if (pythonFile != NULL)
        delete[] pythonFile;
    pythonFile = S->readSafeStr();

    int i, count = S->readInt();
    receivers.setSize(count);
    for (i=0; i<count; i++)
        receivers[i] = plResManager::inst->readKey(S);

    count = S->readInt();
    parameters.setSize(count);
    for (i=0; i<count; i++)
        parameters[i].read(S);
}

void plPythonFileMod::write(hsStream* S) {
    plMultiModifier::write(S);
    S->writeSafeStr(pythonFile);

    int i;
    S->writeInt(receivers.getSize());
    for (i=0; i<receivers.getSize(); i++)
        plResManager::inst->writeKey(S, receivers[i]);

    S->writeInt(parameters.getSize());
    for (i=0; i<parameters.getSize(); i++)
        parameters[i].write(S);
}
