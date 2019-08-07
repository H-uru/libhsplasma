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

#include "pyAGAnim.h"

#include <PRP/Avatar/plAGAnim.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(AgeGlobalAnim, plAgeGlobalAnim)

PY_PROPERTY(ST::string, AgeGlobalAnim, globalVarName, getGlobalVarName, setGlobalVarName)

static PyGetSetDef pyAgeGlobalAnim_GetSet[] = {
    pyAgeGlobalAnim_globalVarName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AgeGlobalAnim, plAgeGlobalAnim, "plAgeGlobalAnim wrapper")

PY_PLASMA_TYPE_INIT(AgeGlobalAnim)
{
    pyAgeGlobalAnim_Type.tp_new = pyAgeGlobalAnim_new;
    pyAgeGlobalAnim_Type.tp_getset = pyAgeGlobalAnim_GetSet;
    pyAgeGlobalAnim_Type.tp_base = &pyAGAnim_Type;
    if (PyType_CheckAndReady(&pyAgeGlobalAnim_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAgeGlobalAnim_Type);
    return (PyObject*)&pyAgeGlobalAnim_Type;
}

PY_PLASMA_IFC_METHODS(AgeGlobalAnim, plAgeGlobalAnim)
