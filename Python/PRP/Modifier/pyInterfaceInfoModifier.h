#ifndef _PYINTERFACEINFOMODIFIER_H
#define _PYINTERFACEINFOMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plInterfaceInfoModifier* fThis;
    bool fPyOwned;
} pyInterfaceInfoModifier;

extern PyTypeObject pyInterfaceInfoModifier_Type;
PyObject* Init_pyInterfaceInfoModifier_Type();
int pyInterfaceInfoModifier_Check(PyObject* obj);
PyObject* pyInterfaceInfoModifier_FromInterfaceInfoModifier(class plInterfaceInfoModifier* mod);

}

#endif
