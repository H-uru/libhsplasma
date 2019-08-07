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

#include "pyAudible.h"

#include <PRP/Audio/plAudible.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(2WayWinAudible, pl2WayWinAudible)

PY_PLASMA_TYPE(2WayWinAudible, pl2WayWinAudible, "pl2WayWinAudible wrapper")

PY_PLASMA_TYPE_INIT(2WayWinAudible)
{
    py2WayWinAudible_Type.tp_new = py2WayWinAudible_new;
    py2WayWinAudible_Type.tp_base = &pyWinAudible_Type;
    if (PyType_CheckAndReady(&py2WayWinAudible_Type) < 0)
        return nullptr;

    Py_INCREF(&py2WayWinAudible_Type);
    return (PyObject*)&py2WayWinAudible_Type;
}

PY_PLASMA_IFC_METHODS(2WayWinAudible, pl2WayWinAudible)
