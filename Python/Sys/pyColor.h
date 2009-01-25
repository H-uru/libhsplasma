#ifndef _PYCOLOR_H

extern "C" {

typedef struct {
    PyObject_HEAD
    struct hsColorRGBA* fThis;
} pyColorRGBA;

typedef struct {
    PyObject_HEAD
    struct hsColor32* fThis;
} pyColor32;

extern PyTypeObject pyColorRGBA_Type;
PyObject* Init_pyColorRGBA_Type();
int pyColorRGBA_Check(PyObject* obj);
PyObject* pyColorRGBA_FromColorRGBA(const struct hsColorRGBA& color);

extern PyTypeObject pyColor32_Type;
PyObject* Init_pyColor32_Type();
int pyColor32_Check(PyObject* obj);
PyObject* pyColor32_FromColor32(const struct hsColor32& color);

}

#endif
