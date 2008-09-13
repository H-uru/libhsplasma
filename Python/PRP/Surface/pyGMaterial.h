#ifndef _PYGMATERIAL_H
#define _PYGMATERIAL_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsGMaterial* fThis;
    bool fPyOwned;
} pyGMaterial;

extern PyTypeObject pyGMaterial_Type;
PyObject* Init_pyGMaterial_Type();
int pyGMaterial_Check(PyObject* obj);
PyObject* pyGMaterial_FromGMaterial(class hsGMaterial* matl);

}

#endif
