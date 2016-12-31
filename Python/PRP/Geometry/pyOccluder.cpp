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

#include <PRP/Geometry/plOccluder.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(Occluder, plOccluder)

static PyObject* pyOccluder_clearPolys(pyOccluder* self) {
    self->fThis->clearPolys();
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_addPoly(pyOccluder* self, PyObject* args) {
    pyCullPoly* poly;
    if (!PyArg_ParseTuple(args, "O", &poly)) {
        PyErr_SetString(PyExc_TypeError, "addPoly expects a plCullPoly");
        return NULL;
    }
    if (!pyCullPoly_Check((PyObject*)poly)) {
        PyErr_SetString(PyExc_TypeError, "addPoly expects a plCullPoly");
        return NULL;
    }
    self->fThis->addPoly(*poly->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_delPoly(pyOccluder* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPoly expects an int");
        return NULL;
    }
    self->fThis->delPoly(idx);
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_clearVisRegions(pyOccluder* self) {
    self->fThis->clearVisRegions();
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_addVisRegion(pyOccluder* self, PyObject* args) {
    pyKey* region;
    if (!PyArg_ParseTuple(args, "O", &region)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)region)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    self->fThis->addVisRegion(*region->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_delVisRegion(pyOccluder* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delVisRegion expects an int");
        return NULL;
    }
    self->fThis->delVisRegion(idx);
    Py_RETURN_NONE;
}

static PyObject* pyOccluder_getPolys(pyOccluder* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPolys().size());
    for (size_t i=0; i<self->fThis->getPolys().size(); i++)
        PyList_SET_ITEM(list, i, pyCullPoly_FromCullPoly(self->fThis->getPolys()[i]));
    return list;
}

static PyObject* pyOccluder_getVisRegions(pyOccluder* self, void*) {
    PyObject* list = PyList_New(self->fThis->getVisRegions().size());
    for (size_t i=0; i<self->fThis->getVisRegions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getVisRegions()[i]));
    return list;
}

static int pyOccluder_setPolys(pyOccluder* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add polys, use addPoly()");
    return -1;
}

static int pyOccluder_setVisRegions(pyOccluder* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add visRegions, use addVisRegion()");
    return -1;
}

static PyMethodDef pyOccluder_Methods[] = {
    { "clearPolys", (PyCFunction)pyOccluder_clearPolys, METH_NOARGS,
      "Remove all plCullPolys from the occluder" },
    { "addPoly", (PyCFunction)pyOccluder_addPoly, METH_VARARGS,
      "Params: poly\n"
      "Add a plCullPoly to the occluder" },
    { "delPoly", (PyCFunction)pyOccluder_delPoly, METH_VARARGS,
      "Params: idx\n"
      "Remove a plCullPoly from the occluder" },
    { "clearVisRegions", (PyCFunction)pyOccluder_clearVisRegions, METH_NOARGS,
      "Remove all Vis Regions from the occluder" },
    { "addVisRegion", (PyCFunction)pyOccluder_addVisRegion, METH_VARARGS,
      "Params: region\n"
      "Add a Vis Region to the occluder" },
    { "delVisRegion", (PyCFunction)pyOccluder_delVisRegion, METH_VARARGS,
      "Params: idx\n"
      "Remove a Vis Region from the occluder" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(float, Occluder, priority, getPriority, setPriority)
PY_PROPERTY_BOUNDS(Bounds3Ext, Occluder, worldBounds, getWorldBounds, setWorldBounds)
PY_PROPERTY(plKey, Occluder, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyOccluder_GetSet[] = {
    pyOccluder_priority_getset,
    pyOccluder_worldBounds_getset,
    pyOccluder_sceneNode_getset,
    { _pycs("polys"), (getter)pyOccluder_getPolys,
        (setter)pyOccluder_setPolys, NULL, NULL },
    { _pycs("visRegions"), (getter)pyOccluder_getVisRegions,
        (setter)pyOccluder_setVisRegions, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyOccluder_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plOccluder",            /* tp_name */
    sizeof(pyOccluder),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plOccluder wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOccluder_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyOccluder_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOccluder_new,                     /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyOccluder_Type() {
    pyOccluder_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyOccluder_Type) < 0)
        return NULL;

    Py_INCREF(&pyOccluder_Type);
    return (PyObject*)&pyOccluder_Type;
}

PY_PLASMA_IFC_METHODS(Occluder, plOccluder)

}
