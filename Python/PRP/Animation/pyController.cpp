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

#include "pyController.h"

#include <PRP/Animation/plController.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(Controller, "plController is abstract")

PY_PLASMA_TYPE(Controller, plController, "plController wrapper")

PY_PLASMA_TYPE_INIT(Controller)
{
    pyController_Type.tp_new = pyController_new;
    pyController_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyController_Type);
    return (PyObject*)&pyController_Type;
}

PY_PLASMA_IFC_METHODS(Controller, plController)
