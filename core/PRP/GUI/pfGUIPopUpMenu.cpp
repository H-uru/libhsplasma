#include "pfGUIPopUpMenu.h"

pfGUIPopUpMenu::pfGUIPopUpMenu()
              : fMargin(4), fAlignment(kAlignDownRight) {
    fFlags.setName(kStayOpenAfterClick, "kStayOpenAfterClick");
    fFlags.setName(kModalOutsideMenus, "kModalOutsideMenus");
    fFlags.setName(kOpenSubMenusOnHover, "kOpenSubMenusOnHover");
    fFlags.setName(kScaleWithResolution, "kScaleWithResolution");
    fFlags[kModalOutsideMenus] = true;
}

pfGUIPopUpMenu::~pfGUIPopUpMenu() {
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
        if (fMenuItems[i].fHandler != NULL)
            delete fMenuItems[i].fHandler;
    }
}

void pfGUIPopUpMenu::read(hsStream* S, plResManager* mgr) {
    pfGUIDialogMod::read(S, mgr);

    fMargin = S->readShort();
    fMenuItems.setSize(S->readInt());
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
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

void pfGUIPopUpMenu::write(hsStream* S, plResManager* mgr) {
    pfGUIDialogMod::write(S, mgr);

    S->writeShort(fMargin);
    S->writeInt(fMenuItems.getSize());
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
        char buf[256];
        memset(buf, 0, 256);
        strncpy(buf, fMenuItems[i].fName, 256);
        S->write(256, buf);
        pfGUICtrlProcWriteableObject::Write(S, fMenuItems[i].fHandler);
        mgr->writeKey(S, fMenuItems[i].fSubMenu);
    }

    mgr->writeKey(S, fSkin);
    mgr->writeKey(S, fOriginAnchor);
    mgr->writeKey(S, fOriginContext);
    S->writeByte(fAlignment);
}

void pfGUIPopUpMenu::IPrcWrite(pfPrcHelper* prc) {
    pfGUIDialogMod::IPrcWrite(prc);

    prc->startTag("PopUpParams");
    prc->writeParam("Margin", fMargin);
    prc->writeParam("Alignment", fAlignment);
    prc->endTag(true);

    prc->writeSimpleTag("MenuItems");
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
        prc->startTag("pfMenuItem");
        prc->writeParam("Name", fMenuItems[i].fName);
        prc->endTag();

        prc->writeSimpleTag("Handler");
        pfGUICtrlProcWriteableObject::PrcWrite(prc, fMenuItems[i].fHandler);
        prc->closeTag();

        prc->writeSimpleTag("SubMenu");
        fMenuItems[i].fSubMenu->prcWrite(prc);
        prc->closeTag();

        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("Skin");
    fSkin->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("OriginAnchor");
    fOriginAnchor->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("OriginContext");
    fOriginContext->prcWrite(prc);
    prc->closeTag();
}

void pfGUIPopUpMenu::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PopUpParams") {
        fMargin = tag->getParam("Margin", "0").toUint();
        fAlignment = (Alignment)tag->getParam("Alignment", "0").toInt();
    } else if (tag->getName() == "MenuItems") {
        fMenuItems.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMenuItems.getSize(); i++) {
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

void pfGUIPopUpMenu::addItem(const plString& name, pfGUICtrlProcWriteableObject* handler,
                             plKey subMenu, float yoffs) {
    pfMenuItem item;
    item.fName = name;
    item.fHandler = handler;
    item.fSubMenu = subMenu;
    item.fYOffsetToNext = yoffs;
    fMenuItems.append(item);
}

void pfGUIPopUpMenu::delItem(size_t idx) {
    if (fMenuItems[idx].fHandler != NULL)
        delete fMenuItems[idx].fHandler;
    fMenuItems.remove(idx);
}

void pfGUIPopUpMenu::moveItem(size_t from, size_t to) {
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

void pfGUIPopUpMenu::clearItems() {
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
        if (fMenuItems[i].fHandler != NULL)
            delete fMenuItems[i].fHandler;
    }
    fMenuItems.clear();
}
