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

#include "pyAGApplicator.h"

#include <PRP/Avatar/plAGApplicator.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(OmniCutoffApplicator, plOmniCutoffApplicator)

PY_PLASMA_TYPE(OmniCutoffApplicator, plOmniCutoffApplicator,
               "plOmniCutoffApplicator wrapper")

PY_PLASMA_TYPE_INIT(OmniCutoffApplicator)
{
    pyOmniCutoffApplicator_Type.tp_new = pyOmniCutoffApplicator_new;
    pyOmniCutoffApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_CheckAndReady(&pyOmniCutoffApplicator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOmniCutoffApplicator_Type);
    return (PyObject*)&pyOmniCutoffApplicator_Type;
}

PY_PLASMA_IFC_METHODS(OmniCutoffApplicator, plOmniCutoffApplicator)
