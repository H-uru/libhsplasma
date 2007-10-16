#include "plKeyControllers.h"

/* plEaseController */
plEaseController::plEaseController() : fNull(true) { }
plEaseController::~plEaseController() { }

void plEaseController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fNull = false;
        fKeys.setSize(S->readInt());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].read(S);
    } else {
        fNull = true;
    }
}

void plEaseController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fNull) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fKeys.getSize());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].write(S);
    }
}

void plEaseController::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plMatrix33Controller */
plMatrix33Controller::plMatrix33Controller() { }
plMatrix33Controller::~plMatrix33Controller() { }

void plMatrix33Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fKeys.setSize(S->readInt());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].read(S);
}

void plMatrix33Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fKeys.getSize());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].write(S);
}

void plMatrix33Controller::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plMatrix44Controller */
plMatrix44Controller::plMatrix44Controller() { }
plMatrix44Controller::~plMatrix44Controller() { }

void plMatrix44Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fKeys.setSize(S->readInt());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].read(S);
}

void plMatrix44Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fKeys.getSize());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].write(S);
}

void plMatrix44Controller::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plPoint3Controller */
plPoint3Controller::plPoint3Controller() : fNull(true) { }
plPoint3Controller::~plPoint3Controller() { }

void plPoint3Controller::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fNull = false;
        fKeys.setSize(S->readInt());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].read(S);
    } else {
        fNull = true;
    }
}

void plPoint3Controller::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fNull) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fKeys.getSize());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].write(S);
    }
}

void plPoint3Controller::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plQuatController */
plQuatController::plQuatController() { }
plQuatController::~plQuatController() { }

void plQuatController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fKeys.setSize(S->readInt());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].read(S);
}

void plQuatController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fKeys.getSize());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].write(S);
}

void plQuatController::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plScalarController */
plScalarController::plScalarController() : fNull(true) { }
plScalarController::~plScalarController() { }

void plScalarController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    if (S->readInt() != 0) {
        fNull = false;
        fKeys.setSize(S->readInt());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].read(S);
    } else {
        fNull = true;
    }
}

void plScalarController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    if (fNull) {
        S->writeInt(0);
    } else {
        S->writeInt(1);
        S->writeInt(fKeys.getSize());
        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i].write(S);
    }
}

void plScalarController::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


/* plScaleValueController */
plScaleValueController::plScaleValueController() { }
plScaleValueController::~plScaleValueController() { }

void plScaleValueController::read(hsStream* S, plResManager* mgr) {
    plLeafController::read(S, mgr);

    fKeys.setSize(S->readInt());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].read(S);
}

void plScaleValueController::write(hsStream* S, plResManager* mgr) {
    plLeafController::write(S, mgr);

    S->writeInt(fKeys.getSize());
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].write(S);
}

void plScaleValueController::prcWrite(pfPrcHelper* prc) {
    plLeafController::prcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++) {
        fKeys[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}
