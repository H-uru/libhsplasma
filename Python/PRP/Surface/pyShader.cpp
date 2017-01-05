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

#include "pyShader.h"

#include <PRP/Surface/plShader.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(Shader, plShader)

static PyObject* pyShader_getConsts(pyShader* self, void*) {
    PyObject* list = PyList_New(self->fThis->getConsts().size());
    for (size_t i=0; self->fThis->getConsts().size(); i++)
        PyList_SET_ITEM(list, i, pyShaderConst_FromShaderConst(self->fThis->getConsts()[i]));
    return list;
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

PY_PROPERTY(plShader::plShaderID, Shader, id, getID, setID)
PY_PROPERTY(unsigned char, Shader, input, getInput, setInput)
PY_PROPERTY(unsigned char, Shader, output, getOutput, setOutput)

static PyGetSetDef pyShader_GetSet[] = {
    { _pycs("constants"), (getter)pyShader_getConsts, (setter)pyShader_setConsts, NULL, NULL },
    pyShader_id_getset,
    pyShader_input_getset,
    pyShader_output_getset,
    PY_GETSET_TERMINATOR
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

    NULL,                               /* tp_methods */
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

    PY_TYPE_ADD_CONST(Shader, "kUnregistered", plShader::kUnregistered);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveFixedFin6", plShader::vs_WaveFixedFin6);
    PY_TYPE_ADD_CONST(Shader, "ps_WaveFixed", plShader::ps_WaveFixed);
    PY_TYPE_ADD_CONST(Shader, "vs_CompCosines", plShader::vs_CompCosines);
    PY_TYPE_ADD_CONST(Shader, "ps_CompCosines", plShader::ps_CompCosines);
    PY_TYPE_ADD_CONST(Shader, "vs_ShoreLeave6", plShader::vs_ShoreLeave6);
    PY_TYPE_ADD_CONST(Shader, "ps_ShoreLeave6", plShader::ps_ShoreLeave6);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveRip", plShader::vs_WaveRip);
    PY_TYPE_ADD_CONST(Shader, "ps_WaveRip", plShader::ps_WaveRip);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec1Lay", plShader::vs_WaveDec1Lay);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec2Lay11", plShader::vs_WaveDec2Lay11);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec2Lay12", plShader::vs_WaveDec2Lay12);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDecEnv", plShader::vs_WaveDecEnv);
    PY_TYPE_ADD_CONST(Shader, "ps_CbaseAbase", plShader::ps_CbaseAbase);
    PY_TYPE_ADD_CONST(Shader, "ps_CalphaAbase", plShader::ps_CalphaAbase);
    PY_TYPE_ADD_CONST(Shader, "ps_CalphaAMult", plShader::ps_CalphaAMult);
    PY_TYPE_ADD_CONST(Shader, "ps_CalphaAadd", plShader::ps_CalphaAadd);
    PY_TYPE_ADD_CONST(Shader, "ps_CaddAbase", plShader::ps_CaddAbase);
    PY_TYPE_ADD_CONST(Shader, "ps_CaddAMult", plShader::ps_CaddAMult);
    PY_TYPE_ADD_CONST(Shader, "ps_CaddAAdd", plShader::ps_CaddAAdd);
    PY_TYPE_ADD_CONST(Shader, "ps_CmultAbase", plShader::ps_CmultAbase);
    PY_TYPE_ADD_CONST(Shader, "ps_CmultAMult", plShader::ps_CmultAMult);
    PY_TYPE_ADD_CONST(Shader, "ps_CmultAAdd", plShader::ps_CmultAAdd);
    PY_TYPE_ADD_CONST(Shader, "ps_WaveDecEnv", plShader::ps_WaveDecEnv);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveGraph2", plShader::vs_WaveGraph2);
    PY_TYPE_ADD_CONST(Shader, "ps_WaveGraph", plShader::ps_WaveGraph);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveGridFin", plShader::vs_WaveGridFin);
    PY_TYPE_ADD_CONST(Shader, "ps_WaveGrid", plShader::ps_WaveGrid);
    PY_TYPE_ADD_CONST(Shader, "vs_BiasNormals", plShader::vs_BiasNormals);
    PY_TYPE_ADD_CONST(Shader, "ps_BiasNormals", plShader::ps_BiasNormals);
    PY_TYPE_ADD_CONST(Shader, "vs_ShoreLeave7", plShader::vs_ShoreLeave7);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveRip7", plShader::vs_WaveRip7);
    PY_TYPE_ADD_CONST(Shader, "ps_MoreCosines", plShader::ps_MoreCosines);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec1Lay_7", plShader::vs_WaveDec1Lay_7);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec2Lay11_7", plShader::vs_WaveDec2Lay11_7);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDec2Lay12_7", plShader::vs_WaveDec2Lay12_7);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveDecEnv_7", plShader::vs_WaveDecEnv_7);
    PY_TYPE_ADD_CONST(Shader, "vs_WaveFixedFin7", plShader::vs_WaveFixedFin7);
    PY_TYPE_ADD_CONST(Shader, "vs_GrassShader", plShader::vs_GrassShader);
    PY_TYPE_ADD_CONST(Shader, "ps_GrassShader", plShader::ps_GrassShader);
    PY_TYPE_ADD_CONST(Shader, "kNumShaders", plShader::kNumShaders);

    Py_INCREF(&pyShader_Type);
    return (PyObject*)&pyShader_Type;
}

PY_PLASMA_IFC_METHODS(Shader, plShader)

}
