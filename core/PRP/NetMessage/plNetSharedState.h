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

#ifndef _PLNETSHAREDSTATE_H
#define _PLNETSHAREDSTATE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

struct PLASMA_DLL plGenericType
{
public:
    enum Type
    {
        kInt, kFloat, kBool, kString, kByte, kAny, kUint, kDouble, kNone = 0xFF
    };

    union
    {
        int fInt;
        unsigned int fUint;
        float fFloat;
        double fDouble;
        bool fBool;
        signed char fByte;
    };
    ST::string fString;
    unsigned char fType;

public:
    plGenericType() : fType(kNone) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class PLASMA_DLL plGenericVar
{
private:
    ST::string fName;
    plGenericType fValue;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    ST::string getName() const { return fName; }
    const plGenericType& getValue() const { return fValue; }

    void setName(const ST::string& name) { fName = name; }
    void setValue(const plGenericType& value) { fValue = value; }

    plGenericType::Type getType() const { return (plGenericType::Type)fValue.fType; }
    int getInt() const { return fValue.fInt; }
    unsigned int getUint() const { return fValue.fUint; }
    float getFloat() const { return fValue.fFloat; }
    double getDouble() const { return fValue.fDouble; }
    bool getBool() const { return fValue.fBool; }
    signed char getByte() const { return fValue.fByte; }
    ST::string getString() const { return fValue.fString; }
};


class PLASMA_DLL plNetSharedState
{
private:
    ST::string fName;
    std::vector<plGenericVar> fVars;
    bool fServerMayDelete;

public:
    plNetSharedState() : fServerMayDelete(false) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    ST::string getName() const { return fName; }
    bool getServerMayDelete() const { return fServerMayDelete; }

    void setName(const ST::string& name) { fName = name; }
    void setServerMayDelete(bool may) { fServerMayDelete = may; }

    const std::vector<plGenericVar>& getVars() const { return fVars; }
    std::vector<plGenericVar>& getVars() { return fVars; }
    void addVar(const plGenericVar& var) { fVars.push_back(var); }
    void delVar(size_t idx) { fVars.erase(fVars.begin() + idx); }
    void clearVars() { fVars.clear(); }
};

#endif
