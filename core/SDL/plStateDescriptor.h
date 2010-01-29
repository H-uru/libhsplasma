#ifndef _PLSTATEDESCRIPTOR_H
#define _PLSTATEDESCRIPTOR_H

#include "plSDL.h"

/* Note: for plStateDescriptor::fVersion, -1 on a search from plSDLMgr means
 * "get the latest version", whereas -1 on a returned plStateDescritpor means
 * "this descriptor is invalid".  Outside of these classes, it should only be
 * necessary to specify the version when needed in plSDLMgr, and to use the
 * isValid() function on returned plStateDescriptor objects.
 */

DllClass plVarDescriptor {
public:
    enum Type {
        kNone = 0xFF,
        kInt = 0, kFloat, kBool, kString, kKey, kStateDescriptor, kCreatable,
        kDouble, kTime, kByte, kShort, kAgeTimeOfDay,
        kVector3 = 50, kPoint3, kRGB, kRGBA, kQuaternion, kRGB8, kRGBA8,

        // For Myst 5
        kUint, kChar, kMatrix44, kBuffer, kAgeTimeElapsed, kGameTimeElapsed
    };

    enum Flags {
        kInternal = 0x1,
        kAlwaysNew = 0x2,
        kVariableLength = 0x4
    };

protected:
    plString fName, fDefault, fDisplay;
    size_t fCount;
    Type fType;
    unsigned int fFlags;
    plString fStateDescType;
    int fStateDescVer;
    class plStateDescriptor* fStateDesc;

public:
    plVarDescriptor();
    ~plVarDescriptor();

    void read(hsStream* S);
    void write(hsStream* S);

    const plString& getName() const;
    const plString& getDefault() const;
    const plString& getDisplay() const;
    size_t getCount() const;
    Type getType() const;
    const plString& getStateDescType() const;
    int getStateDescVer() const;
    plStateDescriptor* getStateDesc() const;
    bool isInternal() const;
    bool isAlwaysNew() const;
    bool isVariableLength() const;
    bool isValid() const;

    void setName(const plString& name);
    void setDefault(const plString& def);
    void setDisplay(const plString& disp);
    void setCount(size_t count);
    void setType(Type type);
    void setStateDescType(const plString& type);
    void setStateDescVer(int ver);
    void setStateDesc(plStateDescriptor* desc);
    void setInternal(bool internal);
    void setAlwaysNew(bool alwaysNew);
    void setVariableLength(bool varLength);

    static Type GetTypeFromString(const plString& type, bool isEoa);
};

DllClass plStateDescriptor {
protected:
    plString fName;
    int fVersion;
    hsTArray<plVarDescriptor*> fVariables;

public:
    plStateDescriptor();
    ~plStateDescriptor();

    void read(hsStream* S);
    void write(hsStream* S);

    const plString& getName() const;
    int getVersion() const;
    bool isValid() const;

    void setName(const plString& name);
    void setVersion(int ver);

    plVarDescriptor* get(size_t idx);
    plVarDescriptor* get(const plString& name);
    void set(size_t idx, plVarDescriptor* var);
    void set(const plString& name, plVarDescriptor* var);

    size_t getNumVars() const;
    void addVariable(plVarDescriptor* var);
    void delVariable(size_t idx);
    void delVariable(const plString& name);
    void clearVariables();
};

#endif
