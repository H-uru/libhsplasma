#ifndef _PLPYTHONFILEMOD_H
#define _PLPYTHONFILEMOD_H

#include "plModifier.h"

DllStruct plPythonParameter {
public:
    enum {
        kInt = 1, kFloat, kBoolean, kString, kSceneObject, kSceneObjectList,
        kActivator, kResponder, kDynamicText, kGUIDialog, kExcludeRegion,
        kAnimation, kAnimationName, kBehavior, kMaterial, kGUIPopUpMenu,
        kGUISkin, kWaterComponent, kSwimCurrentInterface, kClusterComponent,
        kMaterialAnimation, kGrassShaderComponent, kGlobalSDLVar, kSubtitle,
        kBlowerComponent, kNone
    };

    static const char* ValueTypeNames[];

    unsigned int fID, fValueType;
    plKey fObjKey;
    plString fStrValue;

    union {
        int fIntValue;
        float fFloatValue;
        bool fBoolValue;
    };

protected:
    static unsigned int PlasmaToMapped(unsigned int type, PlasmaVer ver);
    static unsigned int MappedToPlasma(unsigned int type, PlasmaVer ver);

public:
    plPythonParameter();
    plPythonParameter(const plPythonParameter& init);

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plPythonFileMod : public plMultiModifier {
    CREATABLE(plPythonFileMod, kPythonFileMod, plMultiModifier)

public:
    enum func_num {
        kfunc_FirstUpdate, kfunc_Update, kfunc_Notify, kfunc_AtTimer,
        kfunc_OnKeyEvent, kfunc_Load, kfunc_Save, kfunc_GUINotify,
        kfunc_PageLoad, kfunc_ClothingUpdate, kfunc_KIMsg, kfunc_MemberUpdate,
        kfunc_RemoteAvatarInfo, kfunc_RTChat, kfunc_VaultEvent, kfunc_AvatarPage,
        kfunc_SDLNotify, kfunc_OwnershipNotify, kfunc_AgeVaultEvent, kfunc_Init,
        kfunc_OnCCRMsg, kfunc_OnServerInitComplete, kfunc_OnVaultNotify,
        kfunc_OnDefaultKeyCaught, kfunc_OnMarkerMsg, kfunc_OnBackdoorMsg,
        kfunc_OnBehaviorNotify, kfunc_OnLOSNotify, kfunc_OnBeginAgeLoad,
        kfunc_OnMovieEvent, kfunc_OnScreenCaptureDone, kfunc_OnClimbingWallEvent,
        kfunc_OnClimbingWallInit, kfunc_OnClimbBlockerEvent, kfunc_OnAvatarSpawn,
        kfunc_OnAccountUpdate, kfunc_gotPublicAgeList, kfunc_OnGameMgrMsg,
        kfunc_OnGameCliMsg, kfunc_lastone
    };

protected:
    plString fPythonFile;
    hsTArray<plKey> fReceivers;
    hsTArray<plPythonParameter> fParameters;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plString& getFilename() const { return fPythonFile; }
    void setFilename(const plString& filename) { fPythonFile = filename; }

    const hsTArray<plKey>& getReceivers() const { return fReceivers; }
    hsTArray<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey rcvr) { fReceivers.append(rcvr); }
    void delReceiver(size_t idx) { fReceivers.remove(idx); }
    void clearReceivers() { fReceivers.clear(); }

    const hsTArray<plPythonParameter>& getParameters() const { return fParameters; }
    hsTArray<plPythonParameter>& getParameters() { return fParameters; }
    void addParameter(const plPythonParameter& param) { fParameters.append(param); }
    void delParameter(size_t idx) { fParameters.remove(idx); }
    void clearParameters() { fParameters.clear(); }
};

#endif
