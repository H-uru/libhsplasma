#include "UruKeys.h"

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

