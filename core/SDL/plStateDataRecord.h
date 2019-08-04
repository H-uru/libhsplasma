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

#ifndef _PLSTATEDATARECORD_H
#define _PLSTATEDATARECORD_H

#include "plSDLMgr.h"
#include "plStateVariable.h"

class PLASMA_DLL plStateDataRecord
{
public:
    enum Flags
    {
        kVolatile = 0x1
    };

protected:
    static const unsigned char kIOVersion;

    plStateDescriptor* fDescriptor;
    plUoid fAssocObject;
    std::vector<plStateVariable*> fVarsList, fSDVarsList;
    std::vector<plStateVariable*> fAllVars;
    unsigned int fFlags;

public:
    plStateDataRecord() : fDescriptor(), fFlags() { }
    ~plStateDataRecord();

    static void ReadStreamHeader(hsStream* S, ST::string& name, int& version,
                                 plUoid* objUoid);
    static void WriteStreamHeader(hsStream* S, const ST::string& name, int version,
                                  plUoid* objUoid);
    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    /*void prcParse(const pfPrcTag* tag);*/ //Zrax'll kill me >.>

    plStateDescriptor* getDescriptor() const { return fDescriptor; }
    void setDescriptor(plStateDescriptor* desc);

    size_t getNumVars() const { return fAllVars.size(); }
    plStateVariable* get(size_t idx) const { return fAllVars[idx]; }
    plStateVariable* get(const ST::string& name) const;
};

#endif
