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
		return PyFloat_FromDouble(self->fThis->getVelocity());
	}

	static PyObject* pyCameraBrain1_getAcceleration(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getAcceleration());
	}

	static PyObject* pyCameraBrain1_getDeceleration(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getDeceleration());
	}

	static PyObject* pyCameraBrain1_getPOAVelocity(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getPOAVelocity());
	}

	static PyObject* pyCameraBrain1_getPOAAcceleration(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getPOAAcceleration());
	}

	static PyObject* pyCameraBrain1_getPOADeceleration(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getPOADeceleration());
	}

	static PyObject* pyCameraBrain1_getPOAOffset(pyCameraBrain1* self, void*)
	{
		return pyVector3_FromVector3(self->fThis->getPOAOffset());
	}

	static PyObject* pyCameraBrain1_getXPanLimit(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getXPanLimit());
	}

	static PyObject* pyCameraBrain1_getZPanLimit(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getZPanLimit());
	}

	static PyObject* pyCameraBrain1_getPanSpeed(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getPanSpeed());
	}

	static PyObject* pyCameraBrain1_getZoomRate(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getZoomRate());
	}

	static PyObject* pyCameraBrain1_getZoomMin(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getZoomMin());
	}

	static PyObject* pyCameraBrain1_getZoomMax(pyCameraBrain1* self, void*)
	{
		return PyFloat_FromDouble(self->fThis->getZoomMax());
	}

	static PyObject* pyCameraBrain1_getFlags(pyCameraBrain1* self, void*)
	{
		return pyBitVector_FromBitVector(self->fThis->getFlags());
	}

	static PyObject* pyCameraBrain1_getEoAFlags(pyCameraBrain1* self, void*)
	{
		return pyBitVector_FromBitVector(self->fThis->getEoAFlags());
	}

	static int pyCameraBrain1_setVelocity(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
				PyErr_SetString(PyExc_TypeError, "camera velocity should be a float");
				return -1;
		}
		self->fThis->setVelocity(PyFloat_AsDouble(value));
		return 0;
	}
	
	static int pyCameraBrain1_setAcceleration(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera acceleration should be a float");
			return -1;
		}
		self->fThis->setAcceleration(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setDeceleration(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera deceleration should be a float");
			return -1;
		}
		self->fThis->setDeceleration(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setPOAVelocity(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera POAvelocity should be a float");
			return -1;
		}
		self->fThis->setVelocity(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setPOAAcceleration(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera POAacceleration should be a float");
			return -1;
		}
		self->fThis->setAcceleration(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setPOADeceleration(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera POAdeceleration should be a float");
			return -1;
		}
		self->fThis->setDeceleration(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setPOAOffset(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !pyVector3_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera POAOffset should be a vector3");
			return -1;
		}
		self->fThis->setPOAOffset(*(pyVector3_AsVector3(value)));
		return 0;
	}

	static int pyCameraBrain1_setXPanLimit(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera XPanLimit should be a float");
			return -1;
		}
		self->fThis->setXPanLimit(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setZPanLimit(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera ZPanLimit should be a float");
			return -1;
		}
		self->fThis->setXPanLimit(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setPanSpeed(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera panspeed should be a float");
			return -1;
		}
		self->fThis->setPanSpeed(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setZoomRate(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera zoomrate should be a float");
			return -1;
		}
		self->fThis->setZoomRate(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setZoomMax(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera zoommax should be a float");
			return -1;
		}
		self->fThis->setZoomMax(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setZoomMin(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera zoommin should be a float");
			return -1;
		}
		self->fThis->setZoomMin(PyFloat_AsDouble(value));
		return 0;
	}

	static int pyCameraBrain1_setFlags(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !pyBitVector_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera flags should be a bitvector");
			return -1;
		}
		self->fThis->setFlags(*(pyBitVector_AsBitVector(value)));
		return 0;
	}

	static int pyCameraBrain1_setEoAFlags(pyCameraBrain1* self, PyObject* value, void*)
	{
		if (value == NULL || !pyBitVector_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "camera EoAflags should be a bitvector");
			return -1;
		}
		self->fThis->setEoAFlags(*(pyBitVector_AsBitVector(value)));
		return 0;
	}

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
		(setter)pyCameraBrain1_setZoomMin, NULL, NULL },
		{ _pycs("flags"), (getter)pyCameraBrain1_getFlags,
		(setter)pyCameraBrain1_setFlags, NULL, NULL },
		{ _pycs("eoaFLags"), (getter)pyCameraBrain1_getEoAFlags,
		(setter)pyCameraBrain1_setEoAFlags, NULL, NULL },
	};

	PyTypeObject pyCameraBrain1_Type = {
		PyVarObject_HEAD_INIT(NULL, 0)
		"PyHSPlasma.plCameraBrain1",     /* tp_name */
		sizeof(pyCameraBrain1),          /* tp_basicsize */
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
		"plCameraBrain1 wrapper",        /* tp_doc */

		NULL,                               /* tp_traverse */
		NULL,                               /* tp_clear */
		NULL,                               /* tp_richcompare */
		0,                                  /* tp_weaklistoffset */
		NULL,                               /* tp_iter */
		NULL,                               /* tp_iternext */

		NULL,          /* tp_methods */
		NULL,                               /* tp_members */
		pyCameraBrain1_GetSet,           /* tp_getset */
		NULL,                               /* tp_base */
		NULL,                               /* tp_dict */
		NULL,                               /* tp_descr_get */
		NULL,                               /* tp_descr_set */
		0,                                  /* tp_dictoffset */

		NULL,                               /* tp_init */
		NULL,                               /* tp_alloc */
		pyCameraBrain1_new,              /* tp_new */
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
