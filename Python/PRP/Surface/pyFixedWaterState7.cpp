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

#include "pyFixedWaterState7.h"

#include <PRP/Surface/plFixedWaterState7.h>
#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

extern "C" {

static PyObject* pyFixedWaterState7_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFixedWaterState7* self = (pyFixedWaterState7*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFixedWaterState7();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY_PROXY(plFixedWaterState7::WaveState, FixedWaterState7, geoState, getGeoState)
PY_PROPERTY_PROXY(plFixedWaterState7::WaveState, FixedWaterState7, texState, getTexState)
PY_PROPERTY(float, FixedWaterState7, rippleScale, getRippleScale, setRippleScale)
PY_PROPERTY(float, FixedWaterState7, waterHeight, getWaterHeight, setWaterHeight)
PY_PROPERTY(hsVector3, FixedWaterState7, windDir, getWindDir, setWindDir)
PY_PROPERTY(hsVector3, FixedWaterState7, specVector, getSpecVector, setSpecVector)
PY_PROPERTY(hsVector3, FixedWaterState7, waterOffset, getWaterOffset, setWaterOffset)
PY_PROPERTY(hsVector3, FixedWaterState7, maxAtten, getMaxAtten, setMaxAtten)
PY_PROPERTY(hsVector3, FixedWaterState7, minAtten, getMinAtten, setMinAtten)
PY_PROPERTY(hsVector3, FixedWaterState7, depthFalloff, getDepthFalloff, setDepthFalloff)
PY_PROPERTY(float, FixedWaterState7, wispiness, getWispiness, setWispiness)
PY_PROPERTY(hsColorRGBA, FixedWaterState7, shoreTint, getShoreTint, setShoreTint)
PY_PROPERTY(hsColorRGBA, FixedWaterState7, maxColor, getMaxColor, setMaxColor)
PY_PROPERTY(hsColorRGBA, FixedWaterState7, minColor, getMinColor, setMinColor)
PY_PROPERTY(float, FixedWaterState7, edgeOpacity, getEdgeOpacity, setEdgeOpacity)
PY_PROPERTY(float, FixedWaterState7, edgeRadius, getEdgeRadius, setEdgeRadius)
PY_PROPERTY(float, FixedWaterState7, period, getPeriod, setPeriod)
PY_PROPERTY(float, FixedWaterState7, fingerLength, getFingerLength, setFingerLength)
PY_PROPERTY(hsColorRGBA, FixedWaterState7, waterTint, getWaterTint, setWaterTint)
PY_PROPERTY(hsColorRGBA, FixedWaterState7, specularTint, getSpecularTint, setSpecularTint)
PY_PROPERTY(hsVector3, FixedWaterState7, envCenter, getEnvCenter, setEnvCenter)
PY_PROPERTY(float, FixedWaterState7, envRadius, getEnvRadius, setEnvRadius)
PY_PROPERTY(float, FixedWaterState7, envRefresh, getEnvRefresh, setEnvRefresh)

static PyGetSetDef pyFixedWaterState7_GetSet[] = {
    pyFixedWaterState7_geoState_getset,
    pyFixedWaterState7_texState_getset,
    pyFixedWaterState7_rippleScale_getset,
    pyFixedWaterState7_waterHeight_getset,
    pyFixedWaterState7_windDir_getset,
    pyFixedWaterState7_specVector_getset,
    pyFixedWaterState7_waterOffset_getset,
    pyFixedWaterState7_maxAtten_getset,
    pyFixedWaterState7_minAtten_getset,
    pyFixedWaterState7_depthFalloff_getset,
    pyFixedWaterState7_wispiness_getset,
    pyFixedWaterState7_shoreTint_getset,
    pyFixedWaterState7_maxColor_getset,
    pyFixedWaterState7_minColor_getset,
    pyFixedWaterState7_edgeOpacity_getset,
    pyFixedWaterState7_edgeRadius_getset,
    pyFixedWaterState7_period_getset,
    pyFixedWaterState7_fingerLength_getset,
    pyFixedWaterState7_waterTint_getset,
    pyFixedWaterState7_specularTint_getset,
    pyFixedWaterState7_envCenter_getset,
    pyFixedWaterState7_envRadius_getset,
    pyFixedWaterState7_envRefresh_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyFixedWaterState7_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFixedWaterState7",    /* tp_name */
    sizeof(pyFixedWaterState7),         /* tp_basicsize */
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
    "plFixedWaterState7 wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFixedWaterState7_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFixedWaterState7_new,             /* tp_new */
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

PyObject* Init_pyFixedWaterState7_Type() {
    if (PyType_Ready(&pyFixedWaterState7_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyFixedWaterState7_Type.tp_dict, "WaveState", Init_pyWaveState7_Type());

    Py_INCREF(&pyFixedWaterState7_Type);
    return (PyObject*)&pyFixedWaterState7_Type;
}

PY_PLASMA_IFC_METHODS(FixedWaterState7, plFixedWaterState7)

}
