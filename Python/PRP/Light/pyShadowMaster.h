#ifndef _PYSHADOWMASTER_H
#define _PYSHADOWMASTER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plShadowMaster* fThis;
    bool fPyOwned;
} pyShadowMaster;

typedef struct {
    PyObject_HEAD
    class plPointShadowMaster* fThis;
    bool fPyOwned;
} pyPointShadowMaster;

typedef struct {
    PyObject_HEAD
    class plDirectShadowMaster* fThis;
    bool fPyOwned;
} pyDirectShadowMaster;

extern PyTypeObject pyShadowMaster_Type;
PyObject* Init_pyShadowMaster_Type();
int pyShadowMaster_Check(PyObject* obj);
PyObject* pyShadowMaster_FromShadowMaster(class plShadowMaster* obj);

extern PyTypeObject pyPointShadowMaster_Type;
PyObject* Init_pyPointShadowMaster_Type();
int pyPointShadowMaster_Check(PyObject* obj);
PyObject* pyPointShadowMaster_FromPointShadowMaster(class plPointShadowMaster* obj);

extern PyTypeObject pyDirectShadowMaster_Type;
PyObject* Init_pyDirectShadowMaster_Type();
int pyDirectShadowMaster_Check(PyObject* obj);
PyObject* pyDirectShadowMaster_FromDirectShadowMaster(class plDirectShadowMaster* obj);

}

#endif
