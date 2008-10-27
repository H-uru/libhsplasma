#ifndef _PYSPANTEMPLATE_H
#define _PYSPANTEMPLATE_H

#include <PRP/Geometry/plSpanTemplate.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSpanTemplate::Vertex* fThis;
    bool fPyOwned;
} pySpanTemplateVertex;

typedef struct {
    PyObject_HEAD
    class plSpanTemplate* fThis;
} pySpanTemplate;

extern PyTypeObject pySpanTemplateVertex_Type;
PyObject* Init_pySpanTemplateVertex_Type();
int pySpanTemplateVertex_Check(PyObject* obj);
PyObject* pySpanTemplateVertex_FromVertex(class plSpanTemplate::Vertex& vert);

extern PyTypeObject pySpanTemplate_Type;
PyObject* Init_pySpanTemplate_Type();
PyObject* pySpanTemplate_FromSpanTemplate(class plSpanTemplate& tpl);

}

#endif
