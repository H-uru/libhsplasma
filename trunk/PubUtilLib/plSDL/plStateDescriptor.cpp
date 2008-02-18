#include "plStateDescriptor.h"

/* plVarDescriptor */
plVarDescriptor::plVarDescriptor()
               : fCount(0), fType(kNone), fFlags(0) { }

plVarDescriptor::~plVarDescriptor() { }

const plString& plVarDescriptor::getName() const { return fName; }
const plString& plVarDescriptor::getDefault() const { return fDefault; }
size_t plVarDescriptor::getCount() const { return fCount; }
plVarDescriptor::Type plVarDescriptor::getType() const { return fType; }
const plString& plVarDescriptor::getStateDescType() const { return fStateDescType; }

bool plVarDescriptor::isInternal() const { return fFlags & kInternal; }
bool plVarDescriptor::isAlwaysNew() const { return fFlags & kAlwaysNew; }
bool plVarDescriptor::isVariableLength() const { return fFlags & kVariableLength; }
bool plVarDescriptor::isValid() const { return fType != kNone; }

void plVarDescriptor::setName(const plString& name) { fName = name; }
void plVarDescriptor::setDefault(const plString& def) { fDefault = def; }
void plVarDescriptor::setCount(size_t count) { fCount = count; }
void plVarDescriptor::setType(plVarDescriptor::Type type) { fType = type; }
void plVarDescriptor::setStateDescType(const plString& type) { fStateDescType = type; }

void plVarDescriptor::setInternal(bool internal) {
    if (internal)
        fFlags |= kInternal;
    else
        fFlags &= ~kInternal;
}

void plVarDescriptor::setAlwaysNew(bool alwaysNew) {
    if (alwaysNew)
        fFlags |= kAlwaysNew;
    else
        fFlags &= ~kAlwaysNew;
}

void plVarDescriptor::setVariableLength(bool varLength) {
    if (varLength)
        fFlags |= kVariableLength;
    else
        fFlags &= ~kVariableLength;
}

plVarDescriptor::Type plVarDescriptor::GetTypeFromString(const plString& type, bool isEoa) {
    plString itype = type;
    itype.toLower();
    if (isEoa) {
        // These translate differently in Myst5...
        if (itype == "bool")
            return kBool;
        else if (itype == "char")
            return kChar;
        else if (itype == "byte")
            return kByte;
        else if (itype == "int")
            return kInt;
        else if (itype == "uint")
            return kUint;
        else if (itype == "float")
            return kFloat;
        else if (itype == "double")
            return kDouble;
        else if (itype == "string")
            return kString;
        else if (itype == "time")
            return kTime;
        else if (itype == "uoid")
            return kKey;
        else if (itype == "vector3")
            return kVector3;
        else if (itype == "point3")
            return kPoint3;
        else if (itype == "quaternion")
            return kQuaternion;
        else if (itype == "matrix44")
            return kMatrix44;
        else if (itype == "rgba")
            return kRGBA;
        else if (itype == "buffer")
            return kBuffer;
        else if (itype == "agetimeofday")
            return kAgeTimeOfDay;
        else if (itype == "agetimeelapsed")
            return kAgeTimeElapsed;
        else if (itype == "gametimeelapsed")
            return kGameTimeElapsed;
        else
            return kStateDescriptor; 
    } else {
        if (type.startsWith("$"))
            return kStateDescriptor;
        else if (itype == "int")
            return kInt;
        else if (itype == "float")
            return kFloat;
        else if (itype == "bool")
            return kBool;
        else if (itype == "string32")
            return kString;
        else if (itype == "plkey")
            return kKey;
        else if (itype == "creatable")
            return kCreatable;
        else if (itype == "double")
            return kDouble;
        else if (itype == "time")
            return kTime;
        else if (itype == "byte")
            return kByte;
        else if (itype == "short")
            return kShort;
        else if (itype == "agetimeofday")
            return kAgeTimeOfDay;
        else if (itype == "vector3")
            return kVector3;
        else if (itype == "point3")
            return kPoint3;
        else if (itype == "rgb")
            return kRGB;
        else if (itype == "rgba")
            return kRGBA;
        else if (itype == "quat")
            return kQuaternion;
        else if (itype == "rgb8")
            return kRGB8;
        else if (itype == "rgba8")
            return kRGBA8;
        else
            return kNone;
    }
}


/* plStateDescriptor */
plStateDescriptor::plStateDescriptor() : fVersion(-1) { }

plStateDescriptor::~plStateDescriptor() {
    for (size_t i=0; i<fVariables.getSize(); i++)
        delete fVariables[i];
}

const plString& plStateDescriptor::getName() const { return fName; }
int plStateDescriptor::getVersion() const { return fVersion; }
bool plStateDescriptor::isValid() const { return fVersion != -1; }

void plStateDescriptor::setName(const plString& name) { fName = name; }
void plStateDescriptor::setVersion(int ver) { fVersion = ver; }

plVarDescriptor* plStateDescriptor::get(size_t idx) {
    return fVariables[idx];
}

plVarDescriptor* plStateDescriptor::get(const plString& name) {
    for (size_t i=0; i<fVariables.getSize(); i++)
        if (fVariables[i]->getName() == name)
            return fVariables[i];
    return NULL;
}

void plStateDescriptor::set(size_t idx, plVarDescriptor* var) {
    fVariables[idx] = var;
}

void plStateDescriptor::set(const plString& name, plVarDescriptor* var) {
    size_t idx = (size_t)-1;
    for (size_t i=0; i<fVariables.getSize(); i++)
        if (fVariables[i]->getName() == name)
            idx = i;
    if (idx == (size_t)-1) {
        fVariables.append(new plVarDescriptor());
        idx = fVariables.getSize() - 1;
    }
    fVariables[idx] = var;
}

size_t plStateDescriptor::getNumVars() const {
    return fVariables.getSize();
}

void plStateDescriptor::addVariable(plVarDescriptor* var) {
    fVariables.append(var);
}

void plStateDescriptor::delVariable(size_t idx) {
    fVariables.remove(idx);
}

void plStateDescriptor::delVariable(const plString& name) {
    for (size_t i=0; i<fVariables.getSize(); i++) {
        if (fVariables[i]->getName() == name) {
            fVariables.remove(i);
            return;
        }
    }
}
