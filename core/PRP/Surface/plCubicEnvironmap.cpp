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

#include "plCubicEnvironmap.h"

const char* plCubicEnvironmap::kFaceNames[kNumFaces] = {
    "Left", "Right", "Front", "Back", "Top", "Bottom"
};

void plCubicEnvironmap::read(hsStream* S, plResManager* mgr)
{
    plBitmap::read(S, mgr);

    for (int i=0; i<kNumFaces; i++) {
        if (S->getVer().isUru() || S->getVer().isUniversal())
            fFaces[i].readData(S);
        else
            fFaces[i].read(S, mgr);
        fFaces[i].init(getKey()->getName() + "-" + kFaceNames[i]);
    }
}

void plCubicEnvironmap::write(hsStream* S, plResManager* mgr)
{
    plBitmap::write(S, mgr);

    for (int i=0; i<kNumFaces; i++) {
        if (S->getVer().isUru() || S->getVer().isUniversal())
            fFaces[i].writeData(S);
        else
            fFaces[i].write(S, mgr);
    }
}

void plCubicEnvironmap::IPrcWrite(pfPrcHelper* prc)
{
    plBitmap::IPrcWrite(prc);

    prc->writeSimpleTag("Faces");
    for (int i=0; i<kNumFaces; i++)
        fFaces[i].prcWrite(prc);
    prc->closeTag();
}

void plCubicEnvironmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Faces") {
        if (tag->countChildren() != kNumFaces)
            throw pfPrcParseException(__FILE__, __LINE__, "plCubicEnvironmap expects exactly 6 faces");
        const pfPrcTag* face = tag->getFirstChild();
        for (size_t i=0; i<kNumFaces; i++) {
            fFaces[i].prcParse(face, mgr);
            face = face->getNextSibling();
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}
