#ifndef _PYMESSAGE_H
#define _PYMESSAGE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plMessage* fThis;
    bool fPyOwned;
} pyMessage;

extern PyTypeObject pyMessage_Type;
PyObject* Init_pyMessage_Type();
int pyMessage_Check(PyObject* obj);
PyObject* pyMessage_FromMessage(class plMessage* msg);

}

#endif
