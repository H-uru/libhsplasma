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

#ifndef _PLPYTHONMOD_H
#define _PLPYTHONMOD_H

#include "plModifier.h"

DllStruct PY_MATERIAL_ANIM {
    plString material_name;
    plString note_name;
    plKey modKey;
};

DllStruct PY_NOTETRACK {
    plKey objKey;
    plString note_name;
    plKey modKey;
};

DllStruct PY_SOUND_IDX {
    plString sound_name;
    int sound_index;
};


DllClass plPythonMod : public plMultiModifier {
    CREATABLE(plPythonMod, kPythonMod, plMultiModifier)

public:
    enum func_num {
        kfunc_Init, kfunc_Update, kfunc_Notify, kfunc_AnimAtStart,
        kfunc_AnimAtStop, kfunc_AnimAtTime, kfunc_AnimAtReverse,
        kfunc_Collide, kfunc_AtTimer, kfunc_OnKeyEvent, kfunc_lastone
    };

protected:
    unsigned char* fPythonCode;
    unsigned int fPythonSize;
    hsTArray<plKey> fReceivers;
    hsTArray<PY_NOTETRACK> fAnimNotetracks;
    hsTArray<PY_SOUND_IDX> fSoundName2Idx;
    hsTArray<PY_MATERIAL_ANIM> fMaterialAnim;

public:
    plPythonMod();
    virtual ~plPythonMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
