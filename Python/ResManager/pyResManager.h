#ifndef _PYRESMANAGER_H
#define _PYRESMANAGER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plResManager* fThis;
} pyResManager;

typedef struct {
    PyObject_HEAD
    class plPageInfo* fThis;
    bool fPyOwned;
} pyPageInfo;

typedef struct {
    PyObject_HEAD
    class plAgeInfo* fThis;
    bool fPyOwned;
} pyAgeInfo;

extern PyTypeObject pyResManager_Type;
PyObject* Init_pyResManager_Type();
int pyResManager_Check(PyObject* obj);

extern PyTypeObject pyFactory_Type;
PyObject* Init_pyFactory_Type();

extern PyTypeObject pyPageInfo_Type;
PyObject* Init_pyPageInfo_Type();
int pyPageInfo_Check(PyObject* obj);
PyObject* pyPageInfo_FromPageInfo(class plPageInfo* page);

extern PyTypeObject pyAgeInfo_Type;
PyObject* Init_pyAgeInfo_Type();
int pyAgeInfo_Check(PyObject* obj);
PyObject* pyAgeInfo_FromAgeInfo(class plAgeInfo* page);

}

#endif
