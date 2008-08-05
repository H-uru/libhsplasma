#ifndef _PYSCENEOBJECT_H
#define _PYSCENEOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSceneObject* fThis;
    bool fPyOwned;
} pySceneObject;

extern PyTypeObject pySceneObject_Type;
PyObject* Init_pySceneObject_Type();
int pySceneObject_Check(PyObject* obj);
PyObject* pySceneObject_FromSceneObject(class plSceneObject* obj);

}

#endif
