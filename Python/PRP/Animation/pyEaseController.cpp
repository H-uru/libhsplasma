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

#include "pyLeafController.h"

#include <PRP/Animation/plKeyControllers.hpp>
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(EaseController)
PY_PLASMA_NEW(EaseController, plEaseController)

PY_PLASMA_TYPE(EaseController, plEaseController, "plEaseController wrapper")

PY_PLASMA_TYPE_INIT(EaseController)
{
    pyEaseController_Type.tp_init = pyEaseController___init__;
    pyEaseController_Type.tp_new = pyEaseController_new;
    pyEaseController_Type.tp_base = &pyLeafController_Type;
    if (PyType_CheckAndReady(&pyEaseController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEaseController_Type);
    return (PyObject*)&pyEaseController_Type;
}

PY_PLASMA_IFC_METHODS(EaseController, plEaseController)
