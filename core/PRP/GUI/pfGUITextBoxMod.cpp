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

#include "pfGUITextBoxMod.h"

pfGUITextBoxMod::pfGUITextBoxMod()
{
    fFlags.setName(kCenterJustify, "kCenterJustify");
    fFlags.setName(kRightJustify, "kRightJustify");
}

void pfGUITextBoxMod::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    int len = S->readInt();
    fText = S->readStr(len);

    if ((!S->getVer().isUruSP() || S->getVer().isUniversal())
            && S->readBool())
        fLocalizationPath = S->readSafeWStr();
    else
        fLocalizationPath = ST::string();
}

void pfGUITextBoxMod::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fText.size());
    S->writeStr(fText);

    if (!S->getVer().isUruSP() || S->getVer().isUniversal()) {
        S->writeBool(!fLocalizationPath.empty());
        if (!fLocalizationPath.empty())
            S->writeSafeWStr(fLocalizationPath);
    }
}

void pfGUITextBoxMod::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("Text");
    prc->writeHexStream(fText.size(), (unsigned char*)fText.c_str());
    prc->closeTag();

    prc->startTag("LocalizationPath");
    prc->writeParam("value", fLocalizationPath);
    prc->endTag(true);
}

void pfGUITextBoxMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Text") {
        size_t bufLen = tag->getContents().size();
        char* buf = new char[bufLen + 1];
        tag->readHexStream(bufLen, (unsigned char*)buf);
        buf[bufLen] = 0;
        fText = buf;
        delete[] buf;
    } else if (tag->getName() == "LocalizationPath") {
        fLocalizationPath = tag->getParam("value", "");
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
