#ifndef _PYVIEWFACEMODIFIER_H
#define _PYVIEWFACEMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plViewFaceModifier* fThis;
    bool fPyOwned;
} pyViewFaceModifier;

extern PyTypeObject pyViewFaceModifier_Type;
PyObject* Init_pyViewFaceModifier_Type();
int pyViewFaceModifier_Check(PyObject* obj);
PyObject* pyViewFaceModifier_FromViewFaceModifier(class plViewFaceModifier* mod);

}

#endif
