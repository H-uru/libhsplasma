#ifndef _PYBITMAP_H
#define _PYBITMAP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plBitmap* fThis;
    bool fPyOwned;
} pyBitmap;

typedef struct {
    PyObject_HEAD
    class plMipmap* fThis;
    bool fPyOwned;
} pyMipmap;

extern PyTypeObject pyBitmap_Type;
PyObject* Init_pyBitmap_Type();
int pyBitmap_Check(PyObject* obj);
PyObject* pyBitmap_FromBitmap(class plBitmap* img);

extern PyTypeObject pyMipmap_Type;
PyObject* Init_pyMipmap_Type();
int pyMipmap_Check(PyObject* obj);
PyObject* pyMipmap_FromMipmap(class plMipmap* img);

}

#endif
