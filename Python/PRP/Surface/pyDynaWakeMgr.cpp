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

#include "pyDynaRippleMgr.h"

#include "PRP/Animation/pyAnimPath.h"
#include <PRP/Surface/plDynaRippleMgr.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(DynaWakeMgr, plDynaWakeMgr)
PY_PLASMA_TYPE(DynaWakeMgr, plDynaWakeMgr, "plDynaWakeMgr wrapper")

PY_PROPERTY(hsVector3, DynaWakeMgr, defaultDir, getDefaultDir, setDefaultDir)

PY_GETSET_GETTER_DECL(DynaWakeMgr, animPath)
{
    return pyAnimPath_FromAnimPath(self->fThis->getAnimPath());
}
PY_GETSET_SETTER_DECL(DynaWakeMgr, animPath)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->setAnimPath(nullptr);
        return 0;
    } else if (pyAnimPath_Check(value)) {
        ((pyAnimPath*)value)->fPyOwned = false;
        self->fThis->setAnimPath(((pyAnimPath*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "animPath should be a plAnimPath");
        return -1;
    }
}
PY_PROPERTY_GETSET_DECL(DynaWakeMgr, animPath)

PY_PROPERTY(float, DynaWakeMgr, animWgt, getAnimWgt, setAnimWgt)
PY_PROPERTY(float, DynaWakeMgr, velWgt, getVelWgt, setVelWgt)

static PyGetSetDef pyDynaWakeMgr_GetSet[] = {
    pyDynaWakeMgr_defaultDir_getset,
    pyDynaWakeMgr_animPath_getset,
    pyDynaWakeMgr_animWgt_getset,
    pyDynaWakeMgr_velWgt_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE_INIT(DynaWakeMgr)
{
    pyDynaWakeMgr_Type.tp_new = pyDynaWakeMgr_new;
    pyDynaWakeMgr_Type.tp_getset = pyDynaWakeMgr_GetSet;
    pyDynaWakeMgr_Type.tp_base = &pyDynaRippleMgr_Type;
    if (PyType_CheckAndReady(&pyDynaWakeMgr_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynaWakeMgr_Type);
    return (PyObject*)&pyDynaWakeMgr_Type;
}

PY_PLASMA_IFC_METHODS(DynaWakeMgr, plDynaWakeMgr)
