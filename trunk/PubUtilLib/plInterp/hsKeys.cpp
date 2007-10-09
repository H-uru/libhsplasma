#include "hsKeys.h"

/* hsKeyFrame */
hsKeyFrame::hsKeyFrame() { }
hsKeyFrame::~hsKeyFrame() { }


/* hsPoint3Key */
void hsPoint3Key::read(hsStream* S) {
    fFrame = S->readShort();
    fValue.read(S);
}

void hsPoint3Key::write(hsStream* S) {
    S->writeShort(fFrame);
    fValue.write(S);
}

void hsPoint3Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsPoint3Key");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}


/* hsBezPoint3Key */
void hsBezPoint3Key::read(hsStream* S) {
    fFrame = S->readShort();
    fInTan.read(S);
    fOutTan.read(S);
    fValue.read(S);
}

void hsBezPoint3Key::write(hsStream* S) {
    S->writeShort(fFrame);
    fInTan.write(S);
    fOutTan.write(S);
    fValue.write(S);
}

void hsBezPoint3Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezPoint3Key");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
      prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}


/* hsScalarKey */
void hsScalarKey::read(hsStream* S) {
    fFrame = S->readShort();
    fValue = S->readFloat();
}

void hsScalarKey::write(hsStream* S) {
    S->writeShort(fFrame);
    S->writeFloat(fValue);
}

void hsScalarKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsScalarKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("Value", fValue);
    prc->endTag(true);
}


/* hsBezScalarKey */
void hsBezScalarKey::read(hsStream* S) {
    fFrame = S->readShort();
    fInTan = S->readFloat();
    fOutTan = S->readFloat();
    fValue = S->readFloat();
}

void hsBezScalarKey::write(hsStream* S) {
    S->writeShort(fFrame);
    S->writeFloat(fInTan);
    S->writeFloat(fOutTan);
    S->writeFloat(fValue);
}

void hsBezScalarKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezScalarKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("Value", fValue);
    prc->writeParam("InTan", fInTan);
    prc->writeParam("OutTan", fOutTan);
    prc->endTag(true);
}


/* hsScaleValue */
void hsScaleValue::read(hsStream* S) {
    fS.read(S);
    fQ.read(S);
}

void hsScaleValue::write(hsStream* S) {
    fS.write(S);
    fQ.write(S);
}

void hsScaleValue::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("hsScaleValue");
    fS.prcWrite(prc);
    fQ.prcWrite(prc);
    prc->closeTag();
}


/* hsScaleKey */
void hsScaleKey::read(hsStream* S) {
    fFrame = S->readShort();
    fValue.read(S);
}

void hsScaleKey::write(hsStream* S) {
    S->writeShort(fFrame);
    fValue.write(S);
}

void hsScaleKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsScaleKey");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}


/* hsBezScaleKey */
void hsBezScaleKey::read(hsStream* S) {
    fFrame = S->readShort();
    fInTan.read(S);
    fOutTan.read(S);
    fValue.read(S);
}

void hsBezScaleKey::write(hsStream* S) {
    S->writeShort(fFrame);
    fInTan.write(S);
    fOutTan.write(S);
    fValue.write(S);
}

void hsBezScaleKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezScaleKey");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
      prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}


/* hsQuatKey */
void hsQuatKey::read(hsStream* S) {
    fFrame = S->readShort();
    fValue.read(S);
}

void hsQuatKey::write(hsStream* S) {
    S->writeShort(fFrame);
    fValue.write(S);
}

void hsQuatKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsQuatKey");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}


/* hsCompressedQuatKey32 */
void hsCompressedQuatKey32::read(hsStream* S) {
    fFrame = S->readShort();
    fData = S->readInt();
}

void hsCompressedQuatKey32::write(hsStream* S) {
    S->writeShort(fFrame);
    S->writeInt(fData);
}

void hsCompressedQuatKey32::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsCompressedQuatKey32");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("Data", fData);
    prc->endTag(true);
}


/* hsCompressedQuatKey64 */
void hsCompressedQuatKey64::read(hsStream* S) {
    fFrame = S->readShort();
    fData[0] = S->readInt();
    fData[1] = S->readInt();
}

void hsCompressedQuatKey64::write(hsStream* S) {
    S->writeShort(fFrame);
    S->writeInt(fData[0]);
    S->writeInt(fData[1]);
}

void hsCompressedQuatKey64::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsCompressedQuatKey64");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("DataHi", fData[0]);
    prc->writeParam("DataLo", fData[1]);
    prc->endTag(true);
}


/* hsG3DSMaxKeyFrame */
void hsG3DSMaxKeyFrame::read(hsStream* S) {
    fFrame = S->readShort();
    fParts.read(S);
}

void hsG3DSMaxKeyFrame::write(hsStream* S) {
    S->writeShort(fFrame);
    fParts.write(S);
}

void hsG3DSMaxKeyFrame::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsG3DSMaxKeyFrame");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fParts.prcWrite(prc);
    prc->closeTag();
}


/* hsMatrix33Key */
void hsMatrix33Key::read(hsStream* S) {
    fFrame = S->readShort();
    fValue.read(S);
}

void hsMatrix33Key::write(hsStream* S) {
    S->writeShort(fFrame);
    fValue.write(S);
}

void hsMatrix33Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsMatrix33Key");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}


/* hsMatrix44Key */
void hsMatrix44Key::read(hsStream* S) {
    fFrame = S->readShort();
    fValue.read(S);
}

void hsMatrix44Key::write(hsStream* S) {
    S->writeShort(fFrame);
    fValue.write(S);
}

void hsMatrix44Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsMatrix44Key");
    prc->writeParam("Frame", fFrame);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}
