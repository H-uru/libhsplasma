#ifndef _PLPYTHONFILEMOD_H
#define _PLPYTHONFILEMOD_H

#include "../../CoreLib/hsStream.h"
#include "../../NucleusLib/pnModifier/plModifier.h"

struct plPythonParameter {
protected:
    PlasmaVer ver;

public:
    enum valueType {
        kInt = 1, kFloat, kBoolean, kString, kSceneObject, kSceneObjectList,
        kActivatorList, kResponderList, kDynamicText, kGUIDialog,
        kExcludeRegion, kAnimation, kAnimationName, kBehavior, kMaterial,
        kGUIPopUpMenu, kGUISkin, kWaterComponent, kSwimCurrentInterface,
        kClusterComponentList, kMaterialAnimation, kGrassShaderComponent,
        kNone
    };

    static const char* valueTypeNames[];

    unsigned int ID, valueType;
    plKey* objKey;

    union {
        int intValue;
        float floatValue;
        bool boolValue;
        char* strValue;
    };

public:
    plPythonParameter(PlasmaVer pv = pvUnknown);
    ~plPythonParameter();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(hsStream* S, pfPrcHelper* prc);
};


DllClass plPythonFileMod : public plMultiModifier {
public:
    struct NamedComponent {
        char* name;
        int   id;
        bool  isActivator;
    };

    enum genref_whats { kNotSure, kAddNotify };
    
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
    //plPythonSDLModifier* SDLMod;
    char* pythonFile;
    //char* moduleName;
    hsTArray<plKey*> receivers;
    //plPipeline* pipe;
    hsTArray<plPythonParameter> parameters;
    
    
public:
    plPythonFileMod();
    virtual ~plPythonFileMod();

    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);
    
    char* getFilename();
    hsTArray<plKey*>& getReceivers();
    hsTArray<plPythonParameter>& getParameters();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
