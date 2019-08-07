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

#include "plStateVariable.h"
#include "plStateDataRecord.h"
#include "ResManager/plFactory.h"
#include "Util/hsBitVector.h"
#include <cstring>

/* plStateVarNotificationInfo */
void plStateVarNotificationInfo::read(hsStream* S)
{
    S->readByte();
    fHintString = S->readSafeStr();
}

void plStateVarNotificationInfo::write(hsStream* S)
{
    S->writeByte(0);
    S->writeSafeStr(fHintString);
}


/* plStateVariable */
void plStateVariable::read(hsStream* S, plResManager* mgr)
{
    fContents = S->readByte();
    if (fContents & plSDL::kHasNotificationInfo)
        fNotificationInfo.read(S);
}

void plStateVariable::write(hsStream* S, plResManager* mgr)
{
    S->writeByte(fContents);
    if (fContents & plSDL::kHasNotificationInfo)
        fNotificationInfo.write(S);
}


/* plSDStateVariable */
plSDStateVariable::~plSDStateVariable()
{
    for (auto rec = fDataRecList.begin(); rec != fDataRecList.end(); ++rec)
        delete *rec;
}

void plSDStateVariable::setDescriptor(plVarDescriptor* desc)
{
    fDescriptor = desc;
    resize(fDescriptor->getCount());
}

void plSDStateVariable::resize(size_t size)
{
    for (auto rec = fDataRecList.begin(); rec != fDataRecList.end(); ++rec)
        delete *rec;
    fCount = size;
    fDataRecList.resize(size);
    for (size_t i=0; i<fDataRecList.size(); i++) {
        fDataRecList[i] = new plStateDataRecord();
        fDataRecList[i]->setDescriptor(fSDVarDescriptor);
    }
}

void plSDStateVariable::read(hsStream* S, plResManager* mgr)
{
    plStateVariable::read(S, mgr);

    S->readByte();
    if (fDescriptor->isVariableLength())
        resize(S->readInt());

    unsigned int count = plSDL::VariableLengthRead(S, fCount);
    bool all = (count == fCount);
    for (size_t i=0; i<count; i++) {
        size_t idx;
        if (!all)
            idx = plSDL::VariableLengthRead(S, fCount);
        else
            idx = i;

        if (idx < fDataRecList.size())
            fDataRecList[idx]->read(S, mgr);
    }
}

void plSDStateVariable::write(hsStream* S, plResManager* mgr)
{
    plStateVariable::write(S, mgr);

    S->writeByte(0);
    if (fDescriptor->isVariableLength())
        S->writeInt(fCount);

    size_t numDirty = 0;
    hsBitVector dirty;
    for (size_t i=0; i<fCount; i++) {
        dirty[i] = false;
        for (size_t j=0; j<fDataRecList[i]->getNumVars(); j++) {
            if (fDataRecList[i]->get(j)->isDirty())
                dirty[i] = true;
        }
        if (dirty[i])
            numDirty++;
    }
    plSDL::VariableLengthWrite(S, fCount, numDirty);
    bool all = (numDirty == fCount);
    for (size_t i=0; i<fCount; i++) {
        if (dirty[i]) {
            if (!all)
                plSDL::VariableLengthWrite(S, fCount, i);
            fDataRecList[i]->write(S, mgr);
        }
    }
}

void plSDStateVariable::SetFromDefault()
{
    for (size_t i=0; i<fCount; i++) {
        for (size_t j=0; j<fDataRecList[i]->getNumVars(); j++)
            fDataRecList[i]->get(j)->SetFromDefault();
    }
    setDirty(false);
}

bool plSDStateVariable::isDefault(bool secondChance) const
{
    if (fCount != fDataRecList.size())
        return false;
    for (size_t i=0; i<fCount; i++) {
        for (size_t j=0; j<fDataRecList[i]->getNumVars(); j++) {
            if (!fDataRecList[i]->get(j)->isDefault(secondChance))
                return false;
        }
    }
    return true;
}


/* plSimpleStateVariable */
void plSimpleStateVariable::IDeAlloc()
{
    if (fGenPtr == nullptr)
        return;

    switch (fDescriptor->getType()) {
    case plVarDescriptor::kInt:
        delete[] fInt;
        break;
    case plVarDescriptor::kUint:
        delete[] fUint;
        break;
    case plVarDescriptor::kFloat:
        delete[] fFloat;
        break;
    case plVarDescriptor::kBool:
        delete[] fBool;
        break;
    case plVarDescriptor::kString:
        delete[] fString;
        break;
    case plVarDescriptor::kKey:
        delete[] fUoid;
        break;
    case plVarDescriptor::kCreatable:
        for (size_t i=0; i<fDescriptor->getCount(); i++)
            delete fCreatable[i];
        delete[] fCreatable;
        break;
    case plVarDescriptor::kDouble:
        delete[] fDouble;
        break;
    case plVarDescriptor::kTime:
        delete[] fTime;
        break;
    case plVarDescriptor::kByte:
        delete[] fByte;
        break;
    case plVarDescriptor::kChar:
        delete[] fChar;
        break;
    case plVarDescriptor::kShort:
        delete[] fShort;
        break;
    case plVarDescriptor::kAgeTimeOfDay:
        break;
    case plVarDescriptor::kVector3:
    case plVarDescriptor::kPoint3:
        delete[] fVector;
        break;
    case plVarDescriptor::kRGB:
        delete[] fColorRGBA;
        break;
    case plVarDescriptor::kRGBA:
        delete[] fColorRGBA;
        break;
    case plVarDescriptor::kQuaternion:
        delete[] fQuat;
        break;
    case plVarDescriptor::kRGB8:
        delete[] fColor32;
        break;
    case plVarDescriptor::kRGBA8:
        delete[] fColor32;
        break;
    case plVarDescriptor::kMatrix44:
        delete[] fMatrix;
        break;
    default:
        break;
    }
}

void plSimpleStateVariable::setDescriptor(plVarDescriptor* desc)
{
    fDescriptor = desc;
    resize(fDescriptor->getCount());
}

void plSimpleStateVariable::resize(size_t size)
{
    IDeAlloc();
    fCount = size;
    if (fDescriptor == nullptr || fCount == 0) {
        fGenPtr = nullptr;
        return;
    }

    switch (fDescriptor->getType()) {
    case plVarDescriptor::kInt:
        fInt = new int[fCount];
        break;
    case plVarDescriptor::kUint:
        fUint = new unsigned int[fCount];
        break;
    case plVarDescriptor::kFloat:
        fFloat = new float[fCount];
        break;
    case plVarDescriptor::kBool:
        fBool = new bool[fCount];
        break;
    case plVarDescriptor::kString:
        fString = new ST::string[fCount];
        break;
    case plVarDescriptor::kKey:
        fUoid = new plUoid[fCount];
        break;
    case plVarDescriptor::kCreatable:
        fCreatable = new plCreatable*[fCount];
        for (size_t i=0; i<fCount; i++)
            fCreatable[i] = nullptr;
        break;
    case plVarDescriptor::kDouble:
        fDouble = new double[fCount];
        break;
    case plVarDescriptor::kTime:
        fTime = new plUnifiedTime[fCount];
        break;
    case plVarDescriptor::kByte:
        fByte = new unsigned char[fCount];
        break;
    case plVarDescriptor::kChar:
        fChar = new signed char[fCount];
        break;
    case plVarDescriptor::kShort:
        fShort = new short[fCount];
        break;
    case plVarDescriptor::kAgeTimeOfDay:
        break;
    case plVarDescriptor::kVector3:
    case plVarDescriptor::kPoint3:
        fVector = new hsVector3[fCount];
        break;
    case plVarDescriptor::kRGB:
        fColorRGBA = new hsColorRGBA[fCount];
        break;
    case plVarDescriptor::kRGBA:
        fColorRGBA = new hsColorRGBA[fCount];
        break;
    case plVarDescriptor::kQuaternion:
        fQuat = new hsQuat[fCount];
        break;
    case plVarDescriptor::kRGB8:
        fColor32 = new hsColor32[fCount];
        break;
    case plVarDescriptor::kRGBA8:
        fColor32 = new hsColor32[fCount];
        break;
    case plVarDescriptor::kMatrix44:
        fMatrix = new hsMatrix44[fCount];
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plSimpleStateVariable::read(hsStream* S, plResManager* mgr)
{
    plStateVariable::read(S, mgr);

    fSimpleVarContents = S->readByte();
    if (fSimpleVarContents & plSDL::kHasTimeStamp)
        fTimeStamp.read(S);

    if (!(fSimpleVarContents & plSDL::kSameAsDefault)) {
        if (fDescriptor->isVariableLength()) {
            size_t count = S->readInt();
            if (count > 9999)
                throw hsBadParamException(__FILE__, __LINE__);
            resize(count);
        }

        for (size_t i=0; i<fCount; i++)
            IReadData(S, mgr, i);
    } else {
        SetFromDefault();
    }
}

void plSimpleStateVariable::write(hsStream* S, plResManager* mgr)
{
    plStateVariable::write(S, mgr);

    if (isDefault(true))
        fSimpleVarContents |= plSDL::kSameAsDefault;
    else {
        fSimpleVarContents &= ~plSDL::kSameAsDefault;
        setDirty(true);
    }

    if (fIsDirty)
      fSimpleVarContents |= plSDL::kHasDirtyFlag;

    S->writeByte(fSimpleVarContents);
    if (fSimpleVarContents & plSDL::kHasTimeStamp)
        fTimeStamp.write(S);

    if (!(fSimpleVarContents & plSDL::kSameAsDefault)) {
        if (fDescriptor->isVariableLength())
            S->writeInt(fCount);

        for (size_t i=0; i<fCount; i++)
            IWriteData(S, mgr, i);
    }
}

void plSimpleStateVariable::IReadData(hsStream* S, plResManager* mgr, size_t idx)
{
    switch (fDescriptor->getType()) {
    case plVarDescriptor::kInt:
        fInt[idx] = S->readInt();
        break;
    case plVarDescriptor::kUint:
        fUint[idx] = S->readInt();
        break;
    case plVarDescriptor::kFloat:
        fFloat[idx] = S->readFloat();
        break;
    case plVarDescriptor::kBool:
        fBool[idx] = S->readBool();
        break;
    case plVarDescriptor::kString:
        {
            char buf[33];
            S->read(32, buf);
            buf[32] = 0;
            fString[idx] = buf;
        }
        break;
    case plVarDescriptor::kKey:
        fUoid[idx].read(S);
        break;
    case plVarDescriptor::kCreatable:
        {
            unsigned short hClass = S->readShort();
            if (hClass != 0x8000) {
                unsigned int len = S->readInt();
                fCreatable[idx] = plFactory::Create(hClass);
                if (fCreatable[idx] == nullptr)
                    fCreatable[idx] = new plCreatableStub(hClass, len);
                fCreatable[idx]->read(S, mgr);
            } else {
                fCreatable[idx] = nullptr;
            }
        }
        break;
    case plVarDescriptor::kDouble:
        fDouble[idx] = S->readDouble();
        break;
    case plVarDescriptor::kTime:
        fTime[idx].read(S);
        break;
    case plVarDescriptor::kByte:
        fByte[idx] = S->readByte();
        break;
    case plVarDescriptor::kChar:
        fChar[idx] = S->readByte();
        break;
    case plVarDescriptor::kShort:
        fShort[idx] = S->readShort();
        break;
    case plVarDescriptor::kAgeTimeOfDay:
        break;
    case plVarDescriptor::kVector3:
    case plVarDescriptor::kPoint3:
        fVector[idx].read(S);
        break;
    case plVarDescriptor::kRGB:
        fColorRGBA[idx].readRGB(S);
        break;
    case plVarDescriptor::kRGBA:
        fColorRGBA[idx].read(S);
        break;
    case plVarDescriptor::kQuaternion:
        fQuat[idx].read(S);
        break;
    case plVarDescriptor::kRGB8:
        fColor32[idx].readRGB8(S);
        break;
    case plVarDescriptor::kRGBA8:
        fColor32[idx].readRGBA8(S);
        break;
    case plVarDescriptor::kMatrix44:
        fMatrix[idx].read(S);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plSimpleStateVariable::IWriteData(hsStream* S, plResManager* mgr, size_t idx)
{
    switch (fDescriptor->getType()) {
    case plVarDescriptor::kInt:
        S->writeInt(fInt[idx]);
        break;
    case plVarDescriptor::kUint:
        S->writeInt(fUint[idx]);
        break;
    case plVarDescriptor::kFloat:
        S->writeFloat(fFloat[idx]);
        break;
    case plVarDescriptor::kBool:
        S->writeBool(fBool[idx]);
        break;
    case plVarDescriptor::kString:
        {
            char buf[32];
            strncpy(buf, fString[idx].c_str(), 32);
            buf[31] = 0;
            S->write(32, buf);
        }
        break;
    case plVarDescriptor::kKey:
        fUoid[idx].write(S);
        break;
    case plVarDescriptor::kCreatable:
        {
            if (fCreatable[idx] == nullptr) {
                S->writeShort(0x8000);
            } else {
                S->writeShort(fCreatable[idx]->ClassIndex());
                S->writeInt(0);
                unsigned long len = S->pos();
                fCreatable[idx]->write(S, mgr);
                unsigned long end = S->pos();
                S->seek(len - 4);
                S->writeInt(end - len);
                S->seek(end);
            }
        }
        break;
    case plVarDescriptor::kDouble:
        S->writeDouble(fDouble[idx]);
        break;
    case plVarDescriptor::kTime:
        fTime[idx].write(S);
        break;
    case plVarDescriptor::kByte:
        S->writeByte(fByte[idx]);
        break;
    case plVarDescriptor::kChar:
        S->writeByte(fChar[idx]);
        break;
    case plVarDescriptor::kShort:
        S->writeShort(fShort[idx]);
        break;
    case plVarDescriptor::kAgeTimeOfDay:
        break;
    case plVarDescriptor::kVector3:
    case plVarDescriptor::kPoint3:
        fVector[idx].write(S);
        break;
    case plVarDescriptor::kRGB:
        fColorRGBA[idx].writeRGB(S);
        break;
    case plVarDescriptor::kRGBA:
        fColorRGBA[idx].write(S);
        break;
    case plVarDescriptor::kQuaternion:
        fQuat[idx].write(S);
        break;
    case plVarDescriptor::kRGB8:
        fColor32[idx].writeRGB8(S);
        break;
    case plVarDescriptor::kRGBA8:
        fColor32[idx].writeRGBA8(S);
        break;
    case plVarDescriptor::kMatrix44:
        fMatrix[idx].write(S);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plSimpleStateVariable::SetFromDefault()
{
    if (fDescriptor == nullptr)
        throw hsBadParamException(__FILE__, __LINE__);
    ST::string def = fDescriptor->getDefault().to_lower();

    for (size_t i=0; i<fDescriptor->getCount(); i++) {
        switch (fDescriptor->getType()) {
        case plVarDescriptor::kInt:
            if (def.empty())
                fInt[i] = 0;
            else
                fInt[i] = def.to_int();
            break;
        case plVarDescriptor::kUint:
            if (def.empty())
                fUint[i] = 0;
            else
                fUint[i] = def.to_uint();
            break;
        case plVarDescriptor::kFloat:
            if (def.empty())
                fFloat[i] = 0.0f;
            else
                fFloat[i] = def.to_float();
            break;
        case plVarDescriptor::kBool:
            if (def.empty())
                fBool[i] = false;
            else
                fBool[i] = def.to_bool();
            break;
        case plVarDescriptor::kString:
            fString[i] = def;
            break;
        case plVarDescriptor::kKey:
            fUoid[i] = plUoid();
            break;
        case plVarDescriptor::kCreatable:
            fCreatable[i] = nullptr;
            break;
        case plVarDescriptor::kDouble:
            if (def.empty())
                fDouble[i] = 0.0;
            else
                fDouble[i] = def.to_double();
            break;
        case plVarDescriptor::kTime:
            fTime[i].toCurrentTime();
            break;
        case plVarDescriptor::kByte:
            if (def.empty())
                fByte[i] = 0;
            else
                fByte[i] = def.to_uint();
            break;
        case plVarDescriptor::kChar:
            if (def.empty())
                fChar[i] = 0;
            else
                fChar[i] = def.to_uint();
            break;
        case plVarDescriptor::kShort:
            if (def.empty())
                fShort[i] = 0;
            else
                fShort[i] = def.to_int();
            break;
        case plVarDescriptor::kAgeTimeOfDay:
            break;
        case plVarDescriptor::kVector3:
        case plVarDescriptor::kPoint3:
            if (def.empty()) {
                fVector[i] = hsVector3(0.0f, 0.0f, 0.0f);
            } else {
                ST::string parse = def;
                parse = parse.after_first('(');
                fVector[i].X = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                fVector[i].Y = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                fVector[i].Z = parse.before_first(')').to_float();
            }
            break;
        case plVarDescriptor::kRGB:
            throw hsNotImplementedException(__FILE__, __LINE__, def);
            break;
        case plVarDescriptor::kRGBA:
            throw hsNotImplementedException(__FILE__, __LINE__, def);
            break;
        case plVarDescriptor::kQuaternion:
            if (def.empty()) {
                fQuat[i] = hsQuat(0.0f, 0.0f, 0.0f, 0.0f);
            } else {
                ST::string parse = def;
                parse = parse.after_first('(');
                fQuat[i].X = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                fQuat[i].Y = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                fQuat[i].Z = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                fQuat[i].W = parse.before_first(')').to_float();
            }
            break;
        case plVarDescriptor::kRGB8:
            if (def.empty()) {
                fColor32[i] = hsColor32(0xFF000000);
            } else {
                ST::string parse = def;
                parse = parse.after_first('(');
                fColor32[i].r = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                fColor32[i].g = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                fColor32[i].b = (unsigned char)(parse.before_first(')').to_float() * 255);
            }
            break;
        case plVarDescriptor::kRGBA8:
            if (def.empty()) {
                fColor32[i] = hsColor32(0xFF000000);
            } else {
                ST::string parse = def;
                parse = parse.after_first('(');
                fColor32[i].r = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                fColor32[i].g = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                fColor32[i].b = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                fColor32[i].a = (unsigned char)(parse.before_first(')').to_float() * 255);
            }
            break;
        case plVarDescriptor::kMatrix44:
            throw hsNotImplementedException(__FILE__, __LINE__, def);
            break;
        default:
            throw hsBadParamException(__FILE__, __LINE__);
        }
    }
    setDirty(false);
}

bool plSimpleStateVariable::isDefault(bool secondChance) const
{
    if (fDescriptor == nullptr)
        throw hsBadParamException(__FILE__, __LINE__);
    ST::string def = fDescriptor->getDefault().to_lower();

    if (fDescriptor->getCount() != fCount)
        return false;

    for (size_t i=0; i<fDescriptor->getCount(); i++) {
        switch (fDescriptor->getType()) {
        case plVarDescriptor::kInt:
            if (def.empty()) {
                if (fInt[i] != 0)
                    return false;
            } else {
                if (fInt[i] != def.to_int())
                    return false;
            }
            break;
        case plVarDescriptor::kUint:
            if (def.empty()) {
                if (fUint[i] != 0)
                    return false;
            } else {
                if (fUint[i] != def.to_uint())
                    return false;
            }
            break;
        case plVarDescriptor::kFloat:
            if (def.empty()) {
                if (fFloat[i] != 0.0f)
                    return false;
            } else {
                if (fFloat[i] != def.to_float())
                    return false;
            }
            break;
        case plVarDescriptor::kBool:
            if (def.empty() || def == "false") {
                if (fBool[i] != false)
                    return false;
            } else if (def == "true") {
                if (fBool[i] != true)
                    return false;
            } else {
                if (fBool[i] != (def.to_int() != 0))
                    return false;
            }
            break;
        case plVarDescriptor::kString:
            if (fString[i] != def)
                return false;
            break;
        case plVarDescriptor::kKey:
            if (secondChance && fUoid[i] != plUoid())
                return false;
            break;
        case plVarDescriptor::kCreatable:
            if (fCreatable[i])
                return false;
            break;
        case plVarDescriptor::kDouble:
            if (def.empty()) {
                if (fDouble[i] != 0.0)
                    return false;
            } else {
                if (fDouble[i] != def.to_float())
                    return false;
            }
            break;
        case plVarDescriptor::kTime:
            return false;
            break;
        case plVarDescriptor::kByte:
            if (def.empty()) {
                if (fByte[i] != 0)
                    return false;
            } else {
                if (fByte[i] != def.to_uint())
                    return false;
            }
            break;
        case plVarDescriptor::kChar:
            if (def.empty()) {
                if (fChar[i] != 0)
                    return false;
            } else {
                if (fChar[i] != (char)def.to_uint())
                    return false;
            }
            break;
        case plVarDescriptor::kShort:
            if (def.empty()) {
                if (fShort[i] != 0)
                    return false;
            } else {
                if (fShort[i] != def.to_int())
                    return false;
            }
            break;
        case plVarDescriptor::kAgeTimeOfDay:
            return fTimeStamp.atEpoch();
            break;
        case plVarDescriptor::kVector3:
        case plVarDescriptor::kPoint3:
            if (def.empty()) {
                if (fVector[i] == hsVector3(0.0f, 0.0f, 0.0f))
                    return false;
            } else {
                ST::string parse = def;
                hsVector3 vec;
                parse = parse.after_first('(');
                vec.X = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                vec.Y = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                vec.Z = parse.before_first(')').to_float();
                if (fVector[i] != vec)
                    return false;
            }
            break;
        case plVarDescriptor::kRGB:
            throw hsNotImplementedException(__FILE__, __LINE__);
            break;
        case plVarDescriptor::kRGBA:
            throw hsNotImplementedException(__FILE__, __LINE__);
            break;
        case plVarDescriptor::kQuaternion:
            if (def.empty()) {
                if (fQuat[i] != hsQuat(0.0f, 0.0f, 0.0f, 0.0f))
                    return false;
            } else {
                ST::string parse = def;
                hsQuat quat;
                parse = parse.after_first('(');
                quat.X = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                quat.Y = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                quat.Z = parse.before_first(',').to_float();
                parse = parse.after_first(',');
                quat.W = parse.before_first(')').to_float();
                if (fQuat[i] != quat)
                    return false;
            }
            break;
        case plVarDescriptor::kRGB8:
            if (def.empty()) {
                if (fColor32[i] != hsColor32(0xFF000000))
                    return false;
            } else {
                ST::string parse = def;
                hsColor32 color;
                parse = parse.after_first('(');
                color.r = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                color.g = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                color.b = (unsigned char)(parse.before_first(')').to_float() * 255);
                if (fColor32[i] != color)
                    return false;
            }
            break;
        case plVarDescriptor::kRGBA8:
            if (def.empty()) {
                if (fColor32[i] != hsColor32(0xFF000000))
                    return false;
            } else {
                ST::string parse = def;
                hsColor32 color;
                parse = parse.after_first('(');
                color.r = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                color.g = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                color.b = (unsigned char)(parse.before_first(',').to_float() * 255);
                parse = parse.after_first(',');
                color.a = (unsigned char)(parse.before_first(')').to_float() * 255);
                if (fColor32[i] != color)
                    return false;
            }
            break;
        case plVarDescriptor::kMatrix44:
            throw hsNotImplementedException(__FILE__, __LINE__);
            break;
        default:
            throw hsBadParamException(__FILE__, __LINE__);
        }
    }
    return true;
}
