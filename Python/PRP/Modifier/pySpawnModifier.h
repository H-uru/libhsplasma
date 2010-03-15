#ifndef _PYSPAWNMODIFIER_H
#define _PYSPAWNMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSpawnModifier* fThis;
    bool fPyOwned;
} pySpawnModifier;

extern PyTypeObject pySpawnModifier_Type;
PyObject* Init_pySpawnModifier_Type();
int pySpawnModifier_Check(PyObject* obj);
PyObject* pySpawnModifier_FromSpawnModifier(class plSpawnModifier* mod);

}

#endif
