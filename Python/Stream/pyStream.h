#ifndef _PYSTREAM_H
#define _PYSTREAM_H

extern "C" {

extern PyTypeObject pyStream_Type;
PyObject* Init_pyStream_Type();

extern PyTypeObject pyFileStream_Type;
PyObject* Init_pyFileStream_Type();

}

#endif
