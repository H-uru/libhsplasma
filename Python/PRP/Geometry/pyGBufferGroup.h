#ifndef _PYGBUFFERGROUP_H
#define _PYGBUFFERGROUP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plGBufferCell* fThis;
} pyGBufferCell;

typedef struct {
    PyObject_HEAD
    class plGBufferTriangle* fThis;
} pyGBufferTriangle;

typedef struct {
    PyObject_HEAD
    struct plGBufferVertex* fThis;
} pyGBufferVertex;

typedef struct {
    PyObject_HEAD
    class plGBufferGroup* fThis;
    bool fPyOwned;
} pyGBufferGroup;

extern PyTypeObject pyGBufferCell_Type;
PyObject* Init_pyGBufferCell_Type();
int pyGBufferCell_Check(PyObject* obj);
PyObject* pyGBufferCell_FromGBufferCell(const class plGBufferCell& cell);

extern PyTypeObject pyGBufferTriangle_Type;
PyObject* Init_pyGBufferTriangle_Type();
int pyGBufferTriangle_Check(PyObject* obj);
PyObject* pyGBufferTriangle_FromGBufferTriangle(const class plGBufferTriangle& tri);

extern PyTypeObject pyGBufferVertex_Type;
PyObject* Init_pyGBufferVertex_Type();
int pyGBufferVertex_Check(PyObject* obj);
PyObject* pyGBufferVertex_FromGBufferVertex(const class plGBufferVertex& vert);

extern PyTypeObject pyGBufferGroup_Type;
PyObject* Init_pyGBufferGroup_Type();
int pyGBufferGroup_Check(PyObject* obj);
PyObject* pyGBufferGroup_FromGBufferGroup(class plGBufferGroup* group);

}

#endif
