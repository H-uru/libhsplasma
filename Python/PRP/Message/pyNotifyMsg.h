#ifndef _PYNOTIFYMSG_H
#define _PYNOTIFYMSG_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plNotifyMsg* fThis;
    bool fPyOwned;
} pyNotifyMsg;

extern PyTypeObject pyNotifyMsg_Type;
PyObject* Init_pyNotifyMsg_Type();
int pyNotifyMsg_Check(PyObject* obj);
PyObject* pyNotifyMsg_FromNotifyMsg(class plNotifyMsg* msg);

}

#endif
