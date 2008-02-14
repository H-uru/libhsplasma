#ifndef _PLSTATEDESCRIPTOR_H
#define _PLSTATEDESCRIPTOR_H

#include "CoreLib/plString.h"
#include "CoreLib/hsTArray.hpp"

/* Note: for plStateDescriptor::fVersion, -1 on a search from plSDLMgr means
 * "get the latest version", whereas -1 on a returned plStateDescritpor means
 * "this descriptor is invalid".  Outside of these classes, it should only be
 * necessary to specify the version when needed in plSDLMgr, and to use the
 * isValid() function on returned plStateDescriptor objects.
 */

DllClass plStateVariable {
public:
    enum Type {
        kNone = 0xFF,
        kInt = 0, kFloat, kBool, kString, kKey, kStateDescriptor, kCreatable,
        kDouble, kTime, kByte, kShort, kAgeTimeOfDay,
        kVector3 = 0x32, kPoint3, kRGB, kRGBA, kQuaternion, kRGB8, kRGBA8,

        // For Myst 5
        kUint, kChar, kMatrix44, kBuffer, kAgeTimeElapsed, kGameTimeElapsed
    };

    enum Flags {
        kInternal = 0x1,
        kAlwaysNew = 0x2,
        kVariableLength = 0x4
    };

protected:
    plString fName, fDefault;
    size_t fCount;
    Type fType;
    unsigned int fFlags;
    plString fStateDescType;

public:
    plStateVariable();
    ~plStateVariable();

    const plString& getName() const;
    const plString& getDefault() const;
    size_t getCount() const;
    Type getType() const;
    const plString& getStateDescType() const;
    bool isInternal() const;
    bool isAlwaysNew() const;
    bool isVariableLength() const;
    bool isValid() const;

    void setName(const plString& name);
    void setDefault(const plString& def);
    void setCount(size_t count);
    void setType(Type type);
    void setStateDescType(const plString& type);
    void setInternal(bool internal);
    void setAlwaysNew(bool alwaysNew);
    void setVariableLength(bool varLength);

    static Type GetTypeFromString(const plString& type, bool isEoa);
};

DllClass plStateDescriptor {
protected:
    plString fName;
    int fVersion;
    hsTArray<plStateVariable*> fVariables;

public:
    plStateDescriptor();
    ~plStateDescriptor();

    const plString& getName() const;
    int getVersion() const;
    bool isValid() const;

    void setName(const plString& name);
    void setVersion(int ver);

    plStateVariable* get(size_t idx);
    plStateVariable* get(const plString& name);
    void set(size_t idx, plStateVariable* var);
    void set(const plString& name, plStateVariable* var);

    size_t getNumVariables() const;
    void addVariable(plStateVariable* var);
    void delVariable(size_t idx);
    void delVariable(const plString& name);
};

#endif
