#ifndef _PLPYTHONFILEMOD_H
#define _PLPYTHONFILEMOD_H

#include "../../CoreLib/hsStream.h"
#include "../../NucleusLib/pnModifier/plModifier.h"

struct plPythonParameter {
public:
    enum {
        kInt = 1, kFloat, kBoolean, kString, kSceneObject, kSceneObjectList,
        kActivator, kResponder, kDynamicText, kGUIDialog, kExcludeRegion,
        kAnimation, kAnimationName, kBehavior, kMaterial, kGUIPopUpMenu,
        kGUISkin, kWaterComponent, kSwimCurrentInterface, kClusterComponent,
        kMaterialAnimation, kGrassShaderComponent, kGlobalSDLVar, kSubtitle,
        kBlowerComponent, kNone
    };

    static const char* valueTypeNames[];

    unsigned int ID, valueType;
    plKey objKey;
    plString strValue;

    union {
        int intValue;
        float floatValue;
        bool boolValue;
    };

public:
    plPythonParameter(PlasmaVer pv = pvUnknown);
    ~plPythonParameter();

    static unsigned int PlasmaToMapped(unsigned int type, PlasmaVer ver);
    static unsigned int MappedToPlasma(unsigned int type, PlasmaVer ver);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};


DllClass plPythonFileMod : public plMultiModifier {
public:
    struct NamedComponent {
        plString name;
        int id;
        bool isActivator;
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
    plString pythonFile;
    //char* moduleName;
    hsTArray<plKey> receivers;
    //plPipeline* pipe;
    hsTArray<plPythonParameter> parameters;
    
    
public:
    plPythonFileMod();
    virtual ~plPythonFileMod();

    DECLARE_CREATABLE(plPythonFileMod)
    
    plString& getFilename();
    hsTArray<plKey>& getReceivers();
    hsTArray<plPythonParameter>& getParameters();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
