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

#include "pySeekPointMod.h"

#include <PRP/Avatar/plSeekPointMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SeekPointMod, plSeekPointMod)

PY_PROPERTY(ST::string, SeekPointMod, name, getName, setName)

PyGetSetDef pySeekPointMod_GetSet[] = {
    pySeekPointMod_name_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SeekPointMod, plSeekPointMod, "plSeekPointMod wrapper")

PY_PLASMA_TYPE_INIT(SeekPointMod)
{
    pySeekPointMod_Type.tp_new = pySeekPointMod_new;
    pySeekPointMod_Type.tp_base = &pyMultiModifier_Type;
    pySeekPointMod_Type.tp_getset = pySeekPointMod_GetSet;
    if (PyType_CheckAndReady(&pySeekPointMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pySeekPointMod_Type);
    return (PyObject*)&pySeekPointMod_Type;
}

PY_PLASMA_IFC_METHODS(SeekPointMod, plSeekPointMod)
