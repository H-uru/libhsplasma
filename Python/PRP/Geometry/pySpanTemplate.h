/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PYSPANTEMPLATE_H
#define _PYSPANTEMPLATE_H

#include <PRP/Geometry/plSpanTemplate.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    struct plSpanTemplate::Vertex* fThis;
    bool fPyOwned;
} pySpanTemplateVertex;

typedef struct {
    PyObject_HEAD
    class plSpanTemplate* fThis;
} pySpanTemplate;

extern PyTypeObject pySpanTemplateVertex_Type;
PyObject* Init_pySpanTemplateVertex_Type();
int pySpanTemplateVertex_Check(PyObject* obj);
PyObject* pySpanTemplateVertex_FromVertex(struct plSpanTemplate::Vertex& vert);

extern PyTypeObject pySpanTemplate_Type;
PyObject* Init_pySpanTemplate_Type();
PyObject* pySpanTemplate_FromSpanTemplate(class plSpanTemplate& tpl);

}

#endif
