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

PY_PLASMA_NEW(RenderTarget, plRenderTarget)

PY_PROPERTY(unsigned short, RenderTarget, width, getWidth, setWidth)
PY_PROPERTY(unsigned short, RenderTarget, height, getHeight, setHeight)
PY_PROPERTY(bool, RenderTarget, proportionalViewport, getProportionalViewport,
            setProportionalViewport)

#define RT_PROPERTY_VIEWPORT(direction) \
    PY_GETSET_GETTER_DECL(RenderTarget, viewport##direction)            \
    {                                                                   \
        plRenderTarget* rt = self->fThis;                               \
        if (rt->getProportionalViewport())                              \
            return pyPlasma_convert(rt->getProportionalViewport##direction()); \
        else                                                            \
            return pyPlasma_convert(rt->getAbsoluteViewport##direction()); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(RenderTarget, viewport##direction)            \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(viewport##direction)                     \
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

PY_PLASMA_TYPE(RenderTarget, plRenderTarget, "plRenderTarget wrapper")

PY_PLASMA_TYPE_INIT(RenderTarget)
{
    pyRenderTarget_Type.tp_new = pyRenderTarget_new;
    pyRenderTarget_Type.tp_getset = pyRenderTarget_GetSet;
    pyRenderTarget_Type.tp_base = &pyBitmap_Type;
    if (PyType_CheckAndReady(&pyRenderTarget_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRenderTarget_Type);
    return (PyObject*)&pyRenderTarget_Type;
}

PY_PLASMA_IFC_METHODS(RenderTarget, plRenderTarget)
