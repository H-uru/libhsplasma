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

#ifndef _PLPYTHONFILEMOD_H
#define _PLPYTHONFILEMOD_H

#include "plModifier.h"

struct PLASMA_DLL plPythonParameter
{
public:
    enum
    {
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
    ST::string fStrValue;

    union
    {
        int fIntValue;
        float fFloatValue;
        bool fBoolValue;
    };

protected:
    static unsigned int PlasmaToMapped(unsigned int type, PlasmaVer ver);
    static unsigned int MappedToPlasma(unsigned int type, PlasmaVer ver);

public:
    plPythonParameter() : fID(), fValueType(kNone), fIntValue() { }
    plPythonParameter(const plPythonParameter& init)
        : fID(), fValueType(), fIntValue() { operator=(init); }

    plPythonParameter& operator=(const plPythonParameter& init);

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plPythonFileMod : public plMultiModifier
{
    CREATABLE(plPythonFileMod, kPythonFileMod, plMultiModifier)

public:
    enum func_num
    {
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
    ST::string fPythonFile;
    std::vector<plKey> fReceivers;
    std::vector<plPythonParameter> fParameters;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const ST::string& getFilename() const { return fPythonFile; }
    void setFilename(const ST::string& filename) { fPythonFile = filename; }

    const std::vector<plKey>& getReceivers() const { return fReceivers; }
    std::vector<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey rcvr) { fReceivers.emplace_back(std::move(rcvr)); }
    void delReceiver(size_t idx) { fReceivers.erase(fReceivers.begin() + idx); }
    void clearReceivers() { fReceivers.clear(); }

    const std::vector<plPythonParameter>& getParameters() const { return fParameters; }
    std::vector<plPythonParameter>& getParameters() { return fParameters; }
    void addParameter(const plPythonParameter& param) { fParameters.push_back(param); }
    void delParameter(size_t idx) { fParameters.erase(fParameters.begin() + idx); }
    void clearParameters() { fParameters.clear(); }
};

#endif
