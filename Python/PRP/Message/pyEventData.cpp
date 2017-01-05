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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

extern "C" {

PY_PLASMA_DEALLOC(EventData)
PY_PLASMA_EMPTY_INIT(EventData)
PY_PLASMA_NEW_MSG(EventData, "proEventData is abstract")

PY_METHOD_NOARGS(EventData, EventType,
    "Returns the EventData Class Type of this proEventData object")
{
    return pyPlasma_convert(self->fThis->EventType());
}

PY_METHOD_STATIC_VA(EventData, Read,
    "Params: stream, resManager\n"
    "Read a proEventData object from `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "Read expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "Read expects hsStream, plResManager");
        return NULL;
    }
    proEventData* evt = proEventData::Read(stream->fThis, mgr->fThis);
    PyObject* pyEvt = pyEventData_FromEventData(evt);
    ((pyEventData*)pyEvt)->fPyOwned = true;
    return pyEvt;
}

PY_METHOD_VA(EventData, write,
    "Params: stream, resManager\n"
    "Write this proEventData object to `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    self->fThis->write(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyEventData_Methods[] = {
    pyEventData_EventType_method,
    pyEventData_Read_method,
    pyEventData_write_method,
    PY_METHOD_TERMINATOR
};

PyTypeObject pyEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.proEventData",          /* tp_name */
    sizeof(pyEventData),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyEventData_dealloc,                /* tp_dealloc */
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
    "proEventData wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEventData_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyEventData___init__,               /* tp_init */
    NULL,                               /* tp_alloc */
    pyEventData_new,                    /* tp_new */
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

PyObject* Init_pyEventData_Type() {
    if (PyType_Ready(&pyEventData_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(EventData, "kCollision", proEventData::kCollision);
    PY_TYPE_ADD_CONST(EventData, "kPicked", proEventData::kPicked);
    PY_TYPE_ADD_CONST(EventData, "kControlKey", proEventData::kControlKey);
    PY_TYPE_ADD_CONST(EventData, "kVariable", proEventData::kVariable);
    PY_TYPE_ADD_CONST(EventData, "kFacing", proEventData::kFacing);
    PY_TYPE_ADD_CONST(EventData, "kContained", proEventData::kContained);
    PY_TYPE_ADD_CONST(EventData, "kActivate", proEventData::kActivate);
    PY_TYPE_ADD_CONST(EventData, "kCallback", proEventData::kCallback);
    PY_TYPE_ADD_CONST(EventData, "kResponderState", proEventData::kResponderState);
    PY_TYPE_ADD_CONST(EventData, "kMultiStage", proEventData::kMultiStage);
    PY_TYPE_ADD_CONST(EventData, "kSpawned", proEventData::kSpawned);
    PY_TYPE_ADD_CONST(EventData, "kClickDrag", proEventData::kClickDrag);
    PY_TYPE_ADD_CONST(EventData, "kCoop", proEventData::kCoop);
    PY_TYPE_ADD_CONST(EventData, "kOfferLinkBook", proEventData::kOfferLinkBook);
    PY_TYPE_ADD_CONST(EventData, "kBook", proEventData::kBook);
    PY_TYPE_ADD_CONST(EventData, "kClimbingBlockerHit", proEventData::kClimbingBlockerHit);
    PY_TYPE_ADD_CONST(EventData, "kNone", proEventData::kNone);

    PY_TYPE_ADD_CONST(EventData, "kNumber", proEventData::kNumber);
    PY_TYPE_ADD_CONST(EventData, "kKey", proEventData::kKey);
    PY_TYPE_ADD_CONST(EventData, "kNotta", proEventData::kNotta);

    PY_TYPE_ADD_CONST(EventData, "kEnterStage", proEventData::kEnterStage);
    PY_TYPE_ADD_CONST(EventData, "kBeginningOfLoop", proEventData::kBeginningOfLoop);
    PY_TYPE_ADD_CONST(EventData, "kAdvanceNextStage", proEventData::kAdvanceNextStage);
    PY_TYPE_ADD_CONST(EventData, "kRegressPrevStage", proEventData::kRegressPrevStage);
    PY_TYPE_ADD_CONST(EventData, "kNothing", proEventData::kNothing);

    Py_INCREF(&pyEventData_Type);
    return (PyObject*)&pyEventData_Type;
}

PY_PLASMA_IFC_METHODS(EventData, proEventData)

}
