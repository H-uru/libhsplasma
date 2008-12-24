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

typedef struct {
    PyObject_HEAD
    class plMobileOccluder* fThis;
    bool fPyOwned;
} pyMobileOccluder;

extern PyTypeObject pyCullPoly_Type;
PyObject* Init_pyCullPoly_Type();
int pyCullPoly_Check(PyObject* obj);
PyObject* pyCullPoly_FromCullPoly(const plCullPoly& poly);

extern PyTypeObject pyOccluder_Type;
PyObject* Init_pyOccluder_Type();
int pyOccluder_Check(PyObject* obj);
PyObject* pyOccluder_FromOccluder(class plOccluder* obj);

extern PyTypeObject pyMobileOccluder_Type;
PyObject* Init_pyMobileOccluder_Type();
int pyMobileOccluder_Check(PyObject* obj);
PyObject* pyMobileOccluder_FromMobileOccluder(class plMobileOccluder* obj);

}

#endif
