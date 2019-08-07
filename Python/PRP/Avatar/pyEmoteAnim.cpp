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

#include "pyATCAnim.h"

#include <PRP/Avatar/plATCAnim.h>
#include "PRP/pyCreatable.h"
#include "PRP/Avatar/pyAGAnim.h"

PY_PLASMA_NEW(EmoteAnim, plEmoteAnim)

PY_PROPERTY(plAGAnim::BodyUsage, EmoteAnim, bodyUsage, getBodyUsage, setBodyUsage)
PY_PROPERTY(float, EmoteAnim, fadeIn, getFadeIn, setFadeIn)
PY_PROPERTY(float, EmoteAnim, fadeOut, getFadeOut, setFadeOut)

static PyGetSetDef pyEmoteAnim_GetSet[] = {
    pyEmoteAnim_bodyUsage_getset,
    pyEmoteAnim_fadeIn_getset,
    pyEmoteAnim_fadeOut_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EmoteAnim, plEmoteAnim, "plEmoteAnim wrapper")

PY_PLASMA_TYPE_INIT(EmoteAnim)
{
    pyEmoteAnim_Type.tp_new = pyEmoteAnim_new;
    pyEmoteAnim_Type.tp_getset = pyEmoteAnim_GetSet;
    pyEmoteAnim_Type.tp_base = &pyATCAnim_Type;
    if (PyType_CheckAndReady(&pyEmoteAnim_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEmoteAnim_Type);
    return (PyObject*)&pyEmoteAnim_Type;
}

PY_PLASMA_IFC_METHODS(EmoteAnim, plEmoteAnim)
