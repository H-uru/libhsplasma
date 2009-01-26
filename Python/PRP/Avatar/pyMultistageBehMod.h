#ifndef _PYMULTISTAGEBEHMOD_H
#define _PYMULTISTAGEBEHMOD_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plMultistageBehMod* fThis;
    bool fPyOwned;
} pyMultistageBehMod;

typedef struct {
    PyObject_HEAD
    class plAnimStage* fThis;
    bool fPyOwned;
} pyAnimStage;

extern PyTypeObject pyMultistageBehMod_Type;
PyObject* Init_pyMultistageBehMod_Type();
int pyMultistageBehMod_Check(PyObject* obj);
PyObject* pyMultistageBehMod_FromMultistageBehMod(class plMultistageBehMod* mod);

extern PyTypeObject pyAnimStage_Type;
PyObject* Init_pyAnimStage_Type();
int pyAnimStage_Check(PyObject* obj);
PyObject* pyAnimStage_FromAnimStage(class plAnimStage* obj);

}

#endif
