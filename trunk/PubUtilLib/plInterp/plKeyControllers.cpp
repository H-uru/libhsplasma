#include "plKeyControllers.h"

/* plEaseController */
plEaseController::plEaseController() : fNull(true) { }
plEaseController::~plEaseController() { }

IMPLEMENT_CREATABLE(plEaseController, kEaseController, plLeafController)

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

void plEaseController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

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

IMPLEMENT_CREATABLE(plMatrix33Controller, kMatrix33Controller, plLeafController)

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

void plMatrix33Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].prcWrite(prc);
    prc->closeTag();
}


/* plMatrix44Controller */
plMatrix44Controller::plMatrix44Controller() { }
plMatrix44Controller::~plMatrix44Controller() { }

IMPLEMENT_CREATABLE(plMatrix44Controller, kMatrix44Controller, plLeafController)

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

void plMatrix44Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].prcWrite(prc);
    prc->closeTag();
}


/* plPoint3Controller */
plPoint3Controller::plPoint3Controller() : fNull(true) { }
plPoint3Controller::~plPoint3Controller() { }

IMPLEMENT_CREATABLE(plPoint3Controller, kPoint3Controller, plLeafController)

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

void plPoint3Controller::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].prcWrite(prc);
    prc->closeTag();
}


/* plQuatController */
plQuatController::plQuatController() { }
plQuatController::~plQuatController() { }

IMPLEMENT_CREATABLE(plQuatController, kQuatController, plLeafController)

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

void plQuatController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].IPrcWrite(prc);
    prc->closeTag();
}


/* plScalarController */
plScalarController::plScalarController() : fNull(true) { }
plScalarController::~plScalarController() { }

IMPLEMENT_CREATABLE(plScalarController, kScalarController, plLeafController)

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

void plScalarController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].prcWrite(prc);
    prc->closeTag();
}


/* plScaleValueController */
plScaleValueController::plScaleValueController() { }
plScaleValueController::~plScaleValueController() { }

IMPLEMENT_CREATABLE(plScaleValueController, kScaleValueController, plLeafController)

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

void plScaleValueController::IPrcWrite(pfPrcHelper* prc) {
    plLeafController::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i].prcWrite(prc);
    prc->closeTag();
}
