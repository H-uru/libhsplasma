#include "pfGUIPopUpMenu.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

pfGUIPopUpMenu::pfGUIPopUpMenu()
              : fParent(NULL), /*fKeyGen(NULL),*/ fNeedsRebuilding(false),
                fWaitingForSkin(false), fOriginX(0.0f), fOriginY(0.0f),
                fMargin(4), fSubMenuOpen(-1), fAlignment(kAlignDownRight) {
    fFlags.setBit(kModalOutsideMenus);
}

pfGUIPopUpMenu::~pfGUIPopUpMenu() {
    for (size_t i=0; i<fMenuItems.getSize(); i++)
        if (fMenuItems[i].fHandler) delete fMenuItems[i].fHandler;
}

IMPLEMENT_CREATABLE(pfGUIPopUpMenu, kGUIPopUpMenu, pfGUIDialogMod)

void pfGUIPopUpMenu::read(hsStream* S, plResManager* mgr) {
    pfGUIDialogMod::read(S, mgr);

    //fKeyGen = new pfPopUpKeyGenerator(fName, getKey()->getUoid());
    fOriginX = -1.0f;
    fOriginY = -1.0f;
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

void pfGUIPopUpMenu::prcWrite(pfPrcHelper* prc) {
    pfGUIDialogMod::prcWrite(prc);

    prc->startTag("PopUpParams");
    prc->writeParam("Margin", fMargin);
    prc->writeParam("Alignment", fAlignment);
    prc->endTag(true);

    prc->writeSimpleTag("MenuItems");
    for (size_t i=0; i<fMenuItems.getSize(); i++) {
        prc->startTag("pfMenuItem");
        prc->writeParam("Name", fMenuItems[i].fName);
        prc->endTag();

        pfGUICtrlProcWriteableObject::PrcWrite(prc, fMenuItems[i].fHandler);

        prc->writeSimpleTag("SubMenu");
        fMenuItems[i].fSubMenu->prcWrite(prc);
        prc->closeTag();
    }

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
