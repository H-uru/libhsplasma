#include "pfGUISkin.h"

/* pfGUISkin::pfSRect */
pfGUISkin::pfSRect::pfSRect() : fX(0), fY(0), fWidth(0), fHeight(0) { }

void pfGUISkin::pfSRect::read(hsStream* S) {
    fX = S->readShort();
    fY = S->readShort();
    fWidth = S->readShort();
    fHeight = S->readShort();
}

void pfGUISkin::pfSRect::write(hsStream* S) {
    S->writeShort(fX);
    S->writeShort(fY);
    S->writeShort(fWidth);
    S->writeShort(fHeight);
}

void pfGUISkin::pfSRect::prcWrite(pfPrcHelper* prc) {
    prc->startTag("pfSRect");
    prc->writeParam("X", fX);
    prc->writeParam("Y", fY);
    prc->writeParam("width", fWidth);
    prc->writeParam("height", fHeight);
    prc->endTag(true);
}

void pfGUISkin::pfSRect::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "pfSRect")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fX = tag->getParam("X", "0").toUint();
    fY = tag->getParam("Y", "0").toUint();
    fWidth = tag->getParam("width", "0").toUint();
    fHeight = tag->getParam("height", "0").toUint();
}

void pfGUISkin::pfSRect::empty() {
    fX = 0;
    fY = 0;
    fWidth = 0;
    fHeight = 0;
}


/* pfGUISkin */
pfGUISkin::pfGUISkin() { }
pfGUISkin::~pfGUISkin() { }

IMPLEMENT_CREATABLE(pfGUISkin, kGUISkin, hsKeyedObject)

void pfGUISkin::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fItemMargin = S->readShort();
    fBorderMargin = S->readShort();
    int i, count = S->readInt();
    for (i=0; i<count; i++)
        fElements[i].read(S);
    for (; i<14; i++)
        fElements[i].empty();

    fTexture = mgr->readKey(S);
}

void pfGUISkin::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeShort(fItemMargin);
    S->writeShort(fBorderMargin);
    S->writeInt(14);
    for (int i=0; i<14; i++)
        fElements[i].write(S);

    mgr->writeKey(S, fTexture);
}

void pfGUISkin::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SkinParams");
    prc->writeParam("ItemMargin", fItemMargin);
    prc->writeParam("BorderMargin", fBorderMargin);
    prc->endTag(true);

    prc->writeSimpleTag("Elements");
    for (int i=0; i<14; i++)
        fElements[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Texture");
    fTexture->prcWrite(prc);
    prc->closeTag();
}

void pfGUISkin::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SkinParams") {
        fItemMargin = tag->getParam("ItemMargin", "0").toUint();
        fBorderMargin = tag->getParam("BorderMargin", "0").toUint();
    } else if (tag->getName() == "Elements") {
        size_t nElements = tag->countChildren();
        if (nElements > 14)
            throw pfPrcParseException(__FILE__, __LINE__, "Too many elements");
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<nElements; i++) {
            fElements[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Texture") {
        if (tag->hasChildren())
            fTexture = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
