#ifndef _PLPYTHONMOD_H
#define _PLPYTHONMOD_H

#include "plModifier.h"

DllStruct PY_MATERIAL_ANIM {
    const char* material_name;  // [this+0x0]
    const char* note_name;  // [this+0x4]
    plKey modKey;  // [this+0x8]
};

DllStruct PY_NOTETRACK {
    plKey objKey;  // [this+0x0]
    const char* note_name;  // [this+0x4]
    plKey modKey;  // [this+0x8]
};

DllStruct PY_SOUND_IDX {
    const char* sound_name;  // [this+0x0]
    int sound_index;  // [this+0x4]
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
	unsigned int fPythonSize; //Somewhat of a hack >.>
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
