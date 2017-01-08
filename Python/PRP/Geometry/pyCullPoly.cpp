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

#include "pyOccluder.h"

#include <PRP/Geometry/plCullPoly.h>
#include <Math/hsGeometry3.h>
#include "Math/pyGeometry3.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(CullPoly)
PY_PLASMA_EMPTY_INIT(CullPoly)
PY_PLASMA_VALUE_NEW(CullPoly, plCullPoly)

static PyObject* pyCullPoly_getVerts(pyCullPoly* self, void*) {
    std::vector<hsVector3> verts = self->fThis->getVerts();
    PyObject* list = PyList_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(verts[i]));
    return list;
}

static int pyCullPoly_setVerts(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setVerts(std::vector<hsVector3>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "verts should be a list of hsVector3s");
        return -1;
    }
    std::vector<hsVector3> verts(PyList_Size(value));
    for (size_t i=0; i<verts.size(); i++) {
        PyObject* item = PyList_GetItem(value, i);
        if (!pyVector3_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "verts should be a list of hsVector3s");
            return -1;
        }
        verts[i] = *((pyVector3*)item)->fThis;
    }
    self->fThis->setVerts(verts);
    return 0;
}

PY_PROPERTY(unsigned int, CullPoly, flags, getFlags, setFlags)
PY_PROPERTY(hsVector3, CullPoly, norm, getNorm, setNorm)
PY_PROPERTY(hsVector3, CullPoly, center, getCenter, setCenter)
PY_PROPERTY(float, CullPoly, dist, getDist, setDist)
PY_PROPERTY(float, CullPoly, radius, getRadius, setRadius)

static PyGetSetDef pyCullPoly_GetSet[] = {
    pyCullPoly_flags_getset,
    { _pycs("verts"), (getter)pyCullPoly_getVerts, (setter)pyCullPoly_setVerts, NULL, NULL },
    pyCullPoly_norm_getset,
    pyCullPoly_center_getset,
    pyCullPoly_dist_getset,
    pyCullPoly_radius_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CullPoly, plCullPoly, "plCullPoly wrapper")

PY_PLASMA_TYPE_INIT(CullPoly) {
    pyCullPoly_Type.tp_dealloc = pyCullPoly_dealloc;
    pyCullPoly_Type.tp_init = pyCullPoly___init__;
    pyCullPoly_Type.tp_new = pyCullPoly_new;
    pyCullPoly_Type.tp_getset = pyCullPoly_GetSet;
    if (PyType_CheckAndReady(&pyCullPoly_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(CullPoly, "kNone", plCullPoly::kNone);
    PY_TYPE_ADD_CONST(CullPoly, "kHole", plCullPoly::kHole);
    PY_TYPE_ADD_CONST(CullPoly, "kTwoSided", plCullPoly::kTwoSided);

    Py_INCREF(&pyCullPoly_Type);
    return (PyObject*)&pyCullPoly_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(CullPoly, plCullPoly)

}
