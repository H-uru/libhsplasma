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

    DECLARE_CREATABLE(plPythonMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
