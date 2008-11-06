#ifndef _PYEVENTCALLBACKMSG_H
#define _PYEVENTCALLBACKMSG_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plEventCallbackMsg* fThis;
    bool fPyOwned;
} pyEventCallbackMsg;

extern PyTypeObject pyEventCallbackMsg_Type;
PyObject* Init_pyEventCallbackMsg_Type();
int pyEventCallbackMsg_Check(PyObject* obj);
PyObject* pyEventCallbackMsg_FromEventCallbackMsg(class plEventCallbackMsg* msg);

}

#endif
