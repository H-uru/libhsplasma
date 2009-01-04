#ifndef _PYGMATSTATE_H
#define _PYGMATSTATE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsGMatState* fThis;
} pyGMatState;

extern PyTypeObject pyGMatState_Type;
PyObject* Init_pyGMatState_Type();
PyObject* pyGMatState_FromGMatState(class hsGMatState& state);

}

#endif
