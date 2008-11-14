#ifndef _PYONESHOTMOD_H
#define _PYONESHOTMOD_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plOneShotMod* fThis;
    bool fPyOwned;
} pyOneShotMod;

extern PyTypeObject pyOneShotMod_Type;
PyObject* Init_pyOneShotMod_Type();
int pyOneShotMod_Check(PyObject* obj);
PyObject* pyOneShotMod_FromOneShotMod(class plOneShotMod* mod);

}

#endif
