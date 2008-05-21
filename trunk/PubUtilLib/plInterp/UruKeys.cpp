#include "UruKeys.h"
#include "hsKeys.h"     // Shortcut, should include everything necessary

/* UruKeyFrame */
UruKeyFrame::UruKeyFrame() : fFlags(0), fFrameNum(-1), fFrameTime(0.0f) { }
UruKeyFrame::~UruKeyFrame() { }

void UruKeyFrame::read(hsStream* S) {
    fFlags = S->readInt();
    fFrameNum = S->readInt();
    fFrameTime = S->readFloat();
}

void UruKeyFrame::write(hsStream* S) {
    S->writeInt(fFlags);
    S->writeInt(fFrameNum);
    S->writeFloat(fFrameTime);
}

void UruKeyFrame::prcWrite(pfPrcHelper* prc) {
    prc->startTag(ClassName());
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Frame", fFrameNum);
    prc->writeParam("Time", fFrameTime);
    prc->endTag();
    IPrcWrite(prc);
    prc->closeTag();
}

void UruKeyFrame::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFlags = tag->getParam("Flags", "0").toUint();
    fFrameNum = tag->getParam("Frame", "0").toUint();
    fFrameTime = tag->getParam("Time", "0").toFloat();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        IPrcParse(child);
        child = child->getNextSibling();
    }
}

UruKeyFrame* UruKeyFrame::toUruKey() {
    return this;
}

hsKeyFrame* UruKeyFrame::toHsKey() {
    return NULL;
}


/* ScalarKeyFrame */
ScalarKeyFrame::ScalarKeyFrame() : fInTan(0.0f), fOutTan(0.0f), fValue(0.0f) { }
ScalarKeyFrame::~ScalarKeyFrame() { }

const char* const ScalarKeyFrame::ClassName() { return "ScalarKeyFrame"; }

void ScalarKeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);

    if (fFlags & kBezController) {
        fInTan = S->readFloat();
        fOutTan = S->readFloat();
    }
    fValue = S->readFloat();
}

void ScalarKeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);

    if (fFlags & kBezController) {
        S->writeFloat(fInTan);
        S->writeFloat(fOutTan);
    }
    S->writeFloat(fValue);
}

void ScalarKeyFrame::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Value", fValue);
    if (fFlags & kBezController) {
        prc->writeParam("InTan", fInTan);
        prc->writeParam("OutTan", fOutTan);
    }
    prc->endTag(true);
}

void ScalarKeyFrame::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Params") {
        fValue = tag->getParam("Value", "0").toFloat();
        fInTan = tag->getParam("InTan", "0").toFloat();
        fOutTan = tag->getParam("OutTan", "0").toFloat();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

UruKeyFrame* ScalarKeyFrame::toUruKey() {
    return this;
}

hsKeyFrame* ScalarKeyFrame::toHsKey() {
    if (fFlags & kBezController) {
        hsBezScalarKey* frm = new hsBezScalarKey();
        frm->fInTan = fInTan;
        frm->fOutTan = fOutTan;
        frm->fFrameTime = fFrameTime;
        frm->fFrame = fFrameNum;
        frm->fValue = fValue;
        return frm;
    } else {
        hsScalarKey* frm = new hsScalarKey();
        frm->fFrameTime = fFrameTime;
        frm->fFrame = fFrameNum;
        frm->fValue = fValue;
        return frm;
    }

    return NULL;
}

/* Point3KeyFrame */
Point3KeyFrame::Point3KeyFrame() { }
Point3KeyFrame::~Point3KeyFrame() { }

const char* const Point3KeyFrame::ClassName() { return "Point3KeyFrame"; }

void Point3KeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);

    if (fFlags & kBezController) {
        fInTan.read(S);
        fOutTan.read(S);
    }
    fValue.read(S);
}

void Point3KeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);

    if (fFlags & kBezController) {
        fInTan.write(S);
        fOutTan.write(S);
    }
    fValue.write(S);
}

void Point3KeyFrame::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Value");
    fValue.prcWrite(prc);
    prc->closeTag();

    if (fFlags & kBezController) {
        prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
        prc->closeTag();
    }
}

void Point3KeyFrame::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Value") {
        if (tag->hasChildren())
            fValue.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "InTan") {
        if (tag->hasChildren())
            fInTan.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "OutTan") {
        if (tag->hasChildren())
            fOutTan.prcParse(tag->getFirstChild());
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

UruKeyFrame* Point3KeyFrame::toUruKey() {
    return this;
}


/* QuatKeyFrame */
QuatKeyFrame::QuatKeyFrame() { }
QuatKeyFrame::~QuatKeyFrame() { }

const char* const QuatKeyFrame::ClassName() { return "QuatKeyFrame"; }

void QuatKeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);
    fValue.read(S);
}

void QuatKeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);
    fValue.write(S);
}

void QuatKeyFrame::IPrcWrite(pfPrcHelper* prc) {
    fValue.prcWrite(prc);
}

void QuatKeyFrame::IPrcParse(const pfPrcTag* tag) {
    fValue.prcParse(tag);
}

UruKeyFrame* QuatKeyFrame::toUruKey() {
    return this;
}


/* Matrix33KeyFrame */
Matrix33KeyFrame::Matrix33KeyFrame() { }
Matrix33KeyFrame::~Matrix33KeyFrame() { }

const char* const Matrix33KeyFrame::ClassName() { return "Matrix33KeyFrame"; }

void Matrix33KeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);
    fValue.read(S);
}

void Matrix33KeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);
    fValue.write(S);
}

void Matrix33KeyFrame::IPrcWrite(pfPrcHelper* prc) {
    fValue.prcWrite(prc);
}

void Matrix33KeyFrame::IPrcParse(const pfPrcTag* tag) {
    fValue.prcParse(tag);
}

UruKeyFrame* Matrix33KeyFrame::toUruKey() {
    return this;
}


/* Matrix44KeyFrame */
Matrix44KeyFrame::Matrix44KeyFrame() { }
Matrix44KeyFrame::~Matrix44KeyFrame() { }

const char* const Matrix44KeyFrame::ClassName() { return "Matrix44KeyFrame"; }

void Matrix44KeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);
    fValue.read(S);
}

void Matrix44KeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);
    fValue.write(S);
}

void Matrix44KeyFrame::IPrcWrite(pfPrcHelper* prc) {
    fValue.prcWrite(prc);
}

void Matrix44KeyFrame::IPrcParse(const pfPrcTag* tag) {
    fValue.prcParse(tag);
}

UruKeyFrame* Matrix44KeyFrame::toUruKey() {
    return this;
}


/* ScaleKeyFrame */
ScaleKeyFrame::ScaleKeyFrame() { }
ScaleKeyFrame::~ScaleKeyFrame() { }

const char* const ScaleKeyFrame::ClassName() { return "ScaleKeyFrame"; }

void ScaleKeyFrame::read(hsStream* S) {
    UruKeyFrame::read(S);

    if (fFlags & kBezController) {
        fInTan.read(S);
        fOutTan.read(S);
    }
    fS.read(S);
    fQ.read(S);
}

void ScaleKeyFrame::write(hsStream* S) {
    UruKeyFrame::write(S);

    if (fFlags & kBezController) {
        fInTan.write(S);
        fOutTan.write(S);
    }
    fS.write(S);
    fQ.write(S);
}

void ScaleKeyFrame::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Value");
    fS.prcWrite(prc);
    fQ.prcWrite(prc);
    prc->closeTag();

    if (fFlags & kBezController) {
        prc->writeSimpleTag("InTan");
        fInTan.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("OutTan");
        fOutTan.prcWrite(prc);
        prc->closeTag();
    }
}

void ScaleKeyFrame::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Value") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "hsVector3") {
                fS.prcParse(child);
            } else if (child->getName() == "hsQuat") {
                fQ.prcParse(child);
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "InTan") {
        if (tag->hasChildren())
            fInTan.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "OutTan") {
        if (tag->hasChildren())
            fOutTan.prcParse(tag->getFirstChild());
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

UruKeyFrame* ScaleKeyFrame::toUruKey() {
    return this;
}
