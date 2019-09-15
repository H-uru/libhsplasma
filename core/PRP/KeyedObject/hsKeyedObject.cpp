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

#include "hsKeyedObject.h"
#include "Stream/hsRAMStream.h"

/* hsKeyedObject */
void hsKeyedObject::init(const ST::string& name)
{
    myKey = new plKeyData();
    myKey->setType(ClassIndex());
    myKey->setName(name);
    myKey->setObj(this);
}

void hsKeyedObject::read(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isMoul())
        myKey = mgr->readKey(S);
    else
        myKey = mgr->readUoid(S);
    if (myKey.Exists()) {
        // In case we're replacing a key
        delete myKey->getObj();
        myKey->setObj(this);
    }
}

void hsKeyedObject::write(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isMoul())
        mgr->writeKey(S, myKey);
    else
        mgr->writeUoid(S, myKey);
}

void hsKeyedObject::IPrcWrite(pfPrcHelper* prc)
{
    plResManager::PrcWriteKey(prc, myKey);
}

void hsKeyedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plKey") {
        myKey = mgr->prcParseKey(tag);
        if (myKey.Exists())
            myKey->setObj(this);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void hsKeyedObject::setKey(plKey key)
{
    myKey = std::move(key);
    if (myKey.Exists())
        myKey->setObj(this);
}


/* hsKeyedObjectStub */
hsKeyedObjectStub::~hsKeyedObjectStub()
{
    delete fStub;
}

void hsKeyedObjectStub::write(hsStream* S, plResManager* mgr)
{
    fStub->write(S, mgr);
}

void hsKeyedObjectStub::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);
    fStub->prcWrite(prc);
}

void hsKeyedObjectStub::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plCreatableStub")
        fStub->prcParse(tag, mgr);
    else
        hsKeyedObject::IPrcParse(tag, mgr);
}

void hsKeyedObjectStub::setStub(plCreatableStub* stub)
{
    delete fStub;
    fStub = stub;
}
