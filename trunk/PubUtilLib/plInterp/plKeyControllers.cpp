#include "plKeyControllers.h"

/* plEaseController */
plEaseController::plEaseController() { }
plEaseController::~plEaseController() { }

IMPLEMENT_CREATABLE(plEaseController, kEaseController, plLeafController)

void plEaseController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fEaseKeys.setSize(S->readInt());
        for (size_t i=0; i<fEaseKeys.getSize(); i++)
            fEaseKeys[i].read(S);
    } else {
        fEaseKeys.setSize(0);
    }
}

void plEaseController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fEaseKeys.getSize() == 0) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fEaseKeys.getSize());
        for (size_t i=0; i<fEaseKeys.getSize(); i++)
            fEaseKeys[i].write(S);
    }
}

void plEaseController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("EaseKeys");
    for (size_t i=0; i<fEaseKeys.getSize(); i++) {
        fEaseKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plEaseController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "EaseKeys") {
        fEaseKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEaseKeys.getSize(); i++) {
            fEaseKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plMatrix33Controller */
plMatrix33Controller::plMatrix33Controller() { }
plMatrix33Controller::~plMatrix33Controller() { }

IMPLEMENT_CREATABLE(plMatrix33Controller, kMatrix33Controller, plLeafController)

void plMatrix33Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fMatrixKeys.setSize(S->readInt());
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].read(S);
}

void plMatrix33Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fMatrixKeys.getSize());
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].write(S);
}

void plMatrix33Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("MatrixKeys");
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].prcWrite(prc);
    prc->closeTag();
}

void plMatrix33Controller::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MatrixKeys") {
        fMatrixKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMatrixKeys.getSize(); i++) {
            fMatrixKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plMatrix44Controller */
plMatrix44Controller::plMatrix44Controller() { }
plMatrix44Controller::~plMatrix44Controller() { }

IMPLEMENT_CREATABLE(plMatrix44Controller, kMatrix44Controller, plLeafController)

void plMatrix44Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fMatrixKeys.setSize(S->readInt());
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].read(S);
}

void plMatrix44Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fMatrixKeys.getSize());
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].write(S);
}

void plMatrix44Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("MatrixKeys");
    for (size_t i=0; i<fMatrixKeys.getSize(); i++)
        fMatrixKeys[i].prcWrite(prc);
    prc->closeTag();
}

void plMatrix44Controller::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MatrixKeys") {
        fMatrixKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMatrixKeys.getSize(); i++) {
            fMatrixKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plPoint3Controller */
plPoint3Controller::plPoint3Controller() { }
plPoint3Controller::~plPoint3Controller() { }

IMPLEMENT_CREATABLE(plPoint3Controller, kPoint3Controller, plLeafController)

void plPoint3Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fPointKeys.setSize(S->readInt());
        for (size_t i=0; i<fPointKeys.getSize(); i++)
            fPointKeys[i].read(S);
    } else {
        fPointKeys.setSize(0);
    }
}

void plPoint3Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fPointKeys.getSize() == 0) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fPointKeys.getSize());
        for (size_t i=0; i<fPointKeys.getSize(); i++)
            fPointKeys[i].write(S);
    }
}

void plPoint3Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("PointKeys");
    for (size_t i=0; i<fPointKeys.getSize(); i++)
        fPointKeys[i].prcWrite(prc);
    prc->closeTag();
}

void plPoint3Controller::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PointKeys") {
        fPointKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPointKeys.getSize(); i++) {
            fPointKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plQuatController */
plQuatController::plQuatController() { }
plQuatController::~plQuatController() { }

IMPLEMENT_CREATABLE(plQuatController, kQuatController, plLeafController)

void plQuatController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fQuatKeys.setSize(S->readInt());
    for (size_t i=0; i<fQuatKeys.getSize(); i++)
        fQuatKeys[i].read(S);
}

void plQuatController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fQuatKeys.getSize());
    for (size_t i=0; i<fQuatKeys.getSize(); i++)
        fQuatKeys[i].write(S);
}

void plQuatController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("QuatKeys");
    for (size_t i=0; i<fQuatKeys.getSize(); i++)
        fQuatKeys[i].IPrcWrite(prc);
    prc->closeTag();
}

void plQuatController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "QuatKeys") {
        fQuatKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fQuatKeys.getSize(); i++) {
            fQuatKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plScalarController */
plScalarController::plScalarController() { }
plScalarController::~plScalarController() { }

IMPLEMENT_CREATABLE(plScalarController, kScalarController, plLeafController)

void plScalarController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fScalarKeys.setSize(S->readInt());
        for (size_t i=0; i<fScalarKeys.getSize(); i++)
            fScalarKeys[i].read(S);
    } else {
        fScalarKeys.setSize(0);
    }
}

void plScalarController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fScalarKeys.getSize() == 0) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fScalarKeys.getSize());
        for (size_t i=0; i<fScalarKeys.getSize(); i++)
            fScalarKeys[i].write(S);
    }
}

void plScalarController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("ScalarKeys");
    for (size_t i=0; i<fScalarKeys.getSize(); i++)
        fScalarKeys[i].prcWrite(prc);
    prc->closeTag();
}

void plScalarController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ScalarKeys") {
        fScalarKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fScalarKeys.getSize(); i++) {
            fScalarKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}


/* plScaleValueController */
plScaleValueController::plScaleValueController() { }
plScaleValueController::~plScaleValueController() { }

IMPLEMENT_CREATABLE(plScaleValueController, kScaleValueController, plLeafController)

void plScaleValueController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fScaleKeys.setSize(S->readInt());
    for (size_t i=0; i<fScaleKeys.getSize(); i++)
        fScaleKeys[i].read(S);
}

void plScaleValueController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fScaleKeys.getSize());
    for (size_t i=0; i<fScaleKeys.getSize(); i++)
        fScaleKeys[i].write(S);
}

void plScaleValueController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("ScaleKeys");
    for (size_t i=0; i<fScaleKeys.getSize(); i++)
        fScaleKeys[i].prcWrite(prc);
    prc->closeTag();
}

void plScaleValueController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ScaleKeys") {
        fScaleKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fScaleKeys.getSize(); i++) {
            fScaleKeys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plLeafController::IPrcParse(tag, mgr);
    }
}
