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

#ifndef _PLSTATEVARIABLE_H
#define _PLSTATEVARIABLE_H

#include "plStateDescriptor.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Math/hsMatrix44.h"
#include "Sys/hsColor.h"
#include "Sys/plUnifiedTime.h"
#include "PRP/plCreatable.h"
#include "PRP/KeyedObject/plUoid.h"

class PLASMA_DLL plStateVarNotificationInfo
{
protected:
    ST::string fHintString;

public:
    void read(hsStream* S);
    void write(hsStream* S);
};


class PLASMA_DLL plStateVariable
{
protected:
    unsigned char fContents;
    plStateVarNotificationInfo fNotificationInfo;
    plVarDescriptor* fDescriptor;
    size_t fCount;
    bool fIsDirty;

public:
    plStateVariable()
        : fContents(plSDL::kHasNotificationInfo), fDescriptor(), fCount(1),
          fIsDirty() { }

    virtual ~plStateVariable() { }

    virtual void setDescriptor(plVarDescriptor* desc) = 0;
    plVarDescriptor* getDescriptor() const { return fDescriptor; }

    virtual void resize(size_t size) = 0;
    size_t getCount() const { return fCount; }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

    virtual void SetFromDefault() = 0;
    virtual bool isDefault(bool secondChance=false) const = 0;

    void setDirty(bool dirty = true) { fIsDirty = dirty; }
    bool isDirty() const { return fIsDirty; }
};


class PLASMA_DLL plSDStateVariable : public plStateVariable
{
protected:
    std::vector<class plStateDataRecord*> fDataRecList;
    plStateDescriptor* fSDVarDescriptor;

public:
    plSDStateVariable() : fSDVarDescriptor() { }
    ~plSDStateVariable();

    void setDescriptor(plVarDescriptor* desc) HS_OVERRIDE;
    void setSDVarDescriptor(plStateDescriptor* desc) { fSDVarDescriptor = desc; }
    void resize(size_t size) HS_OVERRIDE;

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    void SetFromDefault() HS_OVERRIDE;
    bool isDefault(bool secondChance=false) const HS_OVERRIDE;

    plStateDataRecord* Record(size_t idx) const { return fDataRecList[idx]; }
};


class PLASMA_DLL plSimpleStateVariable : public plStateVariable
{
protected:
    union
    {
        void* fGenPtr;

        int* fInt;
        unsigned int* fUint;
        short* fShort;
        unsigned char* fByte;
        signed char* fChar;
        float* fFloat;
        double* fDouble;
        bool* fBool;
        plUoid* fUoid;
        plCreatable** fCreatable;
        ST::string* fString;
        plUnifiedTime* fTime;
        hsVector3* fVector;
        hsQuat* fQuat;
        hsColorRGBA* fColorRGBA;
        hsColor32* fColor32;
        hsMatrix44* fMatrix;
    };
    plUnifiedTime fTimeStamp;
    unsigned char fSimpleVarContents;

public:
    plSimpleStateVariable() : fGenPtr(), fSimpleVarContents() { }
    ~plSimpleStateVariable() { IDeAlloc(); }

    void setDescriptor(plVarDescriptor* desc) HS_OVERRIDE;
    void resize(size_t size) HS_OVERRIDE;

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    void SetFromDefault() HS_OVERRIDE;
    bool isDefault(bool secondChance=false) const HS_OVERRIDE;

    const plUnifiedTime& getTimeStamp() const { return fTimeStamp; }
    void setTimeStamp(const plUnifiedTime& time) { fTimeStamp = time; }

    int& Int(size_t idx) { return fInt[idx]; }
    unsigned int& Uint(size_t idx) { return fUint[idx]; }
    short& Short(size_t idx) { return fShort[idx]; }
    unsigned char& Byte(size_t idx) { return fByte[idx]; }
    signed char& Char(size_t idx) { return fChar[idx]; }
    float& Float(size_t idx) { return fFloat[idx]; }
    double& Double(size_t idx) { return fDouble[idx]; }
    bool& Bool(size_t idx) { return fBool[idx]; }
    plUoid& Uoid(size_t idx) { return fUoid[idx]; }
    plCreatable*& Creatable(size_t idx) { return fCreatable[idx]; }
    ST::string& String(size_t idx) { return fString[idx]; }
    plUnifiedTime& Time(size_t idx) { return fTime[idx]; }
    hsVector3& Vector(size_t idx) { return fVector[idx]; }
    hsQuat& Quat(size_t idx) { return fQuat[idx]; }
    hsColorRGBA& ColorRGBA(size_t idx) { return fColorRGBA[idx]; }
    hsColor32& Color32(size_t idx) { return fColor32[idx]; }
    hsMatrix44& Matrix(size_t idx) { return fMatrix[idx]; }

protected:
    void IDeAlloc();
    void IReadData(hsStream* S, plResManager* mgr, size_t idx);
    void IWriteData(hsStream* S, plResManager* mgr, size_t idx);
};

#endif
