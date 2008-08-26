#ifndef _PYGEOMETRY3_H
#define _PYGEOMETRY3_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsVector3* fThis;
} pyVector3;

typedef struct {
    PyObject_HEAD
    class hsPlane3* fThis;
} pyPlane3;

typedef struct {
    PyObject_HEAD
    class hsQuat* fThis;
} pyQuat;

extern PyTypeObject pyVector3_Type;
PyObject* Init_pyVector3_Type();
int pyVector3_Check(PyObject* obj);
PyObject* pyVector3_FromVector3(const class hsVector3& vec);

extern PyTypeObject pyPlane3_Type;
PyObject* Init_pyPlane3_Type();
int pyPlane3_Check(PyObject* obj);
PyObject* pyPlane3_FromPlane3(const class hsPlane3& vec);

extern PyTypeObject pyQuat_Type;
PyObject* Init_pyQuat_Type();
int pyQuat_Check(PyObject* obj);
PyObject* pyQuat_FromQuat(const class hsQuat& quat);

}

#endif