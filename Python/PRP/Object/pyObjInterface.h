#ifndef _PYOBJINTERFACE_H
#define _PYOBJINTERFACE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plObjInterface* fThis;
    bool fPyOwned;
} pyObjInterface;

typedef struct {
    PyObject_HEAD
    class plAudioInterface* fThis;
    bool fPyOwned;
} pyAudioInterface;

typedef struct {
    PyObject_HEAD
    class plCoordinateInterface* fThis;
    bool fPyOwned;
} pyCoordinateInterface;

typedef struct {
    PyObject_HEAD
    class plDrawInterface* fThis;
    bool fPyOwned;
} pyDrawInterface;

typedef struct {
    PyObject_HEAD
    class plSimulationInterface* fThis;
    bool fPyOwned;
} pySimulationInterface;

extern PyTypeObject pyObjInterface_Type;
PyObject* Init_pyObjInterface_Type();
int pyObjInterface_Check(PyObject* obj);
PyObject* pyObjInterface_FromObjInterface(class plObjInterface* obj);

extern PyTypeObject pyAudioInterface_Type;
PyObject* Init_pyAudioInterface_Type();
int pyAudioInterface_Check(PyObject* obj);
PyObject* pyAudioInterface_FromAudioInterface(class plAudioInterface* obj);

extern PyTypeObject pyCoordinateInterface_Type;
PyObject* Init_pyCoordinateInterface_Type();
int pyCoordinateInterface_Check(PyObject* obj);
PyObject* pyCoordinateInterface_FromCoordinateInterface(class plCoordinateInterface* obj);

extern PyTypeObject pyDrawInterface_Type;
PyObject* Init_pyDrawInterface_Type();
int pyDrawInterface_Check(PyObject* obj);
PyObject* pyDrawInterface_FromDrawInterface(class plDrawInterface* obj);

extern PyTypeObject pySimulationInterface_Type;
PyObject* Init_pySimulationInterface_Type();
int pySimulationInterface_Check(PyObject* obj);
PyObject* pySimulationInterface_FromSimulationInterface(class plSimulationInterface* obj);

}

#endif
