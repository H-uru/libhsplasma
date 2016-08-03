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

#ifndef _PLSDLMGR_H
#define _PLSDLMGR_H

#include "plStateDescriptor.h"
#include "Debug/hsExceptions.hpp"
#include "Stream/hsStream.h"

class PLASMA_DLL plSDLMgr {
protected:
    std::vector<plStateDescriptor*> fDescriptors;

private:
    enum ParseState {
        kFile, kUruStateDesc, kUruVarLine, kEoaStateDesc, kEoaVarLine
    };

public:
    plSDLMgr() { }
    ~plSDLMgr();

    void ReadDescriptors(const plString& filename);
    void ReadDescriptors(hsStream* S);
    void ClearDescriptors();
    plStateDescriptor* GetDescriptor(const plString& name, int version = -1);

    void read(hsStream* S);
    void write(hsStream* S);
};

class PLASMA_DLL plSDLParseException : public hsException {
public:
    plSDLParseException(const char* file, unsigned long line,
                        const char* msg, ...) HS_NOEXCEPT;
};

#endif
