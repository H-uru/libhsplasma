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
    plWeakKey fObjKey;
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
    ~plPythonParameter();

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plPythonFileMod : public plMultiModifier {
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
    hsTArray<plWeakKey> fReceivers;
    hsTArray<plPythonParameter> fParameters;
    
public:
    plPythonFileMod();
    virtual ~plPythonFileMod();

    DECLARE_CREATABLE(plPythonFileMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plString& getFilename() const;
    size_t getNumReceivers() const;
    size_t getNumParameters() const;
    plWeakKey getReceiver(size_t idx) const;
    const plPythonParameter& getParameter(size_t idx) const;

    void setFilename(const plString& filename);
    void clearReceivers();
    void clearParameters();
    void addReceiver(plWeakKey rcvr);
    void addParameter(const plPythonParameter& param);
};

#endif
