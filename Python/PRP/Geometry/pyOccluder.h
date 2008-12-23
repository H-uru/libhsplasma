#ifndef _PYOCCLUDER_H
#define _PYOCCLUDER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCullPoly* fThis;
} pyCullPoly;

typedef struct {
    PyObject_HEAD
    class plOccluder* fThis;
    bool fPyOwned;
} pyOccluder;

extern PyTypeObject pyCullPoly_Type;
PyObject* Init_pyCullPoly_Type();
int pyCullPoly_Check(PyObject* obj);
PyObject* pyCullPoly_FromCullPoly(const plCullPoly& node);

extern PyTypeObject pyOccluder_Type;
PyObject* Init_pyOccluder_Type();
int pyOccluder_Check(PyObject* obj);
PyObject* pyOccluder_FromOccluder(class plOccluder* obj);

}

#endif
