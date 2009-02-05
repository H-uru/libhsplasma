#ifndef _PYAUDIBLE_H
#define _PYAUDIBLE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAudible* fThis;
    bool fPyOwned;
} pyAudible;

typedef struct {
    PyObject_HEAD
    class plAudibleNull* fThis;
    bool fPyOwned;
} pyAudibleNull;

typedef struct {
    PyObject_HEAD
    class plWinAudible* fThis;
    bool fPyOwned;
} pyWinAudible;

typedef struct {
    PyObject_HEAD
    class pl2WayWinAudible* fThis;
    bool fPyOwned;
} py2WayWinAudible;

extern PyTypeObject pyAudible_Type;
PyObject* Init_pyAudible_Type();
int pyAudible_Check(PyObject* obj);
PyObject* pyAudible_FromAudible(class plAudible* obj);

extern PyTypeObject pyAudibleNull_Type;
PyObject* Init_pyAudibleNull_Type();
int pyAudibleNull_Check(PyObject* obj);
PyObject* pyAudibleNull_FromAudibleNull(class plAudibleNull* obj);

extern PyTypeObject pyWinAudible_Type;
PyObject* Init_pyWinAudible_Type();
int pyWinAudible_Check(PyObject* obj);
PyObject* pyWinAudible_FromWinAudible(class plWinAudible* obj);

extern PyTypeObject py2WayWinAudible_Type;
PyObject* Init_py2WayWinAudible_Type();
int py2WayWinAudible_Check(PyObject* obj);
PyObject* py2WayWinAudible_From2WayWinAudible(class pl2WayWinAudible* obj);

}

#endif
