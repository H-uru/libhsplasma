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

#include "pyBounds.h"

#include <PRP/Region/hsBounds.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_VALUE_NEW(Bounds3Ext, hsBounds3Ext)

PY_METHOD_VA(Bounds3Ext, getAxis,
    "Params: axis"
    "Get an axis vector")
{
    int axis;
    if (!PyArg_ParseTuple(args, "i", &axis)) {
        PyErr_SetString(PyExc_TypeError, "getAxis expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getAxis((size_t)axis));
}

PY_METHOD_VA(Bounds3Ext, setAxis,
    "Params: axis, value"
    "Set an axis vector")
{
    int axis;
    PyObject* value;
    if (!PyArg_ParseTuple(args, "iO", &axis, &value)) {
        PyErr_SetString(PyExc_TypeError, "setAxis expects int, hsVector3");
        return nullptr;
    }
    if (!pyPlasma_check<hsVector3>(value)) {
        PyErr_SetString(PyExc_TypeError, "setAxis expects int, hsVector3");
        return nullptr;
    }
    self->fThis->setAxis((size_t)axis, pyPlasma_get<hsVector3>(value));
    Py_RETURN_NONE;
}

PY_METHOD_VA(Bounds3Ext, getDist,
    "Params: axis"
    "Get a distance tuple")
{
    int axis;
    if (!PyArg_ParseTuple(args, "i", &axis)) {
        PyErr_SetString(PyExc_TypeError, "getDist expects an int");
        return nullptr;
    }
    hsFloatPoint2 dist = self->fThis->getDist((size_t)axis);
    return Py_BuildValue("ff", dist.X, dist.Y);
}

PY_METHOD_VA(Bounds3Ext, setDist,
    "Params: axis, value"
    "Set a distance tuple")
{
    int axis;
    hsFloatPoint2 value;
    if (!PyArg_ParseTuple(args, "iff", &axis, &value.X, &value.Y)) {
        PyErr_SetString(PyExc_TypeError, "setAxis expects int, float, float");
        return nullptr;
    }
    self->fThis->setDist((size_t)axis, value);
    Py_RETURN_NONE;
}

PyMethodDef pyBounds3Ext_Methods[] = {
    pyBounds3Ext_getAxis_method,
    pyBounds3Ext_setAxis_method,
    pyBounds3Ext_getDist_method,
    pyBounds3Ext_setDist_method,
    PY_METHOD_TERMINATOR
};

/* Backwards compatibility */
#define BOUNDS_GETSET_AXIS(id)                                          \
    PY_GETSET_GETTER_DECL(Bounds3Ext, axis##id)                         \
    {                                                                   \
        return pyPlasma_convert(self->fThis->getAxis(id));              \
    }                                                                   \
    PY_GETSET_SETTER_DECL(Bounds3Ext, axis##id)                         \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(axis##id)                                \
        if (!pyPlasma_check<hsVector3>(value)) {                        \
            PyErr_SetString(PyExc_TypeError, "axis" #id " expected type hsVector3"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setAxis(id, pyPlasma_get<hsVector3>(value));       \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(Bounds3Ext, axis##id)

BOUNDS_GETSET_AXIS(0)
BOUNDS_GETSET_AXIS(1)
BOUNDS_GETSET_AXIS(2)

#define BOUNDS_GETSET_DIST(id)                                          \
    PY_GETSET_GETTER_DECL(Bounds3Ext, dist##id)                         \
    {                                                                   \
        hsFloatPoint2 dist = self->fThis->getDist(id);                  \
        return Py_BuildValue("ff", dist.X, dist.Y);                     \
    }                                                                   \
    PY_GETSET_SETTER_DECL(Bounds3Ext, dist##id)                         \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(dist##id)                                \
        if (!PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {      \
            PyErr_SetString(PyExc_TypeError, "dist" #id " expected type tuple(float, float)"); \
            return -1;                                                  \
        }                                                               \
        hsFloatPoint2 dist;                                             \
        PyObject* itmX = PyTuple_GET_ITEM(value, 0);                    \
        PyObject* itmY = PyTuple_GET_ITEM(value, 1);                    \
        if (!pyPlasma_check<float>(itmX) || !pyPlasma_check<float>(itmY)) { \
            PyErr_SetString(PyExc_TypeError, "dist" #id " expected type tuple (float, float)"); \
            return -1;                                                  \
        }                                                               \
        dist.X = pyPlasma_get<float>(itmX);                             \
        dist.Y = pyPlasma_get<float>(itmY);                             \
        self->fThis->setDist(id, dist);                                 \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(Bounds3Ext, dist##id)

BOUNDS_GETSET_DIST(0)
BOUNDS_GETSET_DIST(1)
BOUNDS_GETSET_DIST(2)

PY_PROPERTY(unsigned int, Bounds3Ext, flags, getFlags, setFlags)
PY_PROPERTY(hsVector3, Bounds3Ext, corner, getCorner, setCorner)
PY_PROPERTY(float, Bounds3Ext, radius, getRadius, setRadius)

static PyGetSetDef pyBounds3Ext_GetSet[] = {
    pyBounds3Ext_flags_getset,
    pyBounds3Ext_corner_getset,
    pyBounds3Ext_axis0_getset,
    pyBounds3Ext_axis1_getset,
    pyBounds3Ext_axis2_getset,
    pyBounds3Ext_dist0_getset,
    pyBounds3Ext_dist1_getset,
    pyBounds3Ext_dist2_getset,
    pyBounds3Ext_radius_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Bounds3Ext, hsBounds3Ext, "hsBounds3Ext wrapper")

PY_PLASMA_TYPE_INIT(Bounds3Ext)
{
    pyBounds3Ext_Type.tp_new = pyBounds3Ext_new;
    pyBounds3Ext_Type.tp_methods = pyBounds3Ext_Methods;
    pyBounds3Ext_Type.tp_getset = pyBounds3Ext_GetSet;
    pyBounds3Ext_Type.tp_base = &pyBounds3_Type;
    if (PyType_CheckAndReady(&pyBounds3Ext_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisAligned", hsBounds3Ext::kAxisAligned);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kSphereSet", hsBounds3Ext::kSphereSet);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kDistsSet", hsBounds3Ext::kDistsSet);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisZeroZero", hsBounds3Ext::kAxisZeroZero);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisOneZero", hsBounds3Ext::kAxisOneZero);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisTwoZero", hsBounds3Ext::kAxisTwoZero);

    Py_INCREF(&pyBounds3Ext_Type);
    return (PyObject*)&pyBounds3Ext_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds3Ext, hsBounds3Ext)
