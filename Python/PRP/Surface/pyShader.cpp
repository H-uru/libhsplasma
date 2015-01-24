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
#include <PRP/Surface/plShader.h>
#include "pyShader.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyShader_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyShader* self = (pyShader*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plShader();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyShader_getConsts(pyShader* self, void*) {
    PyObject* list = PyList_New(self->fThis->getConsts().size());
    for (size_t i=0; self->fThis->getConsts().size(); i++)
        PyList_SET_ITEM(list, i, pyShaderConst_FromShaderConst(self->fThis->getConsts()[i]));
    return list;
}

static PyObject* pyShader_getID(pyShader* self, void*) {
    return PyInt_FromLong(self->fThis->getID());
}

static PyObject* pyShader_getInput(pyShader* self, void*) {
    return PyInt_FromLong(self->fThis->getInput());
}

static PyObject* pyShader_getOutput(pyShader* self, void*) {
    return PyInt_FromLong(self->fThis->getOutput());
}

static int pyShader_setConsts(pyShader* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setConsts(std::vector<plShaderConst>());
        return 0;
    } else if (PyList_Check(value)) {
        size_t count = PyList_Size(value);
        std::vector<plShaderConst> constList(count);
        for (size_t i=0; i<count; i++) {
            if (!pyShaderConst_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "consts should be a list of strings");
                return -1;
            }
            constList[i] = *((pyShaderConst*)(PyList_GetItem(value, i)))->fThis;
        }
        self->fThis->setConsts(constList);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "consts should be a list of strings");
        return -1;
    }
}

static int pyShader_setID(pyShader* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "id should be an int");
        return -1;
    }
    self->fThis->setID((plShader::plShaderID)PyInt_AsLong(value));
    return 0;
}

static int pyShader_setInput(pyShader* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "input should be an int");
        return -1;
    }
    self->fThis->setInput(PyInt_AsLong(value));
    return 0;
}

static int pyShader_setOutput(pyShader* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "output should be an int");
        return -1;
    }
    self->fThis->setOutput(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyShader_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyShader_GetSet[] = {
    { _pycs("constants"), (getter)pyShader_getConsts, (setter)pyShader_setConsts, NULL, NULL },
    { _pycs("id"), (getter)pyShader_getID, (setter)pyShader_setID, NULL, NULL },
    { _pycs("input"), (getter)pyShader_getInput, (setter)pyShader_setInput, NULL, NULL },
    { _pycs("output"), (getter)pyShader_getOutput, (setter)pyShader_setOutput, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyShader_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plShader",              /* tp_name */
    sizeof(pyShader),                   /* tp_basicsize */
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
    "plShader wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyShader_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyShader_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyShader_new,                       /* tp_new */
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

PyObject* Init_pyShader_Type() {
    pyShader_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyShader_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyShader_Type.tp_dict, "kUnregistered",
                         PyInt_FromLong(plShader::kUnregistered));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveFixedFin6",
                         PyInt_FromLong(plShader::vs_WaveFixedFin6));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_WaveFixed",
                         PyInt_FromLong(plShader::ps_WaveFixed));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_CompCosines",
                         PyInt_FromLong(plShader::vs_CompCosines));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CompCosines",
                         PyInt_FromLong(plShader::ps_CompCosines));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_ShoreLeave6",
                         PyInt_FromLong(plShader::vs_ShoreLeave6));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_ShoreLeave6",
                         PyInt_FromLong(plShader::ps_ShoreLeave6));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveRip",
                         PyInt_FromLong(plShader::vs_WaveRip));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_WaveRip",
                         PyInt_FromLong(plShader::ps_WaveRip));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec1Lay",
                         PyInt_FromLong(plShader::vs_WaveDec1Lay));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec2Lay11",
                         PyInt_FromLong(plShader::vs_WaveDec2Lay11));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec2Lay12",
                         PyInt_FromLong(plShader::vs_WaveDec2Lay12));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDecEnv",
                         PyInt_FromLong(plShader::vs_WaveDecEnv));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CbaseAbase",
                         PyInt_FromLong(plShader::ps_CbaseAbase));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CalphaAbase",
                         PyInt_FromLong(plShader::ps_CalphaAbase));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CalphaAMult",
                         PyInt_FromLong(plShader::ps_CalphaAMult));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CalphaAadd",
                         PyInt_FromLong(plShader::ps_CalphaAadd));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CaddAbase",
                         PyInt_FromLong(plShader::ps_CaddAbase));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CaddAMult",
                         PyInt_FromLong(plShader::ps_CaddAMult));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CaddAAdd",
                         PyInt_FromLong(plShader::ps_CaddAAdd));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CmultAbase",
                         PyInt_FromLong(plShader::ps_CmultAbase));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CmultAMult",
                         PyInt_FromLong(plShader::ps_CmultAMult));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_CmultAAdd",
                         PyInt_FromLong(plShader::ps_CmultAAdd));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_WaveDecEnv",
                         PyInt_FromLong(plShader::ps_WaveDecEnv));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveGraph2",
                         PyInt_FromLong(plShader::vs_WaveGraph2));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_WaveGraph",
                         PyInt_FromLong(plShader::ps_WaveGraph));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveGridFin",
                         PyInt_FromLong(plShader::vs_WaveGridFin));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_WaveGrid",
                         PyInt_FromLong(plShader::ps_WaveGrid));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_BiasNormals",
                         PyInt_FromLong(plShader::vs_BiasNormals));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_BiasNormals",
                         PyInt_FromLong(plShader::ps_BiasNormals));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_ShoreLeave7",
                         PyInt_FromLong(plShader::vs_ShoreLeave7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveRip7",
                         PyInt_FromLong(plShader::vs_WaveRip7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_MoreCosines",
                         PyInt_FromLong(plShader::ps_MoreCosines));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec1Lay_7",
                         PyInt_FromLong(plShader::vs_WaveDec1Lay_7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec2Lay11_7",
                         PyInt_FromLong(plShader::vs_WaveDec2Lay11_7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDec2Lay12_7",
                         PyInt_FromLong(plShader::vs_WaveDec2Lay12_7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveDecEnv_7",
                         PyInt_FromLong(plShader::vs_WaveDecEnv_7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_WaveFixedFin7",
                         PyInt_FromLong(plShader::vs_WaveFixedFin7));
    PyDict_SetItemString(pyShader_Type.tp_dict, "vs_GrassShader",
                         PyInt_FromLong(plShader::vs_GrassShader));
    PyDict_SetItemString(pyShader_Type.tp_dict, "ps_GrassShader",
                         PyInt_FromLong(plShader::ps_GrassShader));
    PyDict_SetItemString(pyShader_Type.tp_dict, "kNumShaders",
                         PyInt_FromLong(plShader::kNumShaders));

    Py_INCREF(&pyShader_Type);
    return (PyObject*)&pyShader_Type;
}

int pyShader_Check(PyObject* obj) {
    if (obj->ob_type == &pyShader_Type
        || PyType_IsSubtype(obj->ob_type, &pyShader_Type))
        return 1;
    return 0;
}

PyObject* pyShader_FromShader(class plShader* shader) {
    if (shader == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyShader* ps = PyObject_New(pyShader, &pyShader_Type);
    ps->fThis = shader;
    ps->fPyOwned = false;
    return (PyObject*)ps;
}

}
