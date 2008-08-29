#ifndef _PYDRAWABLESPANS_H
#define _PYDRAWABLESPANS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDISpanIndex* fThis;
} pyDISpanIndex;

typedef struct {
    PyObject_HEAD
    class plDrawable* fThis;
    bool fPyOwned;
} pyDrawable;

typedef struct {
    PyObject_HEAD
    class plDrawableSpans* fThis;
    bool fPyOwned;
} pyDrawableSpans;

extern PyTypeObject pyDISpanIndex_Type;
PyObject* Init_pyDISpanIndex_Type();
int pyDISpanIndex_Check(PyObject* obj);
PyObject* pyDISpanIndex_FromDISpanIndex(const class plDISpanIndex& idx);

extern PyTypeObject pyDrawable_Type;
PyObject* Init_pyDrawable_Type();
int pyDrawable_Check(PyObject* obj);
PyObject* pyDrawable_FromDrawable(class plDrawable* draw);

extern PyTypeObject pyDrawableSpans_Type;
PyObject* Init_pyDrawableSpans_Type();
int pyDrawableSpans_Check(PyObject* obj);
PyObject* pyDrawableSpans_FromDrawableSpans(class plDrawableSpans* draw);

};

#endif
