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

#include "pfGUIPopUpMenu.h"
#include <cstring>

pfGUIPopUpMenu::pfGUIPopUpMenu()
    : fMargin(4), fAlignment(kAlignDownRight)
{
    fFlags.setName(kStayOpenAfterClick, "kStayOpenAfterClick");
    fFlags.setName(kModalOutsideMenus, "kModalOutsideMenus");
    fFlags.setName(kOpenSubMenusOnHover, "kOpenSubMenusOnHover");
    fFlags.setName(kScaleWithResolution, "kScaleWithResolution");
    fFlags[kModalOutsideMenus] = true;
}

pfGUIPopUpMenu::~pfGUIPopUpMenu()
{
    for (auto item = fMenuItems.begin(); item != fMenuItems.end(); ++item)
        delete item->fHandler;
}

void pfGUIPopUpMenu::read(hsStream* S, plResManager* mgr)
{
    pfGUIDialogMod::read(S, mgr);

    fMargin = S->readShort();
    fMenuItems.resize(S->readInt());
    for (size_t i=0; i<fMenuItems.size(); i++) {
        char buf[257];
        S->read(256, buf);
        buf[256] = 0;
        fMenuItems[i].fName = buf;
        fMenuItems[i].fHandler = pfGUICtrlProcWriteableObject::Read(S);
        fMenuItems[i].fSubMenu = mgr->readKey(S);
    }

    fSkin = mgr->readKey(S);
    fOriginAnchor = mgr->readKey(S);
    fOriginContext = mgr->readKey(S);
    fAlignment = (Alignment)S->readByte();
}

void pfGUIPopUpMenu::write(hsStream* S, plResManager* mgr)
{
    pfGUIDialogMod::write(S, mgr);

    S->writeShort(fMargin);
    S->writeInt(fMenuItems.size());
    for (size_t i=0; i<fMenuItems.size(); i++) {
        char buf[256];
        memset(buf, 0, 256);
        strncpy(buf, fMenuItems[i].fName.c_str(), 256);
        S->write(256, buf);
        pfGUICtrlProcWriteableObject::Write(S, fMenuItems[i].fHandler);
        mgr->writeKey(S, fMenuItems[i].fSubMenu);
    }

    mgr->writeKey(S, fSkin);
    mgr->writeKey(S, fOriginAnchor);
    mgr->writeKey(S, fOriginContext);
    S->writeByte(fAlignment);
}

void pfGUIPopUpMenu::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIDialogMod::IPrcWrite(prc);

    prc->startTag("PopUpParams");
    prc->writeParam("Margin", fMargin);
    prc->writeParam("Alignment", fAlignment);
    prc->endTag(true);

    prc->writeSimpleTag("MenuItems");
    for (size_t i=0; i<fMenuItems.size(); i++) {
        prc->startTag("pfMenuItem");
        prc->writeParam("Name", fMenuItems[i].fName);
        prc->endTag();

        prc->writeSimpleTag("Handler");
        pfGUICtrlProcWriteableObject::PrcWrite(prc, fMenuItems[i].fHandler);
        prc->closeTag();

        prc->writeSimpleTag("SubMenu");
        plResManager::PrcWriteKey(prc, fMenuItems[i].fSubMenu);
        prc->closeTag();

        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("Skin");
    plResManager::PrcWriteKey(prc, fSkin);
    prc->closeTag();
    prc->writeSimpleTag("OriginAnchor");
    plResManager::PrcWriteKey(prc, fOriginAnchor);
    prc->closeTag();
    prc->writeSimpleTag("OriginContext");
    plResManager::PrcWriteKey(prc, fOriginContext);
    prc->closeTag();
}

void pfGUIPopUpMenu::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PopUpParams") {
        fMargin = tag->getParam("Margin", "0").to_uint();
        fAlignment = (Alignment)tag->getParam("Alignment", "0").to_int();
    } else if (tag->getName() == "MenuItems") {
        fMenuItems.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMenuItems.size(); i++) {
            if (child->getName() != "pfMenuItem")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fMenuItems[i].fName = tag->getParam("Name", "");
            size_t nSubChildren = child->countChildren();
            const pfPrcTag* subchild = child->getFirstChild();
            for (size_t j=0; j<nSubChildren; j++) {
                if (subchild->getName() == "Handler") {
                    if (subchild->hasChildren())
                        fMenuItems[i].fHandler = pfGUICtrlProcWriteableObject::PrcParse(subchild->getFirstChild());
                } else if (subchild->getName() == "SubMenu") {
                    if (subchild->hasChildren())
                        fMenuItems[i].fSubMenu = mgr->prcParseKey(tag->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                }
                subchild = subchild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Skin") {
        if (tag->hasChildren())
            fSkin = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "OriginAnchor") {
        if (tag->hasChildren())
            fOriginAnchor = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "OriginContext") {
        if (tag->hasChildren())
            fOriginContext = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIDialogMod::IPrcParse(tag, mgr);
    }
}

void pfGUIPopUpMenu::addItem(const ST::string& name, pfGUICtrlProcWriteableObject* handler,
                             plKey subMenu, float yoffs)
{
    pfMenuItem item;
    item.fName = name;
    item.fHandler = handler;
    item.fSubMenu = std::move(subMenu);
    item.fYOffsetToNext = yoffs;
    fMenuItems.push_back(item);
}

void pfGUIPopUpMenu::delItem(size_t idx)
{
    delete fMenuItems[idx].fHandler;
    fMenuItems.erase(fMenuItems.begin() + idx);
}

void pfGUIPopUpMenu::moveItem(size_t from, size_t to)
{
    if (from == to)
        return;

    pfMenuItem item = fMenuItems[from];
    if (from > to) {
        for (size_t i=from; i>to; i--)
            fMenuItems[i] = fMenuItems[i-1];
    } else {
        for (size_t i=from; i<to; i++)
            fMenuItems[i] = fMenuItems[i+1];
    }
    fMenuItems[to] = item;
}

void pfGUIPopUpMenu::clearItems()
{
    for (auto item = fMenuItems.begin(); item != fMenuItems.end(); ++item)
        delete item->fHandler;
    fMenuItems.clear();
}
