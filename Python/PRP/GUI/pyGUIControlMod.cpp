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

#include <PRP/GUI/pfGUIControlMod.h>
#include "pyGUIControlMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"
#include "Sys/pyColor.h"
#include "pyGUIControlHandlers.h"

/* pyGUIColorScheme */
PY_PLASMA_NEW(GUIColorScheme, pfGUIColorScheme)

PY_PROPERTY(hsColorRGBA, GUIColorScheme, foreColor, getForeColor, setForeColor)
PY_PROPERTY(hsColorRGBA, GUIColorScheme, backColor, getBackColor, setBackColor)
PY_PROPERTY(hsColorRGBA, GUIColorScheme, selForeColor, getSelForeColor, setSelForeColor)
PY_PROPERTY(hsColorRGBA, GUIColorScheme, selBackColor, getSelBackColor, setSelBackColor)
PY_PROPERTY(bool, GUIColorScheme, transparent, getTransparent, setTransparent)
PY_PROPERTY(ST::string, GUIColorScheme, fontFace, getFontFace, setFontFace)
PY_PROPERTY(unsigned char, GUIColorScheme, fontSize, getFontSize, setFontSize)
PY_PROPERTY(unsigned char, GUIColorScheme, fontFlags, getFontFlags, setFontFlags)

static PyGetSetDef pyGUIColorScheme_GetSet[] = {
    pyGUIColorScheme_foreColor_getset,
    pyGUIColorScheme_backColor_getset,
    pyGUIColorScheme_selForeColor_getset,
    pyGUIColorScheme_selBackColor_getset,
    pyGUIColorScheme_transparent_getset,
    pyGUIColorScheme_fontFace_getset,
    pyGUIColorScheme_fontSize_getset,
    pyGUIColorScheme_fontFlags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIColorScheme, pfGUIColorScheme, "pfGUIColorScheme wrapper")

PY_PLASMA_TYPE_INIT(GUIColorScheme)
{
    pyGUIColorScheme_Type.tp_new = pyGUIColorScheme_new;
    pyGUIColorScheme_Type.tp_getset = pyGUIColorScheme_GetSet;
    if (PyType_CheckAndReady(&pyGUIColorScheme_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIColorScheme, "kFontBold", pfGUIColorScheme::kFontBold);
    PY_TYPE_ADD_CONST(GUIColorScheme, "kFontItalic", pfGUIColorScheme::kFontItalic);
    PY_TYPE_ADD_CONST(GUIColorScheme, "kFontShadowed", pfGUIColorScheme::kFontShadowed);

    Py_INCREF(&pyGUIColorScheme_Type);
    return (PyObject*)&pyGUIColorScheme_Type;
}

PY_PLASMA_IFC_METHODS(GUIColorScheme, pfGUIColorScheme)


/* pyGUIControlMod */
PY_PLASMA_NEW(GUIControlMod, pfGUIControlMod)

PY_METHOD_NOARGS(GUIControlMod, clearSoundIndices,
    "Remove all sound indices from the control")
{
    self->fThis->clearSoundIndices();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIControlMod_Methods[] = {
    pyGUIControlMod_clearSoundIndices_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIControlMod, soundIndices)
{
    PyObject* list = PyTuple_New(self->fThis->getSoundIndices().size());
    for (size_t i = 0; i<self->fThis->getSoundIndices().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getSoundIndices()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GUIControlMod, soundIndices)
{
    PY_PROPERTY_CHECK_NULL(soundIndices)
    if (value == Py_None) {
        self->fThis->setSoundIndices(std::vector<int>());
        return 0;
    }
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "soundIndices should be a sequence of ints");
        return -1;
    }
    std::vector<int> soundIndices(seq.size());
    for (size_t i = 0; i<soundIndices.size(); i++) {
        PyObject* itm = seq.get(i);
        if (!pyPlasma_check<int>(itm)) {
            PyErr_SetString(PyExc_TypeError, "soundIndices should be a sequence of ints");
            return -1;
        }
        soundIndices[i] = pyPlasma_get<int>(itm);
    }
    self->fThis->setSoundIndices(soundIndices);
    return 0;
}

PY_GETSET_GETTER_DECL(GUIControlMod, colorScheme)
{
    return pyPlasma_convert(self->fThis->getColorScheme());
}

PY_GETSET_SETTER_DECL(GUIControlMod, colorScheme)
{
    if (value == Py_None) {
        self->fThis->setColorScheme(nullptr);
        return 0;
    }
    if (!pyPlasma_check<pfGUIColorScheme>(value)) {
        PyErr_SetString(PyExc_TypeError, "colorScheme should be a pfGUIColorScheme");
        return -1;
    }
    self->fThis->setColorScheme(pyPlasma_get<pfGUIColorScheme*>(value));
    return 0;
}

PY_PROPERTY(unsigned int, GUIControlMod, tagID, getTagID, setTagID)
PY_PROPERTY(bool, GUIControlMod, visible, isVisible, setVisible)
PY_PROPERTY_GUIPROC(GUICtrlProcWriteableObject, GUIControlMod, handler, getHandler, setHandler)
PY_PROPERTY(plKey, GUIControlMod, dynTextMap, getDynTextMap, setDynTextMap)
PY_PROPERTY(plKey, GUIControlMod, dynTextLayer, getDynTextLayer, setDynTextLayer)
PY_PROPERTY_GETSET_DECL(GUIControlMod, colorScheme)
PY_PROPERTY(plKey, GUIControlMod, proxy, getProxy, setProxy)
PY_PROPERTY(plKey, GUIControlMod, skin, getSkin, setSkin)
PY_PROPERTY_GETSET_DECL(GUIControlMod, soundIndices)

static PyGetSetDef pyGUIControlMod_GetSet[] = {
    pyGUIControlMod_tagID_getset,
    pyGUIControlMod_visible_getset,
    pyGUIControlMod_handler_getset,
    pyGUIControlMod_dynTextMap_getset,
    pyGUIControlMod_dynTextLayer_getset,
    pyGUIControlMod_colorScheme_getset,
    pyGUIControlMod_proxy_getset,
    pyGUIControlMod_skin_getset,
    pyGUIControlMod_soundIndices_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIControlMod, pfGUIControlMod, "pfGUIControlMod wrapper")

PY_PLASMA_TYPE_INIT(GUIControlMod)
{
    pyGUIControlMod_Type.tp_new = pyGUIControlMod_new;
    pyGUIControlMod_Type.tp_methods = pyGUIControlMod_Methods;
    pyGUIControlMod_Type.tp_getset = pyGUIControlMod_GetSet;
    pyGUIControlMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyGUIControlMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIControlMod, "kWantsInterest", pfGUIControlMod::kWantsInterest);
    PY_TYPE_ADD_CONST(GUIControlMod, "kInheritProcFromDlg", pfGUIControlMod::kInheritProcFromDlg);
    PY_TYPE_ADD_CONST(GUIControlMod, "kIntangible", pfGUIControlMod::kIntangible);
    PY_TYPE_ADD_CONST(GUIControlMod, "kXparentBgnd", pfGUIControlMod::kXparentBgnd);
    PY_TYPE_ADD_CONST(GUIControlMod, "kScaleTextWithResolution", pfGUIControlMod::kScaleTextWithResolution);
    PY_TYPE_ADD_CONST(GUIControlMod, "kTakesSpecialKeys", pfGUIControlMod::kTakesSpecialKeys);
    PY_TYPE_ADD_CONST(GUIControlMod, "kHasProxy", pfGUIControlMod::kHasProxy);
    PY_TYPE_ADD_CONST(GUIControlMod, "kBetterHitTesting", pfGUIControlMod::kBetterHitTesting);

    Py_INCREF(&pyGUIControlMod_Type);
    return (PyObject*)&pyGUIControlMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIControlMod, pfGUIControlMod)
