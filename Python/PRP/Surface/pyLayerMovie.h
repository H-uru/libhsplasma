#ifndef _PYLAYERMOVIE_H
#define _PYLAYERMOVIE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerMovie* fThis;
    bool fPyOwned;
} pyLayerMovie;

typedef struct {
    PyObject_HEAD
    class plLayerAVI* fThis;
    bool fPyOwned;
} pyLayerAVI;

typedef struct {
    PyObject_HEAD
    class plLayerBink* fThis;
    bool fPyOwned;
} pyLayerBink;

extern PyTypeObject pyLayerMovie_Type;
PyObject* Init_pyLayerMovie_Type();
int pyLayerMovie_Check(PyObject* obj);
PyObject* pyLayerMovie_FromLayerMovie(class plLayerMovie* layer);

extern PyTypeObject pyLayerAVI_Type;
PyObject* Init_pyLayerAVI_Type();
int pyLayerAVI_Check(PyObject* obj);
PyObject* pyLayerAVI_FromLayerAVI(class plLayerAVI* layer);

extern PyTypeObject pyLayerBink_Type;
PyObject* Init_pyLayerBink_Type();
int pyLayerBink_Check(PyObject* obj);
PyObject* pyLayerBink_FromLayerBink(class plLayerBink* layer);

}

#endif
