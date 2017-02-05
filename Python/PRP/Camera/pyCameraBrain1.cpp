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

#include <PyPlasma.h>
#include <Math/pyGeometry3.h>
#include <Util/pyBitVector.h>
#include <PRP/Camera/plCameraBrain.h>
#include "PRP/pyCreatable.h"
#include "pyCameraBrain.h"

static inline plCameraBrain1* IConvertCond(pyCameraBrain1* self) {
    return plCameraBrain1::Convert(IConvert((pyCreatable*)self));
}

extern "C" {

static PyObject* pyCameraBrain1_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
	pyCameraBrain1* self = (pyCameraBrain1*)type->tp_alloc(type, 0);
	if (self != NULL) {
		self->fThis = new plCameraBrain1();
		self->fPyOwned = true;
	}
	return (PyObject*)self;
}

static PyObject* pyCameraBrain1_getVelocity(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getVelocity());
}

static PyObject* pyCameraBrain1_getAcceleration(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getAcceleration());
}

static PyObject* pyCameraBrain1_getDeceleration(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getDeceleration());
}

static PyObject* pyCameraBrain1_getPOAVelocity(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getPOAVelocity());
}

static PyObject* pyCameraBrain1_getPOAAcceleration(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getPOAAcceleration());
}

static PyObject* pyCameraBrain1_getPOADeceleration(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getPOADeceleration());
}

static PyObject* pyCameraBrain1_getPOAOffset(pyCameraBrain1* self, void*)
{
	return pyVector3_FromVector3(IConvertCond(self)->getPOAOffset());
}

static PyObject* pyCameraBrain1_getXPanLimit(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getXPanLimit());
}

static PyObject* pyCameraBrain1_getZPanLimit(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getZPanLimit());
}

static PyObject* pyCameraBrain1_getPanSpeed(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getPanSpeed());
}

static PyObject* pyCameraBrain1_getZoomRate(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getZoomRate());
}

static PyObject* pyCameraBrain1_getZoomMin(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getZoomMin());
}

static PyObject* pyCameraBrain1_getZoomMax(pyCameraBrain1* self, void*)
{
	return PyFloat_FromDouble(IConvertCond(self)->getZoomMax());
}

static PyObject* pyCameraBrain1_getFlag(pyCameraBrain1* self,  PyObject* args)
{
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getFlags expects an int");
        return NULL;
    }
    return PyBool_FromLong(IConvertCond(self)->getFlag(prop));
}

static PyObject* pyCameraBrain1_getEoaFlag(pyCameraBrain1* self, PyObject* args)
{
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "EoagetFlags expects an int");
        return NULL;
    }
    return PyBool_FromLong(IConvertCond(self)->getEoaFlag(prop));
}

static int pyCameraBrain1_setVelocity(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera velocity should be a float");
			return -1;
	}
	IConvertCond(self)->setVelocity(PyFloat_AsDouble(value));
	return 0;
}
	
static int pyCameraBrain1_setAcceleration(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera acceleration should be a float");
		return -1;
	}
	IConvertCond(self)->setAcceleration(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setDeceleration(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera deceleration should be a float");
		return -1;
	}
	IConvertCond(self)->setDeceleration(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setPOAVelocity(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera POAvelocity should be a float");
		return -1;
	}
	IConvertCond(self)->setVelocity(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setPOAAcceleration(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera POAacceleration should be a float");
		return -1;
	}
	IConvertCond(self)->setAcceleration(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setPOADeceleration(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera POAdeceleration should be a float");
		return -1;
	}
	IConvertCond(self)->setDeceleration(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setPOAOffset(pyCameraBrain1* self, PyObject* value, void*)
{
    if (!pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "camera POAOffset should be an hsVector3");
        return -1;
    }
    IConvertCond(self)->setPOAOffset(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyCameraBrain1_setXPanLimit(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera XPanLimit should be a float");
		return -1;
	}
	IConvertCond(self)->setXPanLimit(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setZPanLimit(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera ZPanLimit should be a float");
		return -1;
	}
	IConvertCond(self)->setXPanLimit(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setPanSpeed(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera panspeed should be a float");
		return -1;
	}
	IConvertCond(self)->setPanSpeed(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setZoomRate(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera zoomrate should be a float");
		return -1;
	}
	IConvertCond(self)->setZoomRate(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setZoomMax(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera zoommax should be a float");
		return -1;
	}
	IConvertCond(self)->setZoomMax(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setZoomMin(pyCameraBrain1* self, PyObject* value, void*)
{
	if (value == NULL || !PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "camera zoommin should be a float");
		return -1;
	}
	IConvertCond(self)->setZoomMin(PyFloat_AsDouble(value));
	return 0;
}

static int pyCameraBrain1_setFlag(pyCameraBrain1* self, PyObject* args, void*)
{
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlags expects int, bool");
        return NULL;
    }
    IConvertCond(self)->setFlag(prop, value);
	return 0;
}

static int pyCameraBrain1_setEoaFlag(pyCameraBrain1* self, PyObject* args, void*)
{
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setEoaFlags expects int, bool");
        return NULL;
    }
    IConvertCond(self)->setEoaFlag(prop, value);
    return 0;
}

PyMethodDef pyCameraBrain1_Methods[] = {
    { "getFlag", (PyCFunction)pyCameraBrain1_getFlag, METH_VARARGS,
    "Params: flag\n"
    "Returns whether the specified flag is set" },
    { "setProperty", (PyCFunction)pyCameraBrain1_setFlag, METH_VARARGS,
    "Params: flag, value\n"
    "Sets the specified flag" },
    { "getEoaFlag", (PyCFunction)pyCameraBrain1_getEoaFlag, METH_VARARGS,
    "Params: flag\n"
    "Returns whether the specified EoA flag is set" },
    { "setProperty", (PyCFunction)pyCameraBrain1_setEoaFlag, METH_VARARGS,
    "Params: flag, value\n"
    "Sets the specified EoA flag" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCameraBrain1_GetSet[] = {
    { _pycs("velocity"), (getter)pyCameraBrain1_getVelocity,
    (setter)pyCameraBrain1_setVelocity, NULL, NULL },
    { _pycs("acceleration"), (getter)pyCameraBrain1_getAcceleration,
    (setter)pyCameraBrain1_setAcceleration, NULL, NULL },
    { _pycs("deceleration"), (getter)pyCameraBrain1_getDeceleration,
    (setter)pyCameraBrain1_setDeceleration, NULL, NULL },
    { _pycs("poaVelocity"), (getter)pyCameraBrain1_getPOAVelocity,
    (setter)pyCameraBrain1_setPOAVelocity, NULL, NULL },
    { _pycs("poaAcceleration"), (getter)pyCameraBrain1_getPOAAcceleration,
    (setter)pyCameraBrain1_setPOAAcceleration, NULL, NULL },
    { _pycs("poaDeceleration"), (getter)pyCameraBrain1_getPOADeceleration,
    (setter)pyCameraBrain1_setPOADeceleration, NULL, NULL },
    { _pycs("poaOffset"), (getter)pyCameraBrain1_getPOAOffset,
    (setter)pyCameraBrain1_setPOAOffset, NULL, NULL },
    { _pycs("xPanLimit"), (getter)pyCameraBrain1_getXPanLimit,
    (setter)pyCameraBrain1_setXPanLimit, NULL, NULL },
    { _pycs("zPanLimit"), (getter)pyCameraBrain1_getZPanLimit,
    (setter)pyCameraBrain1_setZPanLimit, NULL, NULL },
    { _pycs("panSpeed"), (getter)pyCameraBrain1_getPanSpeed,
    (setter)pyCameraBrain1_setPanSpeed, NULL, NULL },
    { _pycs("zoomRate"), (getter)pyCameraBrain1_getZoomRate,
    (setter)pyCameraBrain1_setZoomRate, NULL, NULL },
    { _pycs("zoomMax"), (getter)pyCameraBrain1_getZoomMax,
    (setter)pyCameraBrain1_setZoomMax, NULL, NULL },
    { _pycs("zoomMin"), (getter)pyCameraBrain1_getZoomMin,
    (setter)pyCameraBrain1_setZoomMin, NULL, NULL }
};


PyTypeObject pyCameraBrain1_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"PyHSPlasma.plCameraBrain1",        /* tp_name */
	sizeof(pyCameraBrain1),             /* tp_basicsize */
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
	"plCameraBrain1 wrapper",           /* tp_doc */

	NULL,                               /* tp_traverse */
	NULL,                               /* tp_clear */
	NULL,                               /* tp_richcompare */
	0,                                  /* tp_weaklistoffset */
	NULL,                               /* tp_iter */
	NULL,                               /* tp_iternext */

	pyCameraBrain1_Methods,             /* tp_methods */
	NULL,                               /* tp_members */
	pyCameraBrain1_GetSet,              /* tp_getset */
	NULL,                               /* tp_base */
	NULL,                               /* tp_dict */
	NULL,                               /* tp_descr_get */
	NULL,                               /* tp_descr_set */
	0,                                  /* tp_dictoffset */

	NULL,                               /* tp_init */
	NULL,                               /* tp_alloc */
	pyCameraBrain1_new,                 /* tp_new */
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

PyObject* Init_pyCameraBrain1_Type() {
    if (PyType_Ready(&pyCameraBrain1_Type) < 0)
        return NULL;

    Py_INCREF(&pyCameraBrain1_Type);
    return (PyObject*)&pyCameraBrain1_Type;
}
     
int pyCameraBrain_Check(PyObject* obj) {
	if (obj->ob_type == &pyCameraBrain1_Type
		|| PyType_IsSubtype(obj->ob_type, &pyCameraBrain1_Type))
		return 1;
	return 0;
}

PyObject* pyCameraBrain1_FromCameraBrain1Convert(class plCameraBrain1* atc) {
	if (atc == NULL) {
		Py_INCREF(Py_None);
		return Py_None;
	}
	pyCameraBrain1* pyobj = PyObject_New(pyCameraBrain1, &pyCameraBrain1_Type);
	pyobj->fThis = atc;
	pyobj->fPyOwned = false;
	return (PyObject*)pyobj;
}

}
