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

#include "pyCollisionDetector.h"

#include <PRP/Physics/plCollisionDetector.h>
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(PanicLinkRegion, plPanicLinkRegion)

PY_PROPERTY(bool, PanicLinkRegion, playLinkOutAnim, getPlayLinkOutAnim, setPlayLinkOutAnim)

static PyGetSetDef pyPanicLinkRegion_GetSet[] = {
    pyPanicLinkRegion_playLinkOutAnim_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PanicLinkRegion, plPanicLinkRegion, "plPanicLinkRegion wrapper")

PY_PLASMA_TYPE_INIT(PanicLinkRegion)
{
    pyPanicLinkRegion_Type.tp_new = pyPanicLinkRegion_new;
    pyPanicLinkRegion_Type.tp_getset = pyPanicLinkRegion_GetSet;
    pyPanicLinkRegion_Type.tp_base = &pyCollisionDetector_Type;
    if (PyType_CheckAndReady(&pyPanicLinkRegion_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPanicLinkRegion_Type);
    return (PyObject*)&pyPanicLinkRegion_Type;
}

PY_PLASMA_IFC_METHODS(PanicLinkRegion, plPanicLinkRegion)
