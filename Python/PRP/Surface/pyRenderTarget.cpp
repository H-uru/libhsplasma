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

#include "pyRenderTarget.h"

#include <PRP/Surface/plRenderTarget.h>
#include "pyBitmap.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyRenderTarget_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyRenderTarget* self = (pyRenderTarget*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plRenderTarget();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(unsigned short, RenderTarget, width, getWidth, setWidth)
PY_PROPERTY(unsigned short, RenderTarget, height, getHeight, setHeight)
PY_PROPERTY(bool, RenderTarget, proportionalViewport, getProportionalViewport,
            setProportionalViewport)

#define RT_PROPERTY_VIEWPORT(direction) \
    PY_GETSET_GETTER_DECL(RenderTarget, viewport##direction) {          \
        plRenderTarget* rt = self->fThis;                               \
        if (rt->getProportionalViewport())                              \
            return pyPlasma_convert(rt->getProportionalViewport##direction()); \
        else                                                            \
            return pyPlasma_convert(rt->getAbsoluteViewport##direction()); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(RenderTarget, viewport##direction) {          \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError,                         \
                            "viewport" #direction " cannot be deleted"); \
            return -1;                                                  \
        }                                                               \
        plRenderTarget* rt = self->fThis;                               \
        if (rt->getProportionalViewport()) {                            \
            if (!pyPlasma_check<float>(value)) {                        \
                PyErr_SetString(PyExc_TypeError,                        \
                                "viewport" #direction " expected type float"); \
                return -1;                                              \
            }                                                           \
            rt->setProportionalViewport##direction(pyPlasma_get<float>(value)); \
        } else {                                                        \
            if (!pyPlasma_check<unsigned short>(value)) {               \
                PyErr_SetString(PyExc_TypeError,                        \
                                "viewport" #direction " expected type unsigned short"); \
                return -1;                                              \
            }                                                           \
            rt->setAbsoluteViewport##direction(pyPlasma_get<unsigned short>(value)); \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(RenderTarget, viewport##direction)

RT_PROPERTY_VIEWPORT(Left)
RT_PROPERTY_VIEWPORT(Top)
RT_PROPERTY_VIEWPORT(Right)
RT_PROPERTY_VIEWPORT(Bottom)

PY_PROPERTY(unsigned char, RenderTarget, ZDepth, getZDepth, setZDepth)
PY_PROPERTY(unsigned char, RenderTarget, stencilDepth, getStencilDepth, setStencilDepth)

static PyGetSetDef pyRenderTarget_GetSet[] = {
    pyRenderTarget_width_getset,
    pyRenderTarget_height_getset,
    pyRenderTarget_proportionalViewport_getset,
    pyRenderTarget_viewportLeft_getset,
    pyRenderTarget_viewportTop_getset,
    pyRenderTarget_viewportRight_getset,
    pyRenderTarget_viewportBottom_getset,
    pyRenderTarget_ZDepth_getset,
    pyRenderTarget_stencilDepth_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyRenderTarget_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plRenderTarget",        /* tp_name */
    sizeof(pyRenderTarget),             /* tp_basicsize */
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
    "plRenderTarget wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyRenderTarget_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyRenderTarget_new,                 /* tp_new */
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

PyObject* Init_pyRenderTarget_Type() {
    pyRenderTarget_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyRenderTarget_Type) < 0)
        return NULL;

    Py_INCREF(&pyRenderTarget_Type);
    return (PyObject*)&pyRenderTarget_Type;
}

PY_PLASMA_IFC_METHODS(RenderTarget, plRenderTarget)

}
