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

#include "plCreatable.h"
#include "Stream/hsRAMStream.h"

/* plCreatable */
short plCreatable::ClassIndex(PlasmaVer ver) const
{
    return pdUnifiedTypeMap::MappedToPlasma(ClassIndex(), ver);
}

const char* plCreatable::ClassName() const
{
    return pdUnifiedTypeMap::ClassName(ClassIndex());
}

void plCreatable::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag(ClassName());
    IPrcWrite(prc);
    prc->closeTag();
}

void plCreatable::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        IPrcParse(child, mgr);
        child = child->getNextSibling();
    }
}

ST::string plCreatable::toPrc(pfPrcHelper::PrcExclude exclude)
{
    hsRAMStream S;
    pfPrcHelper prc(&S);
    prc.exclude(exclude);
    prcWrite(&prc);
    return ST::string::from_utf8((const char*)S.data(), S.size(), ST::assume_valid);
}

void plCreatable::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}


/* plCreatableStub */
plCreatableStub::plCreatableStub(short hClass, size_t length)
    : fClassIdx(hClass), fDataLen(length)
{
    fData = new uint8_t[fDataLen];
}

plCreatableStub::~plCreatableStub()
{
    delete[] fData;
}

void plCreatableStub::read(hsStream* S, plResManager* mgr)
{
    S->read(fDataLen, fData);
}

void plCreatableStub::write(hsStream* S, plResManager* mgr)
{
    S->write(fDataLen, fData);
}

void plCreatableStub::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plCreatableStub");
    prc->writeParam("Type", pdUnifiedTypeMap::ClassName(fClassIdx));
    prc->endTag();
    prc->writeHexStream(fDataLen, fData);
    prc->closeTag();
}

void plCreatableStub::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() != "plCreatableStub")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fClassIdx = pdUnifiedTypeMap::ClassIndex(tag->getParam("Type", "").c_str());

    delete[] fData;
    fDataLen = tag->getContents().size();
    fData = new uint8_t[fDataLen];
    tag->readHexStream(fDataLen, fData);
}
