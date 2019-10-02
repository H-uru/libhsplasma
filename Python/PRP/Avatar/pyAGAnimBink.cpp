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

PY_PLASMA_NEW(AGAnimBink, plAGAnimBink)

PY_PROPERTY_PATHLIKE(AGAnimBink, binkFilename, getBinkFilename, setBinkFilename)
PY_PROPERTY_PATHLIKE(AGAnimBink, sgtFilename, getSgtFilename, setSgtFilename)
PY_PROPERTY(ST::string, AGAnimBink,subtitleId, getSubtitleId, setSubtitleId)

static PyGetSetDef pyAGAnimBink_GetSet[] = {
    pyAGAnimBink_binkFilename_getset,
    pyAGAnimBink_sgtFilename_getset,
    pyAGAnimBink_subtitleId_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGAnimBink, plAGAnimBink, "plAGAnimBink wrapper")

PY_PLASMA_TYPE_INIT(AGAnimBink)
{
    pyAGAnimBink_Type.tp_new = pyAGAnimBink_new;
    pyAGAnimBink_Type.tp_getset = pyAGAnimBink_GetSet;
    pyAGAnimBink_Type.tp_base = &pyATCAnim_Type;
    if (PyType_CheckAndReady(&pyAGAnimBink_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAGAnimBink_Type);
    return (PyObject*)&pyAGAnimBink_Type;
}

PY_PLASMA_IFC_METHODS(AGAnimBink, plAGAnimBink)
