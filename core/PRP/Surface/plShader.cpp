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

#include "plShader.h"
#include <cstring>

/* plShaderConst */
plShaderConst::plShaderConst(const plShaderConst& init)
{
    memcpy(fArray, init.fArray, sizeof(fArray));
}

plShaderConst& plShaderConst::operator=(const plShaderConst& init)
{
    memcpy(fArray, init.fArray, sizeof(fArray));
    return *this;
}

void plShaderConst::read(hsStream* S)
{
    fArray[0] = S->readFloat();
    fArray[1] = S->readFloat();
    fArray[2] = S->readFloat();
    fArray[3] = S->readFloat();
}

void plShaderConst::write(hsStream* S)
{
    S->writeFloat(fArray[0]);
    S->writeFloat(fArray[1]);
    S->writeFloat(fArray[2]);
    S->writeFloat(fArray[3]);
}

void plShaderConst::prcWrite(pfPrcHelper* prc)
{
    prc->writeTagNoBreak("plShaderConst");
    prc->directWrite(ST::format("{f} {f} {f} {f}",
                     fArray[0], fArray[1], fArray[2], fArray[3]));
    prc->closeTagNoBreak();
}

void plShaderConst::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plShaderConst")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    std::list<ST::string> data = tag->getContents();
    if (data.size() != 4)
        throw pfPrcParseException(__FILE__, __LINE__, "plShaderConst expects 4 floats");
    auto iter = data.begin();
    fArray[0] = (*iter++).to_float();
    fArray[1] = (*iter++).to_float();
    fArray[2] = (*iter++).to_float();
    fArray[3] = (*iter++).to_float();
}


/* plShader */
void plShader::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fConsts.resize(S->readInt());
    for (size_t i=0; i<fConsts.size(); i++)
        fConsts[i].read(S);
    fID = (plShaderID)S->readInt();

    fInput = S->readByte();
    fOutput = S->readByte();
}

void plShader::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fConsts.size());
    for (size_t i=0; i<fConsts.size(); i++)
        fConsts[i].write(S);
    S->writeInt(fID);

    S->writeByte(fInput);
    S->writeByte(fOutput);
}

void plShader::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Constants");
    for (size_t i=0; i<fConsts.size(); i++)
        fConsts[i].prcWrite(prc);
    prc->closeTag();

    prc->startTag("ShaderParams");
    prc->writeParam("ID", fID);
    prc->writeParam("Input", fInput);
    prc->writeParam("Output", fOutput);
    prc->endTag(true);
}

void plShader::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Constants") {
        const pfPrcTag* child = tag->getFirstChild();
        fConsts.resize(tag->countChildren());
        for (size_t i=0; i<fConsts.size(); i++) {
            fConsts[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ShaderParams") {
        fID = (plShaderID)tag->getParam("ID", "0").to_uint();
        fInput = tag->getParam("Input", "0").to_uint();
        fOutput = tag->getParam("Output", "0").to_uint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
