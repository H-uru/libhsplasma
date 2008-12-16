#ifndef _PYAGANIM_H
#define _PYAGANIM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAGAnim* fThis;
    bool fPyOwned;
} pyAGAnim;

typedef struct {
    PyObject_HEAD
    class plAgeGlobalAnim* fThis;
    bool fPyOwned;
} pyAgeGlobalAnim;

extern PyTypeObject pyAGAnim_Type;
PyObject* Init_pyAGAnim_Type();
int pyAGAnim_Check(PyObject* obj);
PyObject* pyAGAnim_FromAGAnim(class plAGAnim* anim);

extern PyTypeObject pyAgeGlobalAnim_Type;
PyObject* Init_pyAgeGlobalAnim_Type();
int pyAgeGlobalAnim_Check(PyObject* obj);
PyObject* pyAgeGlobalAnim_FromAgeGlobalAnim(class plAgeGlobalAnim* anim);

}

#endif
