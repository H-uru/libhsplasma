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
#include "pyAGAnim.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ATCAnim, plATCAnim)

PY_METHOD_NOARGS(ATCAnim, clearMarkers, "Remove all named markers from the anim")
{
    self->fThis->getMarkers().clear();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ATCAnim, clearLoops, "Remove all named loops from the anim")
{
    self->fThis->getLoops().clear();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ATCAnim, setMarker,
    "Params: key, position\n"
    "Add a named marker at the specified position")
{
    const char* key;
    float pos;
    if (!PyArg_ParseTuple(args, "sf", &key, &pos)) {
        PyErr_SetString(PyExc_TypeError, "setMarker expects string, float");
        return nullptr;
    }
    self->fThis->setMarker(key, pos);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ATCAnim, setLoop,
    "Params: key, start, end\n"
    "Add a named loop to the specified range")
{
    const char* key;
    float begin, end;
    if (!PyArg_ParseTuple(args, "sff", &key, &begin, &end)) {
        PyErr_SetString(PyExc_TypeError, "setLoop expects string, float, float");
        return nullptr;
    }
    self->fThis->setLoop(key, begin, end);
    Py_RETURN_NONE;
}

static PyMethodDef pyATCAnim_Methods[] = {
    pyATCAnim_clearMarkers_method,
    pyATCAnim_clearLoops_method,
    pyATCAnim_setMarker_method,
    pyATCAnim_setLoop_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ATCAnim, markers)
{
    plATCAnim* anim = self->fThis;
    PyObject* dict = PyDict_New();
    for (const auto& mark : anim->getMarkers())
        PyDict_SetItemString(dict, mark.first.c_str(), pyPlasma_convert(mark.second));
    return dict;
}

PY_PROPERTY_SETTER_MSG(ATCAnim, markers, "To add markers, use setMarker()")
PY_PROPERTY_GETSET_DECL(ATCAnim, markers)

PY_GETSET_GETTER_DECL(ATCAnim, loops)
{
    plATCAnim* anim = self->fThis;
    PyObject* dict = PyDict_New();
    for (const auto& loop : anim->getLoops()) {
        PyDict_SetItemString(dict, loop.first.c_str(),
                  Py_BuildValue("ff", loop.second.first, loop.second.second));
    }
    return dict;
}

PY_PROPERTY_SETTER_MSG(ATCAnim, loops, "To add loops, use setLoop()")
PY_PROPERTY_GETSET_DECL(ATCAnim, loops)

PY_GETSET_GETTER_DECL(ATCAnim, stops)
{
    plATCAnim* anim = self->fThis;
    PyObject* list = PyTuple_New(anim->getStops().size());
    for (size_t i = 0; i < anim->getStops().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(anim->getStops()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(ATCAnim, stops)
{
    PY_PROPERTY_CHECK_NULL(stops)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "stops should be a sequence of floats");
        return -1;
    }
    std::vector<float> stops(seq.size());
    for (size_t i=0; i<stops.size(); i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<float>(item)) {
            PyErr_SetString(PyExc_TypeError, "stops should be a sequence of floats");
            return -1;
        }
        stops[i] = pyPlasma_get<float>(item);
    }
    self->fThis->setStops(stops);
    return 0;
}

PY_PROPERTY_GETSET_DECL(ATCAnim, stops)

PY_PROPERTY(float, ATCAnim, initial, getInitial, setInitial)
PY_PROPERTY(float, ATCAnim, loopStart, getLoopStart, setLoopStart)
PY_PROPERTY(float, ATCAnim, loopEnd, getLoopEnd, setLoopEnd)
PY_PROPERTY(bool, ATCAnim, autoStart, getAutoStart, setAutoStart)
PY_PROPERTY(bool, ATCAnim, loop, getDoLoop, setDoLoop)
PY_PROPERTY(unsigned char, ATCAnim, easeInType, getEaseInType, setEaseInType)
PY_PROPERTY(unsigned char, ATCAnim, easeOutType, getEaseOutType, setEaseOutType)
PY_PROPERTY(float, ATCAnim, easeInLength, getEaseInLength, setEaseInLength)
PY_PROPERTY(float, ATCAnim, easeInMin, getEaseInMin, setEaseInMin)
PY_PROPERTY(float, ATCAnim, easeInMax, getEaseInMax, setEaseInMax)
PY_PROPERTY(float, ATCAnim, easeOutLength, getEaseOutLength, setEaseOutLength)
PY_PROPERTY(float, ATCAnim, easeOutMin, getEaseOutMin, setEaseOutMin)
PY_PROPERTY(float, ATCAnim, easeOutMax, getEaseOutMax, setEaseOutMax)

static PyGetSetDef pyATCAnim_GetSet[] = {
    pyATCAnim_initial_getset,
    pyATCAnim_loopStart_getset,
    pyATCAnim_loopEnd_getset,
    pyATCAnim_autoStart_getset,
    pyATCAnim_loop_getset,
    pyATCAnim_easeInType_getset,
    pyATCAnim_easeOutType_getset,
    pyATCAnim_easeInLength_getset,
    pyATCAnim_easeInMin_getset,
    pyATCAnim_easeInMax_getset,
    pyATCAnim_easeOutLength_getset,
    pyATCAnim_easeOutMin_getset,
    pyATCAnim_easeOutMax_getset,
    pyATCAnim_markers_getset,
    pyATCAnim_loops_getset,
    pyATCAnim_stops_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ATCAnim, plATCAnim, "plATCAnim wrapper")

PY_PLASMA_TYPE_INIT(ATCAnim)
{
    pyATCAnim_Type.tp_new = pyATCAnim_new;
    pyATCAnim_Type.tp_methods = pyATCAnim_Methods;
    pyATCAnim_Type.tp_getset = pyATCAnim_GetSet;
    pyATCAnim_Type.tp_base = &pyAGAnim_Type;
    if (PyType_CheckAndReady(&pyATCAnim_Type) < 0)
        return nullptr;

    Py_INCREF(&pyATCAnim_Type);
    return (PyObject*)&pyATCAnim_Type;
}

PY_PLASMA_IFC_METHODS(ATCAnim, plATCAnim)
