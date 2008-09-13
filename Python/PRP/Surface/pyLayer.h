#ifndef _PYLAYER_H
#define _PYLAYER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerInterface* fThis;
    bool fPyOwned;
} pyLayerInterface;

typedef struct {
    PyObject_HEAD
    class plLayer* fThis;
    bool fPyOwned;
} pyLayer;

typedef struct {
    PyObject_HEAD
    class plLayerDepth* fThis;
    bool fPyOwned;
} pyLayerDepth;

extern PyTypeObject pyLayerInterface_Type;
PyObject* Init_pyLayerInterface_Type();
int pyLayerInterface_Check(PyObject* obj);
PyObject* pyLayerInterface_FromLayerInterface(class plLayerInterface* layer);

extern PyTypeObject pyLayer_Type;
PyObject* Init_pyLayer_Type();
int pyLayer_Check(PyObject* obj);
PyObject* pyLayer_FromLayer(class plLayer* layer);

extern PyTypeObject pyLayerDepth_Type;
PyObject* Init_pyLayerDepth_Type();
int pyLayerDepth_Check(PyObject* obj);
PyObject* pyLayerDepth_FromLayerDepth(class plLayerDepth* layer);

}

#endif
