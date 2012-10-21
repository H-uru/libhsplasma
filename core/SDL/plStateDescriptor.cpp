/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plStateDescriptor.h"

/* plVarDescriptor */
void plVarDescriptor::read(hsStream* S) {
    if (S->readByte() != 3)
        throw hsBadParamException(__FILE__, __LINE__, "Bad plVarDescriptor IO Version");

    fName = S->readSafeStr();
    size_t len = S->readShort();
    fDisplay = S->readStr(len);
    fCount = S->readInt();
    fType = (plVarDescriptor::Type)S->readByte();
    fDefault = S->readSafeStr();
    fFlags = S->readInt();

    if (fType == kStateDescriptor) {
        fStateDescType = S->readSafeStr();
        fStateDescVer = S->readShort();
    } else {
        S->readShort();     // Atomic count
        S->readByte();      // Atomic type
    }
}

void plVarDescriptor::write(hsStream* S) {
    S->writeByte(3);
    S->writeSafeStr(fName);
    S->writeShort(fDisplay.len());
    S->writeStr(fDisplay);
    S->writeInt(fCount);
    S->writeByte(fType);
    S->writeSafeStr(fDefault);
    S->writeInt(fFlags);

    if (fType == kStateDescriptor) {
        S->writeSafeStr(fStateDescType);
        S->writeShort(fStateDescVer);
    } else {
        S->writeShort(fCount);
        S->writeByte(fType);
    }
}

void plVarDescriptor::setStateDesc(plStateDescriptor* desc) {
    fStateDesc = desc;
    fStateDescType = desc->getName();
    fStateDescVer = desc->getVersion();
}

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
    plString itype = type.toLower();
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
        else if (itype == "creatable" || itype == "message")
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
        else if (itype == "quat" || itype == "quaternion")
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
plStateDescriptor::~plStateDescriptor() {
    for (size_t i=0; i<fVariables.getSize(); i++)
        delete fVariables[i];
}

void plStateDescriptor::read(hsStream* S) {
    if (S->readByte() != 1)
        throw hsBadParamException(__FILE__, __LINE__, "Bad plStateDescriptor IO Version");
    fName = S->readSafeStr();
    fVersion = S->readShort();

    clearVariables();
    fVariables.setSize(S->readShort());
    for (size_t i=0; i<fVariables.getSize(); i++) {
        fVariables[i] = new plVarDescriptor();
        S->readBool();  // Redundant - tells us whether this is an SDVar or a SimpleVar
        fVariables[i]->read(S);
    }
}

void plStateDescriptor::write(hsStream* S) {
    S->writeByte(1);
    S->writeSafeStr(fName);
    S->writeShort(fVersion);

    S->writeShort(fVariables.getSize());
    for (size_t i=0; i<fVariables.getSize(); i++) {
        S->writeBool(fVariables[i]->getType() == plVarDescriptor::kStateDescriptor);
        fVariables[i]->write(S);
    }
}

void plStateDescriptor::prcWrite(pfPrcHelper* prc) {
    for (size_t i=0; i<fVariables.getSize(); i++) {
        prc->startTag("Variable");
        prc->writeParam("Name", fVariables[i]->getName());
        prc->endTag(true);
    }
}

plVarDescriptor* plStateDescriptor::get(const plString& name) {
    for (size_t i=0; i<fVariables.getSize(); i++)
        if (fVariables[i]->getName() == name)
            return fVariables[i];
    return NULL;
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

void plStateDescriptor::delVariable(size_t idx) {
    delete fVariables[idx];
    fVariables.remove(idx);
}

void plStateDescriptor::delVariable(const plString& name) {
    for (size_t i=0; i<fVariables.getSize(); i++) {
        if (fVariables[i]->getName() == name) {
            delete fVariables[i];
            fVariables.remove(i);
            return;
        }
    }
}

void plStateDescriptor::clearVariables() {
    for (size_t i=0; i<fVariables.getSize(); i++)
        delete fVariables[i];
    fVariables.setSize(0);
}
