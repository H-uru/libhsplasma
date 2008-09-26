#ifndef _PYPHYSICAL_H
#define _PYPHYSICAL_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plPhysical* fThis;
    bool fPyOwned;
} pyPhysical;

typedef struct {
    PyObject_HEAD
    class plGenericPhysical* fThis;
    bool fPyOwned;
} pyGenericPhysical;

extern PyTypeObject pySimDefs_Type;
PyObject* Init_pySimDefs_Type();

extern PyTypeObject pyPhysical_Type;
PyObject* Init_pyPhysical_Type();
int pyPhysical_Check(PyObject* obj);
PyObject* pyPhysical_FromPhysical(class plPhysical* phys);

extern PyTypeObject pyGenericPhysical_Type;
PyObject* Init_pyGenericPhysical_Type();
int pyGenericPhysical_Check(PyObject* obj);
PyObject* pyGenericPhysical_FromGenericPhysical(class plGenericPhysical* phys);

}

#endif
