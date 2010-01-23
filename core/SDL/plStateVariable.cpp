#include "plStateVariable.h"
#include "plStateDataRecord.h"
#include "ResManager/plFactory.h"
#include "Util/hsBitVector.h"

/* plStateVarNotificationInfo */
plStateVarNotificationInfo::plStateVarNotificationInfo() { }
plStateVarNotificationInfo::~plStateVarNotificationInfo() { }

void plStateVarNotificationInfo::read(hsStream* S) {
    S->readByte();
    fHintString = S->readSafeStr();
}

void plStateVarNotificationInfo::write(hsStream* S) {
    S->writeByte(0);
    S->writeSafeStr(fHintString);
}


/* plStateVariable */
plStateVariable::plStateVariable()
               : fContents(plSDL::kHasNotificationInfo), fDescriptor(NULL),
                 fCount(1), fIsDirty(false) { }
plStateVariable::~plStateVariable() { }

plVarDescriptor* plStateVariable::getDescriptor() const { return fDescriptor; }
size_t plStateVariable::getCount() const { return fCount; }

void plStateVariable::read(hsStream* S, plResManager* mgr) {
    fContents = S->readByte();
    if (fContents & plSDL::kHasNotificationInfo)
        fNotificationInfo.read(S);
}

void plStateVariable::write(hsStream* S, plResManager* mgr) {
    S->writeByte(fContents);
    if (fContents & plSDL::kHasNotificationInfo)
        fNotificationInfo.write(S);
}

void plStateVariable::setDirty(bool dirty) { fIsDirty = dirty; }
bool plStateVariable::isDirty() const { return fIsDirty; }


/* plSDStateVariable */
plSDStateVariable::plSDStateVariable() { }

plSDStateVariable::~plSDStateVariable() {
    for (size_t i=0; i<fDataRecList.getSize(); i++)
        delete fDataRecList[i];
}

void plSDStateVariable::setDescriptor(plVarDescriptor* desc) {
    fDescriptor = desc;
    resize(fDescriptor->getCount());
}

void plSDStateVariable::setSDVarDescriptor(plStateDescriptor* desc) {
    fSDVarDescriptor = desc;
}

void plSDStateVariable::resize(size_t size) {
    for (size_t i=0; i<fDataRecList.getSize(); i++)
        delete fDataRecList[i];
    fCount = size;
    fDataRecList.setSize(size);
    for (size_t i=0; i<fDataRecList.getSize(); i++) {
        fDataRecList[i] = new plStateDataRecord();
        fDataRecList[i]->setDescriptor(fSDVarDescriptor);
    }
}

void plSDStateVariable::read(hsStream* S, plResManager* mgr) {
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

        if (idx < fDataRecList.getSize())
            fDataRecList[idx]->read(S, mgr);
    }
}

void plSDStateVariable::write(hsStream* S, plResManager* mgr) {
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

void plSDStateVariable::SetFromDefault() {
    for (size_t i=0; i<fCount; i++) {
        for (size_t j=0; j<fDataRecList[i]->getNumVars(); j++)
            fDataRecList[i]->get(j)->SetFromDefault();
    }
    setDirty(false);
}

bool plSDStateVariable::isDefault() const {
    if (fCount != fDataRecList.getSize())
        return false;
    for (size_t i=0; i<fCount; i++) {
        for (size_t j=0; j<fDataRecList[i]->getNumVars(); j++) {
            if (!fDataRecList[i]->get(j)->isDefault())
                return false;
        }
    }
    return true;
}

plStateDataRecord* plSDStateVariable::Record(size_t idx) { return fDataRecList[idx]; }


/* plSimpleStateVariable */
plSimpleStateVariable::plSimpleStateVariable() {
    fGenPtr = NULL;
}

plSimpleStateVariable::~plSimpleStateVariable() {
    IDeAlloc();
}

void plSimpleStateVariable::IDeAlloc() {
    if (fGenPtr == NULL)
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
            if (fCreatable[i] != NULL) delete fCreatable[i];
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

void plSimpleStateVariable::setDescriptor(plVarDescriptor* desc) {
    fDescriptor = desc;
    resize(fDescriptor->getCount());
}

void plSimpleStateVariable::resize(size_t size) {
    IDeAlloc();
    fCount = size;
    if (fDescriptor == NULL || fCount == 0) {
        fGenPtr = NULL;
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
        fString = new plString[fCount];
        break;
    case plVarDescriptor::kKey:
        fUoid = new plUoid[fCount];
        break;
    case plVarDescriptor::kCreatable:
        fCreatable = new plCreatable*[fCount];
        for (size_t i=0; i<fCount; i++)
            fCreatable[i] = NULL;
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

void plSimpleStateVariable::read(hsStream* S, plResManager* mgr) {
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

void plSimpleStateVariable::write(hsStream* S, plResManager* mgr) {
    plStateVariable::write(S, mgr);

    if (isDefault())
        fSimpleVarContents |= plSDL::kSameAsDefault;
    else
        fSimpleVarContents &= ~plSDL::kSameAsDefault;

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

void plSimpleStateVariable::IReadData(hsStream* S, plResManager* mgr, size_t idx) {
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
                if (fCreatable[idx] == NULL)
                    fCreatable[idx] = new plCreatableStub(hClass, len);
                fCreatable[idx]->read(S, mgr);
            } else {
                fCreatable[idx] = NULL;
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

void plSimpleStateVariable::IWriteData(hsStream* S, plResManager* mgr, size_t idx) {
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
            strncpy(buf, fString[idx].cstr(), 32);
            S->write(32, buf);
        }
        break;
    case plVarDescriptor::kKey:
        fUoid[idx].write(S);
        break;
    case plVarDescriptor::kCreatable:
        {
            if (fCreatable[idx] == NULL) {
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

void plSimpleStateVariable::SetFromDefault() {
    if (fDescriptor == NULL)
        throw hsBadParamException(__FILE__, __LINE__);
    plString def = fDescriptor->getDefault();
    def.toLower();

    for (size_t i=0; i<fDescriptor->getCount(); i++) {
        switch (fDescriptor->getType()) {
        case plVarDescriptor::kInt:
            if (def.empty())
                fInt[i] = 0;
            else
                fInt[i] = def.toInt();
            break;
        case plVarDescriptor::kUint:
            if (def.empty())
                fUint[i] = 0;
            else
                fUint[i] = def.toUint();
            break;
        case plVarDescriptor::kFloat:
            if (def.empty())
                fFloat[i] = 0.0f;
            else
                fFloat[i] = def.toFloat();
            break;
        case plVarDescriptor::kBool:
            if (def.empty())
                fBool[i] = false;
            else if (def == "false")
                fBool[i] = false;
            else if (def == "true")
                fBool[i] = true;
            else
                fBool[i] = (def.toInt() != 0);
            break;
        case plVarDescriptor::kString:
            fString[i] = def;
            break;
        case plVarDescriptor::kKey:
            break;
        case plVarDescriptor::kCreatable:
            fCreatable[i] = NULL;
            break;
        case plVarDescriptor::kDouble:
            if (def.empty())
                fDouble[i] = 0.0;
            else
                fDouble[i] = def.toFloat();
            break;
        case plVarDescriptor::kTime:
            fTime[i].toCurrentTime();
            break;
        case plVarDescriptor::kByte:
            if (def.empty())
                fByte[i] = 0;
            else
                fByte[i] = def.toUint();
            break;
        case plVarDescriptor::kChar:
            if (def.empty())
                fChar[i] = 0;
            else
                fChar[i] = def.toUint();
            break;
        case plVarDescriptor::kShort:
            if (def.empty())
                fShort[i] = 0;
            else
                fShort[i] = def.toInt();
            break;
        case plVarDescriptor::kAgeTimeOfDay:
            break;
        case plVarDescriptor::kVector3:
        case plVarDescriptor::kPoint3:
            if (def.empty()) {
                fVector[i] = hsVector3(0.0f, 0.0f, 0.0f);
            } else {
                plString parse = def;
                parse = parse.afterFirst('(');
                fVector[i].X = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                fVector[i].Y = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                fVector[i].Z = parse.beforeFirst(')').toFloat();
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
                plString parse = def;
                parse = parse.afterFirst('(');
                fQuat[i].X = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                fQuat[i].Y = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                fQuat[i].Z = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                fQuat[i].W = parse.beforeFirst(')').toFloat();
            }
            break;
        case plVarDescriptor::kRGB8:
            if (def.empty()) {
                fColor32[i] = hsColor32(0xFF000000);
            } else {
                plString parse = def;
                parse = parse.afterFirst('(');
                fColor32[i].r = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                fColor32[i].g = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                fColor32[i].b = (unsigned char)(parse.beforeFirst(')').toFloat() * 255);
            }
            break;
        case plVarDescriptor::kRGBA8:
            if (def.empty()) {
                fColor32[i] = hsColor32(0xFF000000);
            } else {
                plString parse = def;
                parse = parse.afterFirst('(');
                fColor32[i].r = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                fColor32[i].g = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                fColor32[i].b = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                fColor32[i].a = (unsigned char)(parse.beforeFirst(')').toFloat() * 255);
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

bool plSimpleStateVariable::isDefault() const {
    if (fDescriptor == NULL)
        throw hsBadParamException(__FILE__, __LINE__);
    plString def = fDescriptor->getDefault();
    def.toLower();

    if (fDescriptor->getCount() != fCount)
        return false;

    for (size_t i=0; i<fDescriptor->getCount(); i++) {
        switch (fDescriptor->getType()) {
        case plVarDescriptor::kInt:
            if (def.empty()) {
                if (fInt[i] != 0)
                    return false;
            } else {
                if (fInt[i] != def.toInt())
                    return false;
            }
            break;
        case plVarDescriptor::kUint:
            if (def.empty()) {
                if (fUint[i] != 0)
                    return false;
            } else {
                if (fUint[i] != def.toUint())
                    return false;
            }
            break;
        case plVarDescriptor::kFloat:
            if (def.empty()) {
                if (fFloat[i] != 0.0f)
                    return false;
            } else {
                if (fFloat[i] != def.toFloat())
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
                if (fBool[i] != (def.toInt() != 0))
                    return false;
            }
            break;
        case plVarDescriptor::kString:
            if (fString[i] != def)
                return false;
            break;
        case plVarDescriptor::kKey:
            return false;
            break;
        case plVarDescriptor::kCreatable:
            if (fCreatable[i] != NULL)
                return false;
            break;
        case plVarDescriptor::kDouble:
            if (def.empty()) {
                if (fDouble[i] != 0.0)
                    return false;
            } else {
                if (fDouble[i] != def.toFloat())
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
                if (fByte[i] != def.toUint())
                    return false;
            }
            break;
        case plVarDescriptor::kChar:
            if (def.empty()) {
                if (fChar[i] != 0)
                    return false;
            } else {
                if (fChar[i] != (char)def.toUint())
                    return false;
            }
            break;
        case plVarDescriptor::kShort:
            if (def.empty()) {
                if (fShort[i] != 0)
                    return false;
            } else {
                if (fShort[i] != def.toInt())
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
                plString parse = def;
                hsVector3 vec;
                parse = parse.afterFirst('(');
                vec.X = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                vec.Y = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                vec.Z = parse.beforeFirst(')').toFloat();
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
                plString parse = def;
                hsQuat quat;
                parse = parse.afterFirst('(');
                quat.X = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                quat.Y = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                quat.Z = parse.beforeFirst(',').toFloat();
                parse = parse.afterFirst(',');
                quat.W = parse.beforeFirst(')').toFloat();
                if (fQuat[i] != quat)
                    return false;
            }
            break;
        case plVarDescriptor::kRGB8:
            if (def.empty()) {
                if (fColor32[i] != hsColor32(0xFF000000))
                    return false;
            } else {
                plString parse = def;
                hsColor32 color;
                parse = parse.afterFirst('(');
                color.r = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                color.g = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                color.b = (unsigned char)(parse.beforeFirst(')').toFloat() * 255);
                if (fColor32[i] != color)
                    return false;
            }
            break;
        case plVarDescriptor::kRGBA8:
            if (def.empty()) {
                if (fColor32[i] != hsColor32(0xFF000000))
                    return false;
            } else {
                plString parse = def;
                hsColor32 color;
                parse = parse.afterFirst('(');
                color.r = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                color.g = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                color.b = (unsigned char)(parse.beforeFirst(',').toFloat() * 255);
                parse = parse.afterFirst(',');
                color.a = (unsigned char)(parse.beforeFirst(')').toFloat() * 255);
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

const plUnifiedTime& plSimpleStateVariable::getTimeStamp() const { return fTimeStamp; }
void plSimpleStateVariable::setTimeStamp(const plUnifiedTime& time) { fTimeStamp = time; }

int& plSimpleStateVariable::Int(size_t idx) { return fInt[idx]; }
unsigned int& plSimpleStateVariable::Uint(size_t idx) { return fUint[idx]; }
short& plSimpleStateVariable::Short(size_t idx) { return fShort[idx]; }
unsigned char& plSimpleStateVariable::Byte(size_t idx) { return fByte[idx]; }
signed char& plSimpleStateVariable::Char(size_t idx) { return fChar[idx]; }
float& plSimpleStateVariable::Float(size_t idx) { return fFloat[idx]; }
double& plSimpleStateVariable::Double(size_t idx) { return fDouble[idx]; }
bool& plSimpleStateVariable::Bool(size_t idx) { return fBool[idx]; }
plUoid& plSimpleStateVariable::Uoid(size_t idx) { return fUoid[idx]; }
plCreatable*& plSimpleStateVariable::Creatable(size_t idx) { return fCreatable[idx]; }
plString& plSimpleStateVariable::String(size_t idx) { return fString[idx]; }
plUnifiedTime& plSimpleStateVariable::Time(size_t idx) { return fTime[idx]; }
hsVector3& plSimpleStateVariable::Vector(size_t idx) { return fVector[idx]; }
hsQuat& plSimpleStateVariable::Quat(size_t idx) { return fQuat[idx]; }
hsColorRGBA& plSimpleStateVariable::ColorRGBA(size_t idx) { return fColorRGBA[idx]; }
hsColor32& plSimpleStateVariable::Color32(size_t idx) { return fColor32[idx]; }
hsMatrix44& plSimpleStateVariable::Matrix(size_t idx) { return fMatrix[idx]; }
