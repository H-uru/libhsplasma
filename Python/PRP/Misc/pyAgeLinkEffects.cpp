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

#include "pyAgeLinkInfo.h"

#include <PRP/Misc/plAgeLinkInfo.h>

PY_PLASMA_NEW(AgeLinkEffects, plAgeLinkEffects)

PY_PROPERTY(ST::string, AgeLinkEffects, linkInAnimName, getLinkInAnimName, setLinkInAnimName)

PyGetSetDef pyAgeLinkEffects_GetSet[] = {
    pyAgeLinkEffects_linkInAnimName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AgeLinkEffects, plAgeLinkEffects, "plAgeLinkEffects wrapper")

PY_PLASMA_TYPE_INIT(AgeLinkEffects)
{
    pyAgeLinkEffects_Type.tp_new = pyAgeLinkEffects_new;
    pyAgeLinkEffects_Type.tp_getset = pyAgeLinkEffects_GetSet;
    if (PyType_CheckAndReady(&pyAgeLinkEffects_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAgeLinkEffects_Type);
    return (PyObject*)&pyAgeLinkEffects_Type;
}

PY_PLASMA_IFC_METHODS(AgeLinkEffects, plAgeLinkEffects)
