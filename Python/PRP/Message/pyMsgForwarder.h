#ifndef _PYMSGFORWARDER_H
#define _PYMSGFORWARDER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plMsgForwarder* fThis;
    bool fPyOwned;
} pyMsgForwarder;

extern PyTypeObject pyMsgForwarder_Type;
PyObject* Init_pyMsgForwarder_Type();
int pyMsgForwarder_Check(PyObject* obj);
PyObject* pyMsgForwarder_FromMsgForwarder(class plMsgForwarder* msg);

}

#endif
