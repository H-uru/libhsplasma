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

PY_PLASMA_VALUE_DEALLOC(CullPoly)
PY_PLASMA_EMPTY_INIT(CullPoly)
PY_PLASMA_VALUE_NEW(CullPoly, plCullPoly)

PY_GETSET_GETTER_DECL(CullPoly, verts)
{
    const std::vector<hsVector3>& verts = self->fThis->getVerts();
    PyObject* list = PyTuple_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(verts[i]));
    return list;
}

PY_GETSET_SETTER_DECL(CullPoly, verts)
{
    PY_PROPERTY_CHECK_NULL(verts)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "verts should be a sequence of hsVector3s");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<hsVector3> verts(count);
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<hsVector3>(item)) {
            PyErr_SetString(PyExc_TypeError, "verts should be a sequence of hsVector3s");
            return -1;
        }
        verts[i] = pyPlasma_get<hsVector3>(item);
    }
    self->fThis->setVerts(verts);
    return 0;
}

PY_PROPERTY_GETSET_DECL(CullPoly, verts)

PY_PROPERTY(unsigned int, CullPoly, flags, getFlags, setFlags)
PY_PROPERTY(hsVector3, CullPoly, norm, getNorm, setNorm)
PY_PROPERTY(hsVector3, CullPoly, center, getCenter, setCenter)
PY_PROPERTY(float, CullPoly, dist, getDist, setDist)
PY_PROPERTY(float, CullPoly, radius, getRadius, setRadius)

static PyGetSetDef pyCullPoly_GetSet[] = {
    pyCullPoly_flags_getset,
    pyCullPoly_verts_getset,
    pyCullPoly_norm_getset,
    pyCullPoly_center_getset,
    pyCullPoly_dist_getset,
    pyCullPoly_radius_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CullPoly, plCullPoly, "plCullPoly wrapper")

PY_PLASMA_TYPE_INIT(CullPoly)
{
    pyCullPoly_Type.tp_dealloc = pyCullPoly_dealloc;
    pyCullPoly_Type.tp_init = pyCullPoly___init__;
    pyCullPoly_Type.tp_new = pyCullPoly_new;
    pyCullPoly_Type.tp_getset = pyCullPoly_GetSet;
    if (PyType_CheckAndReady(&pyCullPoly_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CullPoly, "kNone", plCullPoly::kNone);
    PY_TYPE_ADD_CONST(CullPoly, "kHole", plCullPoly::kHole);
    PY_TYPE_ADD_CONST(CullPoly, "kTwoSided", plCullPoly::kTwoSided);

    Py_INCREF(&pyCullPoly_Type);
    return (PyObject*)&pyCullPoly_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(CullPoly, plCullPoly)
