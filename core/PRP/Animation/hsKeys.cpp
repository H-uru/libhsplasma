#include "hsKeys.h"
#include <cmath>

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

void hsKeyFrame::read(hsStream* S, unsigned int type) {
    fType = type;
    if (S->getVer() <= pvPots) {
        unsigned int flags = S->readInt();
        fFrame = S->readInt();
        fFrameTime = S->readFloat();

        if ((fType == kPoint3KeyFrame || fType == kScalarKeyFrame ||
            fType == kScaleKeyFrame) && ((flags & kBezController) != 0))
            fType++;    //  Use Bezier version
    } else if (S->getVer() >= pvEoa) {
        setFrame(S->readFloat());
    } else {
        setFrame((unsigned int)S->readShort());
    }
}

void hsKeyFrame::write(hsStream* S) {
    if (S->getVer() <= pvPots) {
        if (fType == kBezPoint3KeyFrame || fType == kBezScalarKeyFrame ||
            fType == kBezScaleKeyFrame)
            S->writeInt(kBezController);
        else
            S->writeInt(0);
        S->writeInt(fFrame);
        S->writeFloat(fFrameTime);
    } else if (S->getVer() >= pvEoa) {
        S->writeFloat(fFrameTime);
    } else {
        S->writeShort(fFrame);
    }
}

unsigned int hsKeyFrame::getType() const { return fType; }
unsigned int hsKeyFrame::getFrame() const { return fFrame; }
float hsKeyFrame::getFrameTime() const { return fFrameTime; }

void hsKeyFrame::setType(unsigned int type) { fType = type; }

void hsKeyFrame::setFrame(unsigned int frame) {
    fFrame = frame;
    fFrameTime = fFrame / 30.0f;
}

void hsKeyFrame::setFrame(float frame) {
    fFrameTime = frame;
    fFrame = (unsigned int)floor((fFrameTime * 30.0f) + 0.5f);
}


/* hsPoint3Key */
void hsPoint3Key::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
    if (fType == kBezPoint3KeyFrame) {
        fInTan.read(S);
        fOutTan.read(S);
    }
    fValue.read(S);
}

void hsPoint3Key::write(hsStream* S) {
    hsKeyFrame::write(S);
    if (fType == kBezPoint3KeyFrame) {
        fInTan.write(S);
        fOutTan.write(S);
    }
    fValue.write(S);
}

void hsPoint3Key::prcWrite(pfPrcHelper* prc) {
    if (fType == kBezPoint3KeyFrame)
        prc->startTag("hsBezPoint3Key");
    else
        prc->startTag("hsPoint3Key");

    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();

    prc->writeSimpleTag("Value");
    fValue.prcWrite(prc);
    prc->closeTag();
    if (fType == kBezPoint3KeyFrame) {
        prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
        prc->closeTag();
    }

    prc->closeTag();
}

void hsPoint3Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() == "hsBezPoint3Key")
        fType = kBezPoint3KeyFrame;
    else if (tag->getName() == "hsPoint3Key")
        fType = kPoint3KeyFrame;
    else
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


/* hsScalarKey */
void hsScalarKey::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
    if (fType == kBezScalarKeyFrame) {
        fInTan = S->readFloat();
        fOutTan = S->readFloat();
    }
    fValue = S->readFloat();
}

void hsScalarKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    if (fType == kBezScalarKeyFrame) {
        S->writeFloat(fInTan);
        S->writeFloat(fOutTan);
    }
    S->writeFloat(fValue);
}

void hsScalarKey::prcWrite(pfPrcHelper* prc) {
    if (fType == kBezScalarKeyFrame)
        prc->startTag("hsBezScalarKey");
    else
        prc->startTag("hsScalarKey");

    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->writeParam("Value", fValue);
    if (fType == kBezScalarKeyFrame) {
        prc->writeParam("InTan", fInTan);
        prc->writeParam("OutTan", fOutTan);
    }
    prc->endTag(true);
}

void hsScalarKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() == "hsBezScalarKey")
        fType = kBezScalarKeyFrame;
    else if (tag->getName() == "hsScalarKey")
        fType = kScalarKeyFrame;
    else
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    fValue = tag->getParam("Value", "0").toFloat();
    fInTan = tag->getParam("InTan", "0").toFloat();
    fOutTan = tag->getParam("OutTan", "0").toFloat();
}


/* hsScaleKey */
void hsScaleKey::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
    if (fType == kBezScaleKeyFrame) {
        fInTan.read(S);
        fOutTan.read(S);
    }
    fS.read(S);
    fQ.read(S);
}

void hsScaleKey::write(hsStream* S) {
    hsKeyFrame::write(S);
    if (fType == kBezScaleKeyFrame) {
        fInTan.write(S);
        fOutTan.write(S);
    }
    fS.write(S);
    fQ.write(S);
}

void hsScaleKey::prcWrite(pfPrcHelper* prc) {
    if (fType == kBezScaleKeyFrame)
        prc->startTag("hsBezScaleKey");
    else
        prc->startTag("hsScaleKey");

    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();

    prc->writeSimpleTag("Value");
    fS.prcWrite(prc);
    fQ.prcWrite(prc);
    prc->closeTag();
    if (fType == kBezScaleKeyFrame) {
        prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
        prc->closeTag();
    }

    prc->closeTag();
}

void hsScaleKey::prcParse(const pfPrcTag* tag) {
    if (tag->getName() == "hsBezScaleKey")
        fType = kBezScaleKeyFrame;
    else if (tag->getName() == "hsScaleKey")
        fType = kScaleKeyFrame;
    else
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Value") {
            const pfPrcTag* subchild = child->getFirstChild();
            while (subchild != NULL) {
                if (subchild->getName() == "hsVector3") {
                    if (subchild->hasChildren())
                        fS.prcParse(subchild->getFirstChild());
                } else if (subchild->getName() == "hsQuat") {
                    if (subchild->hasChildren())
                        fQ.prcParse(subchild->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                }
                subchild = subchild->getNextSibling();
            }
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


/* hsQuatKey */
void hsQuatKey::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
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
    fType = kQuatKeyFrame;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}


/* hsCompressedQuatKey32 */
const float hsCompressedQuatKey32::kOneOverRootTwo = 1 / sqrt(2.0f);
const float hsCompressedQuatKey32::k10BitScaleRange = kOneOverRootTwo * 0x3FF;

hsQuat hsCompressedQuatKey32::getQuat() const {
    hsQuat quat;
    switch (fData >> 30) {
    case kCompQuatNukeX:
        quat.Y = ((unsigned)((fData >> 20) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)((fData >> 10) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)((fData >>  0) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.X = sqrt(1.0f - (quat.Y * quat.Y) - (quat.Z * quat.Z) - (quat.W * quat.W));
        break;
    case kCompQuatNukeY:
        quat.X = ((unsigned)((fData >> 20) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)((fData >> 10) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)((fData >>  0) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Y = sqrt(1.0f - (quat.X * quat.X) - (quat.Z * quat.Z) - (quat.W * quat.W));
        break;
    case kCompQuatNukeZ:
        quat.X = ((unsigned)((fData >> 20) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Y = ((unsigned)((fData >> 10) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)((fData >>  0) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Z = sqrt(1.0f - (quat.X * quat.X) - (quat.Y * quat.Y) - (quat.W * quat.W));
        break;
    default:
        quat.X = ((unsigned)((fData >> 20) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Y = ((unsigned)((fData >> 10) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)((fData >>  0) & 0x3FF) / k10BitScaleRange) - kOneOverRootTwo;
        quat.W = sqrt(1.0f - (quat.X * quat.X) - (quat.Y * quat.Y) - (quat.Z * quat.Z));
        break;
    }
    return quat;
}

void hsCompressedQuatKey32::setQuat(const hsQuat& quat, unsigned char format) {
    fData = (format & 0x3) << 30;
    switch (format & 0x3) {
    case kCompQuatNukeX:
        fData |= ((unsigned)((quat.Y + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 20;
        fData |= ((unsigned)((quat.Z + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 10;
        fData |= ((unsigned)((quat.W + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) <<  0;
        break;
    case kCompQuatNukeY:
        fData |= ((unsigned)((quat.X + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 20;
        fData |= ((unsigned)((quat.Z + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 10;
        fData |= ((unsigned)((quat.W + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) <<  0;
        break;
    case kCompQuatNukeZ:
        fData |= ((unsigned)((quat.X + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 20;
        fData |= ((unsigned)((quat.Y + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 10;
        fData |= ((unsigned)((quat.W + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) <<  0;
        break;
    default:
        fData |= ((unsigned)((quat.X + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 20;
        fData |= ((unsigned)((quat.Y + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) << 10;
        fData |= ((unsigned)((quat.Z + kOneOverRootTwo) * k10BitScaleRange) & 0x3FF) <<  0;
        break;
    }
}

void hsCompressedQuatKey32::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
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
    prc->writeParam("Format", fData >> 30);
    prc->endTag();
    getQuat().prcWrite(prc);
    prc->closeTag();
}

void hsCompressedQuatKey32::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsCompressedQuatKey32")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fType = kCompressedQuatKeyFrame32;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    unsigned char fmt = tag->getParam("Format", "0").toUint();

    if (tag->hasChildren()) {
        hsQuat q;
        q.prcParse(tag->getFirstChild());
        setQuat(q, fmt);
    }
}


/* hsCompressedQuatKey64 */
const float hsCompressedQuatKey64::kOneOverRootTwo = 1 / sqrt(2.0f);
const float hsCompressedQuatKey64::k20BitScaleRange = kOneOverRootTwo * 0xFFFFF;
const float hsCompressedQuatKey64::k21BitScaleRange = kOneOverRootTwo * 0x1FFFFF;

hsQuat hsCompressedQuatKey64::getQuat() const {
    hsQuat quat;
    switch (fData[0] >> 30) {
    case kCompQuatNukeX:
        quat.Y = ((unsigned)((fData[0] >> 10) & 0xFFFFF) / k20BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)(((fData[0] & 0x3FF) << 11) | (fData[1] >> 21)) / k20BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)(fData[1] & 0x1FFFFF) / k21BitScaleRange) - kOneOverRootTwo;
        quat.X = sqrt(1.0f - (quat.Y * quat.Y) - (quat.Z * quat.Z) - (quat.W * quat.W));
        break;
    case kCompQuatNukeY:
        quat.X = ((unsigned)((fData[0] >> 10) & 0xFFFFF) / k20BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)(((fData[0] & 0x3FF) << 11) | (fData[1] >> 21)) / k20BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)(fData[1] & 0x1FFFFF) / k21BitScaleRange) - kOneOverRootTwo;
        quat.Y = sqrt(1.0f - (quat.X * quat.X) - (quat.Z * quat.Z) - (quat.W * quat.W));
        break;
    case kCompQuatNukeZ:
        quat.X = ((unsigned)((fData[0] >> 10) & 0xFFFFF) / k20BitScaleRange) - kOneOverRootTwo;
        quat.Y = ((unsigned)(((fData[0] & 0x3FF) << 11) | (fData[1] >> 21)) / k20BitScaleRange) - kOneOverRootTwo;
        quat.W = ((unsigned)(fData[1] & 0x1FFFFF) / k21BitScaleRange) - kOneOverRootTwo;
        quat.Z = sqrt(1.0f - (quat.X * quat.X) - (quat.Y * quat.Y) - (quat.W * quat.W));
        break;
    default:
        quat.X = ((unsigned)((fData[0] >> 10) & 0xFFFFF) / k20BitScaleRange) - kOneOverRootTwo;
        quat.Y = ((unsigned)(((fData[0] & 0x3FF) << 11) | (fData[1] >> 21)) / k20BitScaleRange) - kOneOverRootTwo;
        quat.Z = ((unsigned)(fData[1] & 0x1FFFFF) / k21BitScaleRange) - kOneOverRootTwo;
        quat.W = sqrt(1.0f - (quat.X * quat.X) - (quat.Y * quat.Y) - (quat.Z * quat.Z));
        break;
    }
    return quat;
}

void hsCompressedQuatKey64::setQuat(const hsQuat& quat, unsigned char format) {
    fData[0] = (format & 0x3) << 30;
    fData[1] = 0;
    switch (format & 0x3) {
    case kCompQuatNukeX:
        fData[0] |= ((unsigned)((quat.Y + kOneOverRootTwo) * k20BitScaleRange) & 0xFFFFF) << 10;
        fData[0] |= ((unsigned)((quat.Z + kOneOverRootTwo) * k20BitScaleRange) & 0x3FF) >> 11;
        fData[1] |= ((unsigned)((quat.Z + kOneOverRootTwo) * k20BitScaleRange)) << 21;
        fData[1] |= ((unsigned)((quat.W + kOneOverRootTwo) * k21BitScaleRange) & 0x1FFFFF);
        break;
    case kCompQuatNukeY:
        fData[0] |= ((unsigned)((quat.X + kOneOverRootTwo) * k20BitScaleRange) & 0xFFFFF) << 10;
        fData[0] |= ((unsigned)((quat.Z + kOneOverRootTwo) * k20BitScaleRange) & 0x3FF) >> 11;
        fData[1] |= ((unsigned)((quat.Z + kOneOverRootTwo) * k20BitScaleRange)) << 21;
        fData[1] |= ((unsigned)((quat.W + kOneOverRootTwo) * k21BitScaleRange) & 0x1FFFFF);
        break;
    case kCompQuatNukeZ:
        fData[0] |= ((unsigned)((quat.X + kOneOverRootTwo) * k20BitScaleRange) & 0xFFFFF) << 10;
        fData[0] |= ((unsigned)((quat.Y + kOneOverRootTwo) * k20BitScaleRange) & 0x3FF) >> 11;
        fData[1] |= ((unsigned)((quat.Y + kOneOverRootTwo) * k20BitScaleRange)) << 21;
        fData[1] |= ((unsigned)((quat.W + kOneOverRootTwo) * k21BitScaleRange) & 0x1FFFFF);
        break;
    default:
        fData[0] |= ((unsigned)((quat.X + kOneOverRootTwo) * k20BitScaleRange) & 0xFFFFF) << 10;
        fData[0] |= ((unsigned)((quat.Y + kOneOverRootTwo) * k20BitScaleRange) & 0x3FF) >> 11;
        fData[1] |= ((unsigned)((quat.Y + kOneOverRootTwo) * k20BitScaleRange)) << 21;
        fData[1] |= ((unsigned)((quat.Z + kOneOverRootTwo) * k21BitScaleRange) & 0x1FFFFF);
        break;
    }
}

void hsCompressedQuatKey64::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
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
    prc->writeParam("Format", fData[0] >> 30);
    prc->endTag();
    getQuat().prcWrite(prc);
    prc->closeTag();
}

void hsCompressedQuatKey64::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsCompressedQuatKey64")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fType = kCompressedQuatKeyFrame64;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    unsigned char fmt = tag->getParam("Format", "0").toUint();

    if (tag->hasChildren()) {
        hsQuat q;
        q.prcParse(tag->getFirstChild());
        setQuat(q, fmt);
    }
}


/* hsG3DSMaxKeyFrame */
void hsG3DSMaxKeyFrame::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
    fValue.read(S);
}

void hsG3DSMaxKeyFrame::write(hsStream* S) {
    hsKeyFrame::write(S);
    fValue.write(S);
}

void hsG3DSMaxKeyFrame::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsG3DSMaxKeyFrame");
    prc->writeParam("Frame", fFrame);
    prc->writeParam("FrameTime", fFrameTime);
    prc->endTag();
      fValue.prcWrite(prc);
    prc->closeTag();
}

void hsG3DSMaxKeyFrame::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsG3DSMaxKeyFrame")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fType = k3dsMaxKeyFrame;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}


/* hsMatrix33Key */
void hsMatrix33Key::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
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

void hsMatrix33Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix33Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fType = kMatrix33KeyFrame;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();
    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}


/* hsMatrix44Key */
void hsMatrix44Key::read(hsStream* S, unsigned int type) {
    hsKeyFrame::read(S, type);
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

void hsMatrix44Key::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix44Key")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fType = kMatrix44KeyFrame;

    fFrame = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("FrameTime", "0").toFloat();

    if (tag->hasChildren())
        fValue.prcParse(tag->getFirstChild());
}
