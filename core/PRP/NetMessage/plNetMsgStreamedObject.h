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

#ifndef _PLNETMSGSTREAMEDOBJECT_H
#define _PLNETMSGSTREAMEDOBJECT_H

#include "plNetMsgStream.h"
#include "plNetMsgObject.h"

class PLASMA_DLL plNetMsgStreamedObject : public plNetMsgObject {
    CREATABLE(plNetMsgStreamedObject, kNetMsgStreamedObject, plNetMsgObject)

private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStreamedObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsRAMStream* getStream() { return &fStream; }

    unsigned char getCompressionType() const { return fCompressionType; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
};

#endif
