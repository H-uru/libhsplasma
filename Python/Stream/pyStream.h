#ifndef _PYSTREAM_H
#define _PYSTREAM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsStream* fThis;
} pyStream;

typedef struct {
    PyObject_HEAD
    class hsFileStream* fThis;
} pyFileStream;

typedef struct {
    PyObject_HEAD
    class plEncryptedStream* fThis;
} pyEncryptedStream;


extern PyTypeObject pyStream_Type;
PyObject* Init_pyStream_Type();
int pyStream_Check(PyObject* obj);

extern PyTypeObject pyFileStream_Type;
PyObject* Init_pyFileStream_Type();

extern PyTypeObject pyEncryptedStream_Type;
PyObject* Init_pyEncryptedStream_Type();

}

#endif
