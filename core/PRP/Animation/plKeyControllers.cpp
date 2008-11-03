#include "plKeyControllers.h"

/* plEaseController */
plEaseController::plEaseController() { }
plEaseController::~plEaseController() { }

IMPLEMENT_CREATABLE(plEaseController, kEaseController, plLeafController)


/* plMatrix33Controller */
plMatrix33Controller::plMatrix33Controller() { }
plMatrix33Controller::~plMatrix33Controller() { }

IMPLEMENT_CREATABLE(plMatrix33Controller, kMatrix33Controller, plLeafController)


/* plMatrix44Controller */
plMatrix44Controller::plMatrix44Controller() { }
plMatrix44Controller::~plMatrix44Controller() { }

IMPLEMENT_CREATABLE(plMatrix44Controller, kMatrix44Controller, plLeafController)


/* plPoint3Controller */
plPoint3Controller::plPoint3Controller() { }
plPoint3Controller::~plPoint3Controller() { }

IMPLEMENT_CREATABLE(plPoint3Controller, kPoint3Controller, plLeafController)


/* plQuatController */
plQuatController::plQuatController() { }
plQuatController::~plQuatController() { }

IMPLEMENT_CREATABLE(plQuatController, kQuatController, plLeafController)


/* plScalarController */
plScalarController::plScalarController() { }
plScalarController::~plScalarController() { }

IMPLEMENT_CREATABLE(plScalarController, kScalarController, plLeafController)


/* plScaleValueController */
plScaleValueController::plScaleValueController() { }
plScaleValueController::~plScaleValueController() { }

IMPLEMENT_CREATABLE(plScaleValueController, kScaleValueController, plLeafController)
