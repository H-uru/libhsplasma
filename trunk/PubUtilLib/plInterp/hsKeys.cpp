#include "hsKeys.h"
#include "UruKeys.h"

/* hsKeyFrame */
const char* hsKeyFrame::TypeNames[] = {
    "kUnknownKeyFrame", "kPoint3KeyFrame", "kBezPoint3KeyFrame",
    "kScalarKeyFrame", "kBezScalarKeyFrame", "kScaleKeyFrame",
    "kBezScaleKeyFrame", "kQuatKeyFrame", "kCompressedQuatKeyFrame32",
    "kCompressedQuatKeyFrame64", "k3dsMaxKeyFrame", "kMatrix33KeyFrame",
    "kMatrix44KeyFrame"
};

hsKeyFrame::hsKeyFrame() { }
hsKeyFrame::~hsKeyFrame() { }

void hsKeyFrame::read(hsStream* S) {
    if (S->getVer() >= pvEoa)
        fFrameTime = S->readFloat();
    else
        fFrame = S->readShort();
}

void hsKeyFrame::write(hsStream* S) {
    // TODO: Convert between fFrameTime and fFrame...
    if (S->getVer() >= pvEoa)
        S->writeFloat(fFrameTime);
    else
        S->writeShort(fFrame);
}

struct UruKeyFrame* hsKeyFrame::toUruKey() {
    return NULL;
}

hsKeyFrame* hsKeyFrame::toHsKey() {
    return this;
}


/* hsPoint3Key */
void hsPoint3Key::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue.read(S);
}

void hsPoint3Key::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsPoint3Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsPoint3Key");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}

struct UruKeyFrame* hsPoint3Key::toUruKey() {
    Point3KeyFrame* frm = new Point3KeyFrame();
    frm->fFrameNum = fFrame;
    frm->fFrameTime = fFrameTime;
    frm->fValue = fValue;

    return frm;
}

void hsPoint3Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsPoint3Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}

hsKeyFrame* hsPoint3Key::toHsKey() {
    return this;
}

/* hsBezPoint3Key */
void hsBezPoint3Key::read(hsStream* S) {
    hsKeyFrame::read(S);
    fInTan.read(S);
    fOutTan.read(S);
    fValue.read(S);
}

void hsBezPoint3Key::write(hsStream* S) {
    hsKeyFrame::write(S);
    fInTan.write(S);
    fOutTan.write(S);
    fValue.write(S);
}

void hsBezPoint3Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezPoint3Key");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      prc->writeSimpleTag("Value");
        fValue.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}

struct UruKeyFrame* hsBezPoint3Key::toUruKey() {
    Point3KeyFrame* frm = new Point3KeyFrame();
    frm->fFlags = 0x2;
    frm->fFrameNum = fFrame;
    frm->fFrameTime = fFrameTime;
    frm->fValue = fValue;
    frm->fInTan = fInTan;
    frm->fOutTan = fOutTan;

    return frm;
}

void hsBezPoint3Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsBezPoint3Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Value") {
            if (child->hasChildren())
                fValue.prcParse(child->getFirstChild());
        } else if (child->getName() == "InTan") {
            if (child->hasChildren())
                fInTan.prcParse(child->getFirstChild());
        } else if (child->getName() == "OutTan") {
            if (child->hasChildren())
                fOutTan.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

hsKeyFrame* hsBezPoint3Key::toHsKey() {
    return this;
}


/* hsScalarKey */
void hsScalarKey::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue = S->readFloat();
}

void hsScalarKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    S->writeFloat(fValue);
}

void hsScalarKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsScalarKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->writeParam("Value", fValue);
    prc->endTag(true);
}

void hsScalarKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsScalarKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    fValue = tag->getParam("Value", "0").toFloat();
}

hsKeyFrame* hsScalarKey::toHsKey() {
    return this;
}



/* hsBezScalarKey */
void hsBezScalarKey::read(hsStream* S) {
    hsKeyFrame::read(S);
    fInTan = S->readFloat();
    fOutTan = S->readFloat();
    fValue = S->readFloat();
}

void hsBezScalarKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    S->writeFloat(fInTan);
    S->writeFloat(fOutTan);
    S->writeFloat(fValue);
}

void hsBezScalarKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezScalarKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->writeParam("Value", fValue);
    prc->writeParam("InTan", fInTan);
    prc->writeParam("OutTan", fOutTan);
    prc->endTag(true);
}

void hsBezScalarKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsBezPoint3Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    fValue = tag->getParam("Value", "0").toFloat();
    fInTan = tag->getParam("InTan", "0").toFloat();
    fOutTan = tag->getParam("OutTan", "0").toFloat();
}

hsKeyFrame* hsBezScalarKey::toHsKey() {
    return this;
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

void hsScaleValue::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsScaleValue")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "hsVector3") {
            if (child->hasChildren())
                fS.prcParse(child->getFirstChild());
        } else if (child->getName() == "hsQuat") {
            if (child->hasChildren())
                fQ.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

hsKeyFrame* hsScaleValue::toHsKey() {
    return this;
}


/* hsScaleKey */
void hsScaleKey::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue.read(S);
}

void hsScaleKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsScaleKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsScaleKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}

void hsScaleKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsScaleKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();

    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}

hsKeyFrame* hsScaleKey::toHsKey() {
    return this;
}



/* hsBezScaleKey */
void hsBezScaleKey::read(hsStream* S) {
    hsKeyFrame::read(S);
    fInTan.read(S);
    fOutTan.read(S);
    fValue.read(S);
}

void hsBezScaleKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    fInTan.write(S);
    fOutTan.write(S);
    fValue.write(S);
}

void hsBezScaleKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsBezScaleKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      prc->writeSimpleTag("Value");
        fValue.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}

void hsBezScaleKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsBezScaleKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Value") {
            if (child->hasChildren())
                fValue.prcParse(child->getFirstChild());
        } else if (child->getName() == "InTan") {
            if (child->hasChildren())
                fInTan.prcParse(child->getFirstChild());
        } else if (child->getName() == "OutTan") {
            if (child->hasChildren())
                fOutTan.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

hsKeyFrame* hsBezScaleKey::toHsKey() {
    return this;
}

/* hsQuatKey */
void hsQuatKey::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue.read(S);
}

void hsQuatKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsQuatKey::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsQuatKey");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}

void hsQuatKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsQuatKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}

hsKeyFrame* hsQuatKey::toHsKey() {
    return this;
}

struct UruKeyFrame* hsQuatKey::toUruKey() {
    QuatKeyFrame* frm = new QuatKeyFrame();
    frm->fFrameNum = fFrame;
    frm->fFrameTime = fFrameTime;
    frm->fValue = fValue;

    return frm;
}


/* hsCompressedQuatKey32 */
void hsCompressedQuatKey32::read(hsStream* S) {
    hsKeyFrame::read(S);
    fData = S->readInt();
}

void hsCompressedQuatKey32::write(hsStream* S) {
    hsKeyFrame::write(S);
    S->writeInt(fData);
}

void hsCompressedQuatKey32::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsCompressedQuatKey32");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->writeParam("Data", fData);
    prc->endTag(true);
}

void hsCompressedQuatKey32::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsCompressedQuatKey32")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    fData = tag->getParam("Data", "0").toUint();
}

struct UruKeyFrame* hsCompressedQuatKey32::toUruKey() {
    return NULL;
}

hsKeyFrame* hsCompressedQuatKey32::toHsKey() {
    return this;
}


/* hsCompressedQuatKey64 */
void hsCompressedQuatKey64::read(hsStream* S) {
    hsKeyFrame::read(S);
    fData[0] = S->readInt();
    fData[1] = S->readInt();
}

void hsCompressedQuatKey64::write(hsStream* S) {
    hsKeyFrame::write(S);
    S->writeInt(fData[0]);
    S->writeInt(fData[1]);
}

void hsCompressedQuatKey64::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsCompressedQuatKey64");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->writeParam("DataHi", fData[0]);
    prc->writeParam("DataLo", fData[1]);
    prc->endTag(true);
}

void hsCompressedQuatKey64::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsCompressedQuatKey64")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    fData[0] = tag->getParam("DataHi", "0").toUint();
    fData[1] = tag->getParam("DataLo", "0").toUint();
}

hsKeyFrame* hsCompressedQuatKey64::toHsKey() {
    return this;
}

struct UruKeyFrame* hsCompressedQuatKey64::toUruKey() {
    return NULL;
}

/* hsG3DSMaxKeyFrame */
void hsG3DSMaxKeyFrame::read(hsStream* S) {
    hsKeyFrame::read(S);
    fParts.read(S);
}

void hsG3DSMaxKeyFrame::write(hsStream* S) {
    hsKeyFrame::write(S);
    fParts.write(S);
}

void hsG3DSMaxKeyFrame::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsG3DSMaxKeyFrame");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fParts.prcWrite(prc);
    prc->closeTag();
}

void hsG3DSMaxKeyFrame::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsG3DSMaxKeyFrame")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fParts.prcParse(tag->getFirstChild());
}

hsKeyFrame* hsG3DSMaxKeyFrame::toHsKey() {
    return this;
}

struct UruKeyFrame* hsG3DSMaxKeyFrame::toUruKey() {
    return NULL;
}


/* hsMatrix33Key */
void hsMatrix33Key::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue.read(S);
}

void hsMatrix33Key::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsMatrix33Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsMatrix33Key");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}

struct UruKeyFrame* hsMatrix33Key::toUruKey() {
    Matrix33KeyFrame* frm = new Matrix33KeyFrame();
    frm->fFrameNum = fFrame;
    frm->fFrameTime = fFrameTime;
    frm->fValue = fValue;

    return frm;
}

void hsMatrix33Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix33Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}

hsKeyFrame* hsMatrix33Key::toHsKey() {
    return this;
}


/* hsMatrix44Key */
void hsMatrix44Key::read(hsStream* S) {
    hsKeyFrame::read(S);
    fValue.read(S);
}

void hsMatrix44Key::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsMatrix44Key::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsMatrix44Key");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}


struct UruKeyFrame* hsMatrix44Key::toUruKey() {
    Matrix44KeyFrame* frm = new Matrix44KeyFrame();
    frm->fFrameNum = fFrame;
    frm->fFrameTime = fFrameTime;
    frm->fValue = fValue;

    return frm;
}

hsKeyFrame* hsMatrix44Key::toHsKey() {
    return this;
}


void hsMatrix44Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix44Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();

    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}
