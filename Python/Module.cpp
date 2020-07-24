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

#include <PyPlasma.h>
#include <Stream/hsStream.h>
#include <Util/PlasmaVersions.h>

#include "Debug/pyDebug.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"
#include "ResManager/pyResManager.h"
#include "SDL/pySDL.h"
#include "Stream/pyPrcHelper.h"
#include "Stream/pyStream.h"
#include "Sys/pyColor.h"
#include "Sys/pyUnifiedTime.h"
#include "Util/pyBitVector.h"
#include "Util/pyDDSurface.h"
#include "Vault/pyServerGuid.h"
#include "Vault/pyVaultNode.h"
#include "Vault/pyVaultStore.h"

#include "PRP/pyCreatable.h"
#include "PRP/pySceneNode.h"
#include "PRP/Animation/pyAnimPath.h"
#include "PRP/Animation/pyAnimTimeConvert.h"
#include "PRP/Animation/pyATCEaseCurves.h"
#include "PRP/Animation/pyController.h"
#include "PRP/Animation/pyFilterCoordInterface.h"
#include "PRP/Animation/pyKeys.h"
#include "PRP/Animation/pyLeafController.h"
#include "PRP/Animation/pyLineFollowMod.h"
#include "PRP/Animation/pyPosController.h"
#include "PRP/Animation/pyRotController.h"
#include "PRP/Animation/pyScaleController.h"
#include "PRP/Animation/pyViewFaceModifier.h"
#include "PRP/Avatar/pyAGAnim.h"
#include "PRP/Avatar/pyAGApplicator.h"
#include "PRP/Avatar/pyAGChannel.h"
#include "PRP/Avatar/pyAGMasterMod.h"
#include "PRP/Avatar/pyAGModifier.h"
#include "PRP/Avatar/pyATCAnim.h"
#include "PRP/Avatar/pyClothingItem.h"
#include "PRP/Avatar/pyLadderModifier.h"
#include "PRP/Avatar/pyMultistageBehMod.h"
#include "PRP/Avatar/pySeekPointMod.h"
#include "PRP/Avatar/pySittingModifier.h"
#include "PRP/Audio/pyAudible.h"
#include "PRP/Audio/pySound.h"
#include "PRP/Audio/pySoundBuffer.h"
#include "PRP/Audio/pyWin32Sound.h"
#include "PRP/Audio/pyWin32StaticSound.h"
#include "PRP/Camera/pyCameraBrain.h"
#include "PRP/Camera/pyCameraModifier.h"
#include "PRP/ConditionalObject/pyActivatorConditionalObject.h"
#include "PRP/ConditionalObject/pyAnimationEventConditionalObject.h"
#include "PRP/ConditionalObject/pyBooleanConditionalObject.h"
#include "PRP/ConditionalObject/pyConditionalObject.h"
#include "PRP/ConditionalObject/pyControlEventConditionalObject.h"
#include "PRP/ConditionalObject/pyDetectConditionalObjects.h"
#include "PRP/ConditionalObject/pyFacingConditionalObject.h"
#include "PRP/ConditionalObject/pyKeyPressConditionalObject.h"
#include "PRP/ConditionalObject/pyVolumeSensorConditionalObject.h"
#include "PRP/Geometry/pyCluster.h"
#include "PRP/Geometry/pyClusterGroup.h"
#include "PRP/Geometry/pyDrawableSpans.h"
#include "PRP/Geometry/pyGBufferGroup.h"
#include "PRP/Geometry/pyGeometrySpan.h"
#include "PRP/Geometry/pyOccluder.h"
#include "PRP/Geometry/pySharedMesh.h"
#include "PRP/Geometry/pySpaceTree.h"
#include "PRP/Geometry/pySpan.h"
#include "PRP/Geometry/pySpanInstance.h"
#include "PRP/Geometry/pySpanTemplate.h"
#include "PRP/GUI/pyGUIButtonMod.h"
#include "PRP/GUI/pyGUICheckBoxCtrl.h"
#include "PRP/GUI/pyGUIControlHandlers.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/GUI/pyGUIDialogMod.h"
#include "PRP/GUI/pyGUIDynDisplayCtrl.h"
#include "PRP/GUI/pyGUIKnobCtrl.h"
#include "PRP/GUI/pyGUIListBoxMod.h"
#include "PRP/GUI/pyGUIMisc.h"
#include "PRP/GUI/pyGUIMultiLineEditCtrl.h"
#include "PRP/GUI/pyGUIPopUpMenu.h"
#include "PRP/GUI/pyGUIProgressCtrl.h"
#include "PRP/GUI/pyGUIRadioGroupCtrl.h"
#include "PRP/GUI/pyGUISkin.h"
#include "PRP/GUI/pyGUITextBoxMod.h"
#include "PRP/GUI/pyGUIUpDownPairMod.h"
#include "PRP/GUI/pyGUIValueCtrl.h"
#include "PRP/GUI/pyImageLibMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/Light/pyLightInfo.h"
#include "PRP/Light/pyShadowCaster.h"
#include "PRP/Light/pyShadowMaster.h"
#include "PRP/Message/pyAnimCmdMsg.h"
#include "PRP/Message/pyArmatureEffectMsg.h"
#include "PRP/Message/pyCameraMsg.h"
#include "PRP/Message/pyCursorChangeMsg.h"
#include "PRP/Message/pyEnableMsg.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/Message/pyEventData.h"
#include "PRP/Message/pyExcludeRegionMsg.h"
#include "PRP/Message/pyLinkToAgeMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/Message/pyMessageWithCallbacks.h"
#include "PRP/Message/pyMsgForwarder.h"
#include "PRP/Message/pyNotifyMsg.h"
#include "PRP/Message/pyResponderMsg.h"
#include "PRP/Message/pyRideAnimatedPhysMsg.h"
#include "PRP/Message/pySimulationMsg.h"
#include "PRP/Message/pySoundMsg.h"
#include "PRP/Message/pySwimMsg.h"
#include "PRP/Message/pyTimerCallbackMsg.h"
#include "PRP/Message/pyWarpMsg.h"
#include "PRP/Misc/pyRenderLevel.h"
#include "PRP/Misc/pyAgeLinkInfo.h"
#include "PRP/Misc/pyFogEnvironment.h"
#include "PRP/Misc/pySpawnPointInfo.h"
#include "PRP/Modifier/pyExcludeRegionModifier.h"
#include "PRP/Modifier/pyFollowMod.h"
#include "PRP/Modifier/pyInterfaceInfoModifier.h"
#include "PRP/Modifier/pyLogicModifier.h"
#include "PRP/Modifier/pyMaintainersMarkerModifier.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Modifier/pyOneShotMod.h"
#include "PRP/Modifier/pyPostEffectMod.h"
#include "PRP/Modifier/pyPythonFileMod.h"
#include "PRP/Modifier/pyResponderModifier.h"
#include "PRP/Modifier/pySpawnModifier.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Object/pySceneObject.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/Particle/pyBoundInterface.h"
#include "PRP/Particle/pyParticleApplicator.h"
#include "PRP/Particle/pyParticleEffect.h"
#include "PRP/Particle/pyParticleEmitter.h"
#include "PRP/Particle/pyParticleGenerator.h"
#include "PRP/Particle/pyParticleSystem.h"
#include "PRP/Physics/pyCollisionDetector.h"
#include "PRP/Physics/pyDetectorModifier.h"
#include "PRP/Physics/pyHKSubWorld.h"
#include "PRP/Physics/pyObjectInVolumeDetector.h"
#include "PRP/Physics/pyPhysical.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/Region/pyConvexVolume.h"
#include "PRP/Region/pySimpleRegionSensor.h"
#include "PRP/Region/pySoftVolume.h"
#include "PRP/Region/pySwimRegion.h"
#include "PRP/Region/pyVisRegion.h"
#include "PRP/Region/pyVolumeIsect.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/Surface/pyCubicEnvironmap.h"
#include "PRP/Surface/pyDistOpacityMod.h"
#include "PRP/Surface/pyDynaDecalMgr.h"
#include "PRP/Surface/pyDynaRippleMgr.h"
#include "PRP/Surface/pyDynamicEnvMap.h"
#include "PRP/Surface/pyDynamicTextMap.h"
#include "PRP/Surface/pyFadeOpacityMod.h"
#include "PRP/Surface/pyFixedWaterState7.h"
#include "PRP/Surface/pyFont.h"
#include "PRP/Surface/pyGMaterial.h"
#include "PRP/Surface/pyGMatState.h"
#include "PRP/Surface/pyGrassShaderMod.h"
#include "PRP/Surface/pyLayer.h"
#include "PRP/Surface/pyLayerAnimation.h"
#include "PRP/Surface/pyLayerMovie.h"
#include "PRP/Surface/pyPrintShape.h"
#include "PRP/Surface/pyRenderTarget.h"
#include "PRP/Surface/pyShader.h"
#include "PRP/Surface/pyWaveSet.h"

/* For compatibility with plString's CleanFileName utility */
static ST::string CleanFileName(const ST::string& fname, bool allowPathChars)
{
    ST::char_buffer result = fname.to_utf8();
    for (char* bp = result.data(); *bp; bp++) {
        if (*bp == '?' || *bp == '*' || *bp == '<' || *bp == '>' ||
            *bp == '"' || *bp == '|' || *bp < (char)0x20)
            *bp = '_';
        if (!allowPathChars && (*bp == '/' || *bp == '\\' || *bp == ':'))
            *bp = '_';
    }
    return result;
}

PY_METHOD_GLOBAL_VA(PyHSPlasma, CleanFileName,
    "Params: string, allowPathChars=False\n"
    "Strips illegal characters from a filename. If allowPathChars is True,\n"
    "the characters '\\', '/' and ':' will not be removed")
{
    const char* fname;
    unsigned char allowPathChars = 0;
    if (!PyArg_ParseTuple(args, "s|b", &fname, &allowPathChars)) {
        PyErr_SetString(PyExc_TypeError, "CleanFileName expects a string");
        return nullptr;
    }
    return pyPlasma_convert(CleanFileName(fname, allowPathChars != 0));
}

static PyMethodDef PyHSPlasma_Methods[] = {
    PyHSPlasma_CleanFileName_method,
    PY_METHOD_TERMINATOR
};

#if PY_MAJOR_VERSION >= 3
static PyModuleDef PyHSPlasma_Module = {
    PyModuleDef_HEAD_INIT,      /* m_base */
    "PyHSPlasma",               /* m_name */
    "Python libHSPlasma interface module",  /* m_doc */
    0,                          /* m_size */
    PyHSPlasma_Methods,         /* m_methods */
    nullptr,                    /* m_reload */
    nullptr,                    /* m_traverse */
    nullptr,                    /* m_clear */
    nullptr,                    /* m_free */
};
#endif

static void initPyHSPlasma_Constants(PyObject* module)
{
    /* Generic constants */
    PyModule_AddIntConstant(module, "pvUnknown", PlasmaVer::pvUnknown);
    PyModule_AddIntConstant(module, "pvPrime", PlasmaVer::pvPrime);
    PyModule_AddIntConstant(module, "pvPots", PlasmaVer::pvPots);
    PyModule_AddIntConstant(module, "pvMoul", PlasmaVer::pvMoul);
    PyModule_AddIntConstant(module, "pvEoa", PlasmaVer::pvEoa);
    PyModule_AddIntConstant(module, "pvHex", PlasmaVer::pvHex);
    PyModule_AddIntConstant(module, "pvUniversal", PlasmaVer::pvUniversal);

    /* File modes */
    PyModule_AddIntConstant(module, "fmRead", fmRead);
    PyModule_AddIntConstant(module, "fmWrite", fmWrite);
    PyModule_AddIntConstant(module, "fmReadWrite", fmReadWrite);
    PyModule_AddIntConstant(module, "fmCreate", fmCreate);

    /* Enum CallbackEvent */
    PyModule_AddIntConstant(module, "kStart", kStart);
    PyModule_AddIntConstant(module, "kStop", kStop);
    PyModule_AddIntConstant(module, "kReverse", kReverse);
    PyModule_AddIntConstant(module, "kTime", kTime);
    PyModule_AddIntConstant(module, "kLoop", kLoop);
    PyModule_AddIntConstant(module, "kBegin", kBegin);
    PyModule_AddIntConstant(module, "kEnd", kEnd);
    PyModule_AddIntConstant(module, "kEventEnd", kEventEnd);
    PyModule_AddIntConstant(module, "kSingleFrameAdjust", kSingleFrameAdjust);
    PyModule_AddIntConstant(module, "kSingleFrameEval", kSingleFrameEval);

    /* Enum ControlEventCode */
    PyModule_AddIntConstant(module, "B_CONTROL_ACTION", B_CONTROL_ACTION);
    PyModule_AddIntConstant(module, "B_CONTROL_ACTION_MOUSE", B_CONTROL_ACTION_MOUSE);
    PyModule_AddIntConstant(module, "B_CONTROL_JUMP", B_CONTROL_JUMP);
    PyModule_AddIntConstant(module, "B_CONTROL_MOVE_FORWARD", B_CONTROL_MOVE_FORWARD);
    PyModule_AddIntConstant(module, "B_CONTROL_MOVE_BACKWARD", B_CONTROL_MOVE_BACKWARD);
    PyModule_AddIntConstant(module, "B_CONTROL_STRAFE_LEFT", B_CONTROL_STRAFE_LEFT);
    PyModule_AddIntConstant(module, "B_CONTROL_STRAFE_RIGHT", B_CONTROL_STRAFE_RIGHT);
    PyModule_AddIntConstant(module, "B_CONTROL_MOVE_UP", B_CONTROL_MOVE_UP);
    PyModule_AddIntConstant(module, "B_CONTROL_MOVE_DOWN", B_CONTROL_MOVE_DOWN);
    PyModule_AddIntConstant(module, "B_CONTROL_ROTATE_LEFT", B_CONTROL_ROTATE_LEFT);
    PyModule_AddIntConstant(module, "B_CONTROL_ROTATE_RIGHT", B_CONTROL_ROTATE_RIGHT);
    PyModule_AddIntConstant(module, "B_CONTROL_ROTATE_UP", B_CONTROL_ROTATE_UP);
    PyModule_AddIntConstant(module, "B_CONTROL_ROTATE_DOWN", B_CONTROL_ROTATE_DOWN);
    PyModule_AddIntConstant(module, "B_CONTROL_MODIFIER_FAST", B_CONTROL_MODIFIER_FAST);
    PyModule_AddIntConstant(module, "B_CONTROL_ALWAYS_RUN", B_CONTROL_ALWAYS_RUN);
    PyModule_AddIntConstant(module, "B_CONTROL_EQUIP", B_CONTROL_EQUIP);
    PyModule_AddIntConstant(module, "B_CONTROL_DROP", B_CONTROL_DROP);
    PyModule_AddIntConstant(module, "B_CONTROL_TURN_TO", B_CONTROL_TURN_TO);
    PyModule_AddIntConstant(module, "B_TOGGLE_DRIVE_MODE", B_TOGGLE_DRIVE_MODE);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_FORWARD", B_CAMERA_MOVE_FORWARD);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_BACKWARD", B_CAMERA_MOVE_BACKWARD);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_UP", B_CAMERA_MOVE_UP);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_DOWN", B_CAMERA_MOVE_DOWN);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_LEFT", B_CAMERA_MOVE_LEFT);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_RIGHT", B_CAMERA_MOVE_RIGHT);
    PyModule_AddIntConstant(module, "B_CAMERA_PAN_UP", B_CAMERA_PAN_UP);
    PyModule_AddIntConstant(module, "B_CAMERA_PAN_DOWN", B_CAMERA_PAN_DOWN);
    PyModule_AddIntConstant(module, "B_CAMERA_PAN_LEFT", B_CAMERA_PAN_LEFT);
    PyModule_AddIntConstant(module, "B_CAMERA_PAN_RIGHT", B_CAMERA_PAN_RIGHT);
    PyModule_AddIntConstant(module, "B_CAMERA_MOVE_FAST", B_CAMERA_MOVE_FAST);
    PyModule_AddIntConstant(module, "B_CAMERA_ROTATE_RIGHT", B_CAMERA_ROTATE_RIGHT);
    PyModule_AddIntConstant(module, "B_CAMERA_ROTATE_LEFT", B_CAMERA_ROTATE_LEFT);
    PyModule_AddIntConstant(module, "B_CAMERA_ROTATE_UP", B_CAMERA_ROTATE_UP);
    PyModule_AddIntConstant(module, "B_CAMERA_ROTATE_DOWN", B_CAMERA_ROTATE_DOWN);
    PyModule_AddIntConstant(module, "B_CAMERA_RECENTER", B_CAMERA_RECENTER);
    PyModule_AddIntConstant(module, "B_CAMERA_DRIVE_SPEED_UP", B_CAMERA_DRIVE_SPEED_UP);
    PyModule_AddIntConstant(module, "B_CAMERA_DRIVE_SPEED_DOWN", B_CAMERA_DRIVE_SPEED_DOWN);
    PyModule_AddIntConstant(module, "B_CAMERA_ZOOM_IN", B_CAMERA_ZOOM_IN);
    PyModule_AddIntConstant(module, "B_CAMERA_ZOOM_OUT", B_CAMERA_ZOOM_OUT);
    PyModule_AddIntConstant(module, "B_SET_CONSOLE_MODE", B_SET_CONSOLE_MODE);
    PyModule_AddIntConstant(module, "B_CONTROL_CONSOLE_COMMAND", B_CONTROL_CONSOLE_COMMAND);
    PyModule_AddIntConstant(module, "B_CONTROL_TOGGLE_PHYSICAL", B_CONTROL_TOGGLE_PHYSICAL);
    PyModule_AddIntConstant(module, "B_CONTROL_PICK", B_CONTROL_PICK);
    PyModule_AddIntConstant(module, "A_CONTROL_MOVE", A_CONTROL_MOVE);
    PyModule_AddIntConstant(module, "A_CONTROL_TURN", A_CONTROL_TURN);
    PyModule_AddIntConstant(module, "A_CONTROL_MOUSE_X", A_CONTROL_MOUSE_X);
    PyModule_AddIntConstant(module, "A_CONTROL_MOUSE_Y", A_CONTROL_MOUSE_Y);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_UP", S_SET_CURSOR_UP);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_DOWN", S_SET_CURSOR_DOWN);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_RIGHT", S_SET_CURSOR_RIGHT);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_LEFT", S_SET_CURSOR_LEFT);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_POISED", S_SET_CURSOR_POISED);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_HIDDEN", S_SET_CURSOR_HIDDEN);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_UNHIDDEN", S_SET_CURSOR_UNHIDDEN);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_ARROW", S_SET_CURSOR_ARROW);
    PyModule_AddIntConstant(module, "S_SEARCH_FOR_PICKABLE", S_SEARCH_FOR_PICKABLE);
    PyModule_AddIntConstant(module, "S_INCREASE_MIC_VOL", S_INCREASE_MIC_VOL);
    PyModule_AddIntConstant(module, "S_DECREASE_MIC_VOL", S_DECREASE_MIC_VOL);
    PyModule_AddIntConstant(module, "S_PUSH_TO_TALK", S_PUSH_TO_TALK);
    PyModule_AddIntConstant(module, "S_SET_THIRD_PERSON_MODE", S_SET_THIRD_PERSON_MODE);
    PyModule_AddIntConstant(module, "S_SET_FIRST_PERSON_MODE", S_SET_FIRST_PERSON_MODE);
    PyModule_AddIntConstant(module, "S_SET_WALK_MODE", S_SET_WALK_MODE);
    PyModule_AddIntConstant(module, "S_SET_FREELOOK", S_SET_FREELOOK);
    PyModule_AddIntConstant(module, "S_SET_CONSOLE_SINGLE", S_SET_CONSOLE_SINGLE);
    PyModule_AddIntConstant(module, "S_SET_CONSOLE_HIDDEN", S_SET_CONSOLE_HIDDEN);
    PyModule_AddIntConstant(module, "B_CONTROL_SET_EQUIPED_STATE", B_CONTROL_SET_EQUIPED_STATE);
    PyModule_AddIntConstant(module, "B_CONTROL_SCROLL_UP_LIST", B_CONTROL_SCROLL_UP_LIST);
    PyModule_AddIntConstant(module, "B_CONTROL_SCROLL_DOWN_LIST", B_CONTROL_SCROLL_DOWN_LIST);
    PyModule_AddIntConstant(module, "B_CONTROL_SET_INVENTORY_ACTIVE", B_CONTROL_SET_INVENTORY_ACTIVE);
    PyModule_AddIntConstant(module, "B_CONTROL_SET_INVENTORY_DISACTIVE", B_CONTROL_SET_INVENTORY_DISACTIVE);
    PyModule_AddIntConstant(module, "B_CONTROL_REMOVE_INV_OBJECT", B_CONTROL_REMOVE_INV_OBJECT);
    PyModule_AddIntConstant(module, "B_CONTROL_ENABLE_OBJECT", B_CONTROL_ENABLE_OBJECT);
    PyModule_AddIntConstant(module, "B_CONTROL_EMOTE", B_CONTROL_EMOTE);
    PyModule_AddIntConstant(module, "B_CONTROL_EXIT_MODE", B_CONTROL_EXIT_MODE);
    PyModule_AddIntConstant(module, "B_CONTROL_DIVE", B_CONTROL_DIVE);
    PyModule_AddIntConstant(module, "B_CAMERA_PAN_TO_CURSOR", B_CAMERA_PAN_TO_CURSOR);
    PyModule_AddIntConstant(module, "B_CONTROL_OPEN_KI", B_CONTROL_OPEN_KI);
    PyModule_AddIntConstant(module, "B_CONTROL_OPEN_BOOK", B_CONTROL_OPEN_BOOK);
    PyModule_AddIntConstant(module, "B_CONTROL_EXIT_GUI_MODE", B_CONTROL_EXIT_GUI_MODE);
    PyModule_AddIntConstant(module, "B_CONTROL_MODIFIER_STRAFE", B_CONTROL_MODIFIER_STRAFE);
    PyModule_AddIntConstant(module, "B_CONTROL_CAMERA_WALK_PAN", B_CONTROL_CAMERA_WALK_PAN);
    PyModule_AddIntConstant(module, "S_SET_BASIC_MODE", S_SET_BASIC_MODE);
    PyModule_AddIntConstant(module, "B_CONTROL_IGNORE_AVATARS", B_CONTROL_IGNORE_AVATARS);
    PyModule_AddIntConstant(module, "B_CONTROL_LADDER_INVERTED", B_CONTROL_LADDER_INVERTED);
    PyModule_AddIntConstant(module, "B_CONTROL_CONSUMABLE_JUMP", B_CONTROL_CONSUMABLE_JUMP);
    PyModule_AddIntConstant(module, "S_SET_WALK_BACK_MODE", S_SET_WALK_BACK_MODE);
    PyModule_AddIntConstant(module, "S_SET_WALK_BACK_LB_MODE", S_SET_WALK_BACK_LB_MODE);
    PyModule_AddIntConstant(module, "S_SET_CURSOR_UPWARD", S_SET_CURSOR_UPWARD);
    PyModule_AddIntConstant(module, "S_SET_LADDER_CONTROL", S_SET_LADDER_CONTROL);
    PyModule_AddIntConstant(module, "S_CLEAR_LADDER_CONTROL", S_CLEAR_LADDER_CONTROL);

    /* Enum plKeyDef */
    PyModule_AddIntConstant(module, "KEY_A", KEY_A);
    PyModule_AddIntConstant(module, "KEY_B", KEY_B);
    PyModule_AddIntConstant(module, "KEY_C", KEY_C);
    PyModule_AddIntConstant(module, "KEY_D", KEY_D);
    PyModule_AddIntConstant(module, "KEY_E", KEY_E);
    PyModule_AddIntConstant(module, "KEY_F", KEY_F);
    PyModule_AddIntConstant(module, "KEY_G", KEY_G);
    PyModule_AddIntConstant(module, "KEY_H", KEY_H);
    PyModule_AddIntConstant(module, "KEY_I", KEY_I);
    PyModule_AddIntConstant(module, "KEY_J", KEY_J);
    PyModule_AddIntConstant(module, "KEY_K", KEY_K);
    PyModule_AddIntConstant(module, "KEY_L", KEY_L);
    PyModule_AddIntConstant(module, "KEY_M", KEY_M);
    PyModule_AddIntConstant(module, "KEY_N", KEY_N);
    PyModule_AddIntConstant(module, "KEY_O", KEY_O);
    PyModule_AddIntConstant(module, "KEY_P", KEY_P);
    PyModule_AddIntConstant(module, "KEY_Q", KEY_Q);
    PyModule_AddIntConstant(module, "KEY_R", KEY_R);
    PyModule_AddIntConstant(module, "KEY_S", KEY_S);
    PyModule_AddIntConstant(module, "KEY_T", KEY_T);
    PyModule_AddIntConstant(module, "KEY_U", KEY_U);
    PyModule_AddIntConstant(module, "KEY_V", KEY_V);
    PyModule_AddIntConstant(module, "KEY_W", KEY_W);
    PyModule_AddIntConstant(module, "KEY_X", KEY_X);
    PyModule_AddIntConstant(module, "KEY_Y", KEY_Y);
    PyModule_AddIntConstant(module, "KEY_Z", KEY_Z);
    PyModule_AddIntConstant(module, "KEY_0", KEY_0);
    PyModule_AddIntConstant(module, "KEY_1", KEY_1);
    PyModule_AddIntConstant(module, "KEY_2", KEY_2);
    PyModule_AddIntConstant(module, "KEY_3", KEY_3);
    PyModule_AddIntConstant(module, "KEY_4", KEY_4);
    PyModule_AddIntConstant(module, "KEY_5", KEY_5);
    PyModule_AddIntConstant(module, "KEY_6", KEY_6);
    PyModule_AddIntConstant(module, "KEY_7", KEY_7);
    PyModule_AddIntConstant(module, "KEY_8", KEY_8);
    PyModule_AddIntConstant(module, "KEY_9", KEY_9);
    PyModule_AddIntConstant(module, "KEY_F1", KEY_F1);
    PyModule_AddIntConstant(module, "KEY_F2", KEY_F2);
    PyModule_AddIntConstant(module, "KEY_F3", KEY_F3);
    PyModule_AddIntConstant(module, "KEY_F4", KEY_F4);
    PyModule_AddIntConstant(module, "KEY_F5", KEY_F5);
    PyModule_AddIntConstant(module, "KEY_F6", KEY_F6);
    PyModule_AddIntConstant(module, "KEY_F7", KEY_F7);
    PyModule_AddIntConstant(module, "KEY_F8", KEY_F8);
    PyModule_AddIntConstant(module, "KEY_F9", KEY_F9);
    PyModule_AddIntConstant(module, "KEY_F10", KEY_F10);
    PyModule_AddIntConstant(module, "KEY_F11", KEY_F11);
    PyModule_AddIntConstant(module, "KEY_F12", KEY_F12);
    PyModule_AddIntConstant(module, "KEY_ESCAPE", KEY_ESCAPE);
    PyModule_AddIntConstant(module, "KEY_TAB", KEY_TAB);
    PyModule_AddIntConstant(module, "KEY_SHIFT", KEY_SHIFT);
    PyModule_AddIntConstant(module, "KEY_CTRL", KEY_CTRL);
    PyModule_AddIntConstant(module, "KEY_ALT", KEY_ALT);
    PyModule_AddIntConstant(module, "KEY_UP", KEY_UP);
    PyModule_AddIntConstant(module, "KEY_DOWN", KEY_DOWN);
    PyModule_AddIntConstant(module, "KEY_LEFT", KEY_LEFT);
    PyModule_AddIntConstant(module, "KEY_RIGHT", KEY_RIGHT);
    PyModule_AddIntConstant(module, "KEY_BACKSPACE", KEY_BACKSPACE);
    PyModule_AddIntConstant(module, "KEY_ENTER", KEY_ENTER);
    PyModule_AddIntConstant(module, "KEY_PAUSE", KEY_PAUSE);
    PyModule_AddIntConstant(module, "KEY_CAPSLOCK", KEY_CAPSLOCK);
    PyModule_AddIntConstant(module, "KEY_PAGEUP", KEY_PAGEUP);
    PyModule_AddIntConstant(module, "KEY_PAGEDOWN", KEY_PAGEDOWN);
    PyModule_AddIntConstant(module, "KEY_END", KEY_END);
    PyModule_AddIntConstant(module, "KEY_HOME", KEY_HOME);
    PyModule_AddIntConstant(module, "KEY_PRINTSCREEN", KEY_PRINTSCREEN);
    PyModule_AddIntConstant(module, "KEY_INSERT", KEY_INSERT);
    PyModule_AddIntConstant(module, "KEY_DELETE", KEY_DELETE);
    PyModule_AddIntConstant(module, "KEY_NUMPAD0", KEY_NUMPAD0);
    PyModule_AddIntConstant(module, "KEY_NUMPAD1", KEY_NUMPAD1);
    PyModule_AddIntConstant(module, "KEY_NUMPAD2", KEY_NUMPAD2);
    PyModule_AddIntConstant(module, "KEY_NUMPAD3", KEY_NUMPAD3);
    PyModule_AddIntConstant(module, "KEY_NUMPAD4", KEY_NUMPAD4);
    PyModule_AddIntConstant(module, "KEY_NUMPAD5", KEY_NUMPAD5);
    PyModule_AddIntConstant(module, "KEY_NUMPAD6", KEY_NUMPAD6);
    PyModule_AddIntConstant(module, "KEY_NUMPAD7", KEY_NUMPAD7);
    PyModule_AddIntConstant(module, "KEY_NUMPAD8", KEY_NUMPAD8);
    PyModule_AddIntConstant(module, "KEY_NUMPAD9", KEY_NUMPAD9);
    PyModule_AddIntConstant(module, "KEY_NUMPAD_MULTIPLY", KEY_NUMPAD_MULTIPLY);
    PyModule_AddIntConstant(module, "KEY_NUMPAD_ADD", KEY_NUMPAD_ADD);
    PyModule_AddIntConstant(module, "KEY_NUMPAD_SUBTRACT", KEY_NUMPAD_SUBTRACT);
    PyModule_AddIntConstant(module, "KEY_NUMPAD_PERIOD", KEY_NUMPAD_PERIOD);
    PyModule_AddIntConstant(module, "KEY_NUMPAD_DIVIDE", KEY_NUMPAD_DIVIDE);
    PyModule_AddIntConstant(module, "KEY_SPACE", KEY_SPACE);
    PyModule_AddIntConstant(module, "KEY_COMMA", KEY_COMMA);
    PyModule_AddIntConstant(module, "KEY_PERIOD", KEY_PERIOD);
    PyModule_AddIntConstant(module, "KEY_DASH", KEY_DASH);
    PyModule_AddIntConstant(module, "KEY_EQUAL", KEY_EQUAL);
    PyModule_AddIntConstant(module, "KEY_SEMICOLON", KEY_SEMICOLON);
    PyModule_AddIntConstant(module, "KEY_SLASH", KEY_SLASH);
    PyModule_AddIntConstant(module, "KEY_TILDE", KEY_TILDE);
    PyModule_AddIntConstant(module, "KEY_LBRACKET", KEY_LBRACKET);
    PyModule_AddIntConstant(module, "KEY_BACKSLASH", KEY_BACKSLASH);
    PyModule_AddIntConstant(module, "KEY_RBRACKET", KEY_RBRACKET);
    PyModule_AddIntConstant(module, "KEY_QUOTE", KEY_QUOTE);
    PyModule_AddIntConstant(module, "KEY_UNMAPPED", KEY_UNMAPPED);
}

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_PyHSPlasma()
{
    PyObject* module = PyModule_Create(&PyHSPlasma_Module);

#else
PyMODINIT_FUNC initPyHSPlasma()
{
    PyObject* module = Py_InitModule3("PyHSPlasma", PyHSPlasma_Methods,
                                      "libHSPlasma Python Interface Module");

#endif
    initPyHSPlasma_Constants(module);

    /* Debug */
    PyModule_AddObject(module, "plDebug", Init_pyDebug_Type());

    /* SDL */
    PyModule_AddObject(module, "plSDLMgr", Init_pySDLMgr_Type());
    PyModule_AddObject(module, "plVarDescriptor", Init_pyVarDescriptor_Type());
    PyModule_AddObject(module, "plStateDescriptor", Init_pyStateDescriptor_Type());

    /* Stream */
    PyModule_AddObject(module, "hsStream", Init_pyStream_Type());
    PyModule_AddObject(module, "hsFileStream", Init_pyFileStream_Type());
    PyModule_AddObject(module, "plEncryptedStream", Init_pyEncryptedStream_Type());
    PyModule_AddObject(module, "hsRAMStream", Init_pyRAMStream_Type());
    PyModule_AddObject(module, "pfPrcHelper", Init_pyPrcHelper_Type());

    /* Util */
    PyModule_AddObject(module, "hsBitVector", Init_pyBitVector_Type());
    PyModule_AddObject(module, "plDDSurface", Init_pyDDSurface_Type());

    /* Vault */
    PyModule_AddObject(module, "plServerGuid", Init_pyServerGuid_Type());
    PyModule_AddObject(module, "plVaultStore", Init_pyVaultStore_Type());
    PyModule_AddObject(module, "plVault", Init_pyVault_Type());
    PyModule_AddObject(module, "plVaultNode", Init_pyVaultNode_Type());
    PyModule_AddObject(module, "plVaultPlayerNode", Init_pyVaultPlayerNode_Type());
    PyModule_AddObject(module, "plVaultAgeNode", Init_pyVaultAgeNode_Type());
    PyModule_AddObject(module, "plVaultGameServerNode", Init_pyVaultGameServerNode_Type());
    PyModule_AddObject(module, "plVaultAdminNode", Init_pyVaultAdminNode_Type());
    PyModule_AddObject(module, "plVaultServerNode", Init_pyVaultServerNode_Type());
    PyModule_AddObject(module, "plVaultFolderNode", Init_pyVaultFolderNode_Type());
    PyModule_AddObject(module, "plVaultPlayerInfoNode", Init_pyVaultPlayerInfoNode_Type());
    PyModule_AddObject(module, "plVaultSystemNode", Init_pyVaultSystemNode_Type());
    PyModule_AddObject(module, "plVaultImageNode", Init_pyVaultImageNode_Type());
    PyModule_AddObject(module, "plVaultTextNoteNode", Init_pyVaultTextNoteNode_Type());
    PyModule_AddObject(module, "plVaultSDLNode", Init_pyVaultSDLNode_Type());
    PyModule_AddObject(module, "plVaultAgeLinkNode", Init_pyVaultAgeLinkNode_Type());
    PyModule_AddObject(module, "plVaultChronicleNode", Init_pyVaultChronicleNode_Type());
    PyModule_AddObject(module, "plVaultPlayerInfoListNode", Init_pyVaultPlayerInfoListNode_Type());
    PyModule_AddObject(module, "plVaultMarkerNode", Init_pyVaultMarkerNode_Type());
    PyModule_AddObject(module, "plVaultAgeInfoNode", Init_pyVaultAgeInfoNode_Type());
    PyModule_AddObject(module, "plVaultAgeInfoListNode", Init_pyVaultAgeInfoListNode_Type());
    PyModule_AddObject(module, "plVaultMarkerListNode", Init_pyVaultMarkerListNode_Type());

    /* Sys */
    PyModule_AddObject(module, "hsColorRGBA", Init_pyColorRGBA_Type());
    PyModule_AddObject(module, "hsColor32", Init_pyColor32_Type());
    PyModule_AddObject(module, "plUnifiedTime", Init_pyUnifiedTime_Type());

    /* Math */
    PyModule_AddObject(module, "hsVector3", Init_pyVector3_Type());
    PyModule_AddObject(module, "hsPlane3", Init_pyPlane3_Type());
    PyModule_AddObject(module, "hsQuat", Init_pyQuat_Type());
    PyModule_AddObject(module, "hsAffineParts", Init_pyAffineParts_Type());
    PyModule_AddObject(module, "hsMatrix33", Init_pyMatrix33_Type());
    PyModule_AddObject(module, "hsMatrix44", Init_pyMatrix44_Type());

    /* ResManager */
    PyModule_AddObject(module, "plFactory", Init_pyFactory_Type());
    PyModule_AddObject(module, "plResManager", Init_pyResManager_Type());
    PyModule_AddObject(module, "plPageInfo", Init_pyPageInfo_Type());
    PyModule_AddObject(module, "plAgeInfo", Init_pyAgeInfo_Type());

    /* pyBounds */
    PyModule_AddObject(module, "hsBounds", Init_pyBounds_Type());
    PyModule_AddObject(module, "hsBounds3", Init_pyBounds3_Type());
    PyModule_AddObject(module, "hsBounds3Ext", Init_pyBounds3Ext_Type());
    PyModule_AddObject(module, "hsBoundsOriented", Init_pyBoundsOriented_Type());

    /* pySpan */
    PyModule_AddObject(module, "plSpan", Init_pySpan_Type());
    PyModule_AddObject(module, "plVertexSpan", Init_pyVertexSpan_Type());
    PyModule_AddObject(module, "plIcicle", Init_pyIcicle_Type());
    PyModule_AddObject(module, "plParticleSpan", Init_pyParticleSpan_Type());

    /* pyKey */
    PyModule_AddObject(module, "plKey", Init_pyKey_Type());
    PyModule_AddObject(module, "plLocation", Init_pyLocation_Type());

    /* Cluster stuff */
    PyModule_AddObject(module, "plCluster", Init_pyCluster_Type());
    PyModule_AddObject(module, "plSpanEncoding", Init_pySpanEncoding_Type());
    PyModule_AddObject(module, "plSpanInstance", Init_pySpanInstance_Type());
    PyModule_AddObject(module, "plSpanTemplate", Init_pySpanTemplate_Type());
    PyModule_AddObject(module, "plSpanTemplateVertex", Init_pySpanTemplateVertex_Type());
    PyModule_AddObject(module, "plLODDist", Init_pyLODDist_Type());

    /* Key Frames */
    PyModule_AddObject(module, "hsKeyFrame", Init_pyKeyFrame_Type());
    PyModule_AddObject(module, "hsPoint3Key", Init_pyPoint3Key_Type());
    PyModule_AddObject(module, "hsScalarKey", Init_pyScalarKey_Type());
    PyModule_AddObject(module, "hsScaleKey", Init_pyScaleKey_Type());
    PyModule_AddObject(module, "hsQuatKey", Init_pyQuatKey_Type());
    PyModule_AddObject(module, "hsCompressedQuatKey32", Init_pyCompressedQuatKey32_Type());
    PyModule_AddObject(module, "hsCompressedQuatKey64", Init_pyCompressedQuatKey64_Type());
    PyModule_AddObject(module, "hsG3DSMaxKeyFrame", Init_pyG3DSMaxKeyFrame_Type());
    PyModule_AddObject(module, "hsMatrix33Key", Init_pyMatrix33Key_Type());
    PyModule_AddObject(module, "hsMatrix44Key", Init_pyMatrix44Key_Type());

    /* proEventData stuff */
    PyModule_AddObject(module, "proEventData", Init_pyEventData_Type());
    PyModule_AddObject(module, "proCollisionEventData", Init_pyCollisionEventData_Type());
    PyModule_AddObject(module, "proPickedEventData", Init_pyPickedEventData_Type());
    PyModule_AddObject(module, "proControlKeyEventData", Init_pyControlKeyEventData_Type());
    PyModule_AddObject(module, "proVariableEventData", Init_pyVariableEventData_Type());
    PyModule_AddObject(module, "proFacingEventData", Init_pyFacingEventData_Type());
    PyModule_AddObject(module, "proContainedEventData", Init_pyContainedEventData_Type());
    PyModule_AddObject(module, "proActivateEventData", Init_pyActivateEventData_Type());
    PyModule_AddObject(module, "proCallbackEventData", Init_pyCallbackEventData_Type());
    PyModule_AddObject(module, "proResponderStateEventData", Init_pyResponderStateEventData_Type());
    PyModule_AddObject(module, "proMultiStageEventData", Init_pyMultiStageEventData_Type());
    PyModule_AddObject(module, "proSpawnedEventData", Init_pySpawnedEventData_Type());
    PyModule_AddObject(module, "proClickDragEventData", Init_pyClickDragEventData_Type());
    PyModule_AddObject(module, "proCoopEventData", Init_pyCoopEventData_Type());
    PyModule_AddObject(module, "proOfferLinkBookEventData", Init_pyOfferLinkBookEventData_Type());
    PyModule_AddObject(module, "proBookEventData", Init_pyBookEventData_Type());
    PyModule_AddObject(module, "proClimbingBlockerHitEventData", Init_pyClimbingBlockerHitEventData_Type());

    /* Other Creatable Dependencies */
    PyModule_AddObject(module, "plDISpanIndex", Init_pyDISpanIndex_Type());
    PyModule_AddObject(module, "plGBufferCell", Init_pyGBufferCell_Type());
    PyModule_AddObject(module, "plGBufferTriangle", Init_pyGBufferTriangle_Type());
    PyModule_AddObject(module, "plGBufferVertex", Init_pyGBufferVertex_Type());
    PyModule_AddObject(module, "plGBufferGroup", Init_pyGBufferGroup_Type());
    PyModule_AddObject(module, "plGeometrySpan", Init_pyGeometrySpan_Type());
    PyModule_AddObject(module, "plRenderLevel", Init_pyRenderLevel_Type());
    PyModule_AddObject(module, "plSpaceTreeNode", Init_pySpaceTreeNode_Type());
    PyModule_AddObject(module, "hsGMatState", Init_pyGMatState_Type());
    PyModule_AddObject(module, "plShaderConst", Init_pyShaderConst_Type());
    PyModule_AddObject(module, "plWAVHeader", Init_pyWAVHeader_Type());
    PyModule_AddObject(module, "plSimDefs", Init_pySimDefs_Type());
    PyModule_AddObject(module, "plPythonParameter", Init_pyPythonParameter_Type());
    PyModule_AddObject(module, "plResponderModifier_Cmd", Init_pyResponderModifier_Cmd_Type());
    PyModule_AddObject(module, "plResponderModifier_State", Init_pyResponderModifier_State_Type());
    PyModule_AddObject(module, "plCullPoly", Init_pyCullPoly_Type());
    PyModule_AddObject(module, "plSpawnPointInfo", Init_pySpawnPointInfo_Type());
    PyModule_AddObject(module, "plFixedWaterState7", Init_pyFixedWaterState7_Type());
    PyModule_AddObject(module, "plCameraConfig", Init_pyCameraConfig_Type());
    PyModule_AddObject(module, "plAgeLinkEffects", Init_pyAgeLinkEffects_Type());
    PyModule_AddObject(module, "plGrassWave", Init_pyGrassWave_Type());

    /* Creatables */
    PyModule_AddObject(module, "plCreatable", Init_pyCreatable_Type());
    PyModule_AddObject(module, "plCreatableStub", Init_pyCreatableStub_Type());
    PyModule_AddObject(module, "plAgeInfoStruct", Init_pyAgeInfoStruct_Type());
    PyModule_AddObject(module, "plAgeLinkStruct", Init_pyAgeLinkStruct_Type());

    PyModule_AddObject(module, "hsKeyedObject", Init_pyKeyedObject_Type());
    PyModule_AddObject(module, "hsKeyedObjectStub", Init_pyKeyedObjectStub_Type());
    PyModule_AddObject(module, "plSceneNode", Init_pySceneNode_Type());
    PyModule_AddObject(module, "plSynchedObject", Init_pySynchedObject_Type());
    PyModule_AddObject(module, "plSceneObject", Init_pySceneObject_Type());
    PyModule_AddObject(module, "plObjInterface", Init_pyObjInterface_Type());
    PyModule_AddObject(module, "plAudioInterface", Init_pyAudioInterface_Type());
    PyModule_AddObject(module, "plCoordinateInterface", Init_pyCoordinateInterface_Type());
    PyModule_AddObject(module, "plDrawInterface", Init_pyDrawInterface_Type());
    PyModule_AddObject(module, "plSimulationInterface", Init_pySimulationInterface_Type());
    PyModule_AddObject(module, "plDrawable", Init_pyDrawable_Type());
    PyModule_AddObject(module, "plDrawableSpans", Init_pyDrawableSpans_Type());
    PyModule_AddObject(module, "hsGMaterial", Init_pyGMaterial_Type());
    PyModule_AddObject(module, "plLayerInterface", Init_pyLayerInterface_Type());
    PyModule_AddObject(module, "plLayer", Init_pyLayer_Type());
    PyModule_AddObject(module, "plLayerDepth", Init_pyLayerDepth_Type());
    PyModule_AddObject(module, "plShader", Init_pyShader_Type());
    PyModule_AddObject(module, "plBitmap", Init_pyBitmap_Type());
    PyModule_AddObject(module, "plMipmap", Init_pyMipmap_Type());
    PyModule_AddObject(module, "plRenderTarget", Init_pyRenderTarget_Type());
    PyModule_AddObject(module, "plCubicRenderTarget", Init_pyCubicRenderTarget_Type());
    PyModule_AddObject(module, "plLightInfo", Init_pyLightInfo_Type());
    PyModule_AddObject(module, "plDirectionalLightInfo", Init_pyDirectionalLightInfo_Type());
    PyModule_AddObject(module, "plLimitedDirLightInfo", Init_pyLimitedDirLightInfo_Type());
    PyModule_AddObject(module, "plOmniLightInfo", Init_pyOmniLightInfo_Type());
    PyModule_AddObject(module, "plSpotLightInfo", Init_pySpotLightInfo_Type());
    PyModule_AddObject(module, "plSoundBuffer", Init_pySoundBuffer_Type());
    PyModule_AddObject(module, "plPhysical", Init_pyPhysical_Type());
    PyModule_AddObject(module, "plGenericPhysical", Init_pyGenericPhysical_Type());
    PyModule_AddObject(module, "plConditionalObject", Init_pyConditionalObject_Type());
    PyModule_AddObject(module, "plActivatorConditionalObject", Init_pyActivatorConditionalObject_Type());
    PyModule_AddObject(module, "plActivatorActivatorConditionalObject", Init_pyActivatorActivatorConditionalObject_Type());
    PyModule_AddObject(module, "plANDConditionalObject", Init_pyANDConditionalObject_Type());
    PyModule_AddObject(module, "plAnimationEventConditionalObject", Init_pyAnimationEventConditionalObject_Type());
    PyModule_AddObject(module, "plORConditionalObject", Init_pyORConditionalObject_Type());
    PyModule_AddObject(module, "plControlEventConditionalObject", Init_pyControlEventConditionalObject_Type());
    PyModule_AddObject(module, "plFacingConditionalObject", Init_pyFacingConditionalObject_Type());
    PyModule_AddObject(module, "plKeyPressConditionalObject", Init_pyKeyPressConditionalObject_Type());
    PyModule_AddObject(module, "plLocalPlayerInBoxConditionalObject", Init_pyLocalPlayerInBoxConditionalObject_Type());
    PyModule_AddObject(module, "plLocalPlayerIntersectPlaneConditionalObject", Init_pyLocalPlayerIntersectPlaneConditionalObject_Type());
    PyModule_AddObject(module, "plObjectInBoxConditionalObject", Init_pyObjectInBoxConditionalObject_Type());
    PyModule_AddObject(module, "plObjectIntersectPlaneConditionalObject", Init_pyObjectIntersectPlaneConditionalObject_Type());
    PyModule_AddObject(module, "plVolActivatorConditionalObject", Init_pyVolActivatorConditionalObject_Type());
    PyModule_AddObject(module, "plVolumeSensorConditionalObject", Init_pyVolumeSensorConditionalObject_Type());
    PyModule_AddObject(module, "plVolumeSensorConditionalObjectNoArbitration", Init_pyVolumeSensorConditionalObjectNoArbitration_Type());
    PyModule_AddObject(module, "plModifier", Init_pyModifier_Type());
    PyModule_AddObject(module, "plAGModifier", Init_pyAGModifier_Type());
    PyModule_AddObject(module, "plSingleModifier", Init_pySingleModifier_Type());
    PyModule_AddObject(module, "plAGMasterMod", Init_pyAGMasterMod_Type());
    PyModule_AddObject(module, "plSittingModifier", Init_pySittingModifier_Type());
    PyModule_AddObject(module, "plDetectorModifier", Init_pyDetectorModifier_Type());
    PyModule_AddObject(module, "plPickingDetector", Init_pyPickingDetector_Type());
    PyModule_AddObject(module, "plCollisionDetector", Init_pyCollisionDetector_Type());
    PyModule_AddObject(module, "plSubworldRegionDetector", Init_pySubworldRegionDetector_Type());
    PyModule_AddObject(module, "plPanicLinkRegion", Init_pyPanicLinkRegion_Type());
    PyModule_AddObject(module, "plObjectInVolumeDetector", Init_pyObjectInVolumeDetector_Type());
    PyModule_AddObject(module, "plObjectInVolumeAndFacingDetector", Init_pyObjectInVolumeAndFacingDetector_Type());
    PyModule_AddObject(module, "plMultiModifier", Init_pyMultiModifier_Type());
    PyModule_AddObject(module, "plPythonFileMod", Init_pyPythonFileMod_Type());
    PyModule_AddObject(module, "plSpawnModifier", Init_pySpawnModifier_Type());
    PyModule_AddObject(module, "plViewFaceModifier", Init_pyViewFaceModifier_Type());
    PyModule_AddObject(module, "plMaintainersMarkerModifier",
            Init_pyMaintainersMarkerModifier_Type());
    PyModule_AddObject(module, "plExcludeRegionModifier", Init_pyExcludeRegionModifier_Type());
    PyModule_AddObject(module, "plClusterGroup", Init_pyClusterGroup_Type());
    PyModule_AddObject(module, "plLayerAnimationBase", Init_pyLayerAnimationBase_Type());
    PyModule_AddObject(module, "plLayerAnimation", Init_pyLayerAnimation_Type());
    PyModule_AddObject(module, "plLayerLinkAnimation", Init_pyLayerLinkAnimation_Type());
    PyModule_AddObject(module, "plLayerSDLAnimation", Init_pyLayerSDLAnimation_Type());
    PyModule_AddObject(module, "plLayerMovie", Init_pyLayerMovie_Type());
    PyModule_AddObject(module, "plLayerAVI", Init_pyLayerAVI_Type());
    PyModule_AddObject(module, "plLayerBink", Init_pyLayerBink_Type());
    PyModule_AddObject(module, "plOneShotMod", Init_pyOneShotMod_Type());
    PyModule_AddObject(module, "plPostEffectMod", Init_pyPostEffectMod_Type());
    PyModule_AddObject(module, "plResponderModifier", Init_pyResponderModifier_Type());
    PyModule_AddObject(module, "plCubicEnvironmap", Init_pyCubicEnvironmap_Type());
    PyModule_AddObject(module, "plDistOpacityMod", Init_pyDistOpacityMod_Type());
    PyModule_AddObject(module, "plDynamicEnvMap", Init_pyDynamicEnvMap_Type());
    PyModule_AddObject(module, "plDynamicCamMap", Init_pyDynamicCamMap_Type());
    PyModule_AddObject(module, "plDynamicTextMap", Init_pyDynamicTextMap_Type());
    PyModule_AddObject(module, "plFadeOpacityMod", Init_pyFadeOpacityMod_Type());
    PyModule_AddObject(module, "plAGAnim", Init_pyAGAnim_Type());
    PyModule_AddObject(module, "plAgeGlobalAnim", Init_pyAgeGlobalAnim_Type());
    PyModule_AddObject(module, "plATCAnim", Init_pyATCAnim_Type());
    PyModule_AddObject(module, "plEmoteAnim", Init_pyEmoteAnim_Type());
    PyModule_AddObject(module, "plAGAnimBink", Init_pyAGAnimBink_Type());
    PyModule_AddObject(module, "plMsgForwarder", Init_pyMsgForwarder_Type());
    PyModule_AddObject(module, "plOccluder", Init_pyOccluder_Type());
    PyModule_AddObject(module, "plMobileOccluder", Init_pyMobileOccluder_Type());
    PyModule_AddObject(module, "plMultistageBehMod", Init_pyMultistageBehMod_Type());
    PyModule_AddObject(module, "plFollowMod", Init_pyFollowMod_Type());
    PyModule_AddObject(module, "plInterfaceInfoModifier", Init_pyInterfaceInfoModifier_Type());
    PyModule_AddObject(module, "plLogicModBase", Init_pyLogicModBase_Type());
    PyModule_AddObject(module, "plLogicModifier", Init_pyLogicModifier_Type());
    PyModule_AddObject(module, "plAudible", Init_pyAudible_Type());
    PyModule_AddObject(module, "plAudibleNull", Init_pyAudibleNull_Type());
    PyModule_AddObject(module, "plWinAudible", Init_pyWinAudible_Type());
    PyModule_AddObject(module, "pl2WayWinAudible", Init_py2WayWinAudible_Type());
    PyModule_AddObject(module, "plClothingItem", Init_pyClothingItem_Type());
    PyModule_AddObject(module, "plShadowMaster", Init_pyShadowMaster_Type());
    PyModule_AddObject(module, "plPointShadowMaster", Init_pyPointShadowMaster_Type());
    PyModule_AddObject(module, "plDirectShadowMaster", Init_pyDirectShadowMaster_Type());
    PyModule_AddObject(module, "pfGUICtrlProcObject", Init_pyGUICtrlProcObject_Type());
    PyModule_AddObject(module, "pfGUICtrlProcWriteableObject", Init_pyGUICtrlProcWriteableObject_Type());
    PyModule_AddObject(module, "pfGUICloseDlgProc", Init_pyGUICloseDlgProc_Type());
    PyModule_AddObject(module, "pfGUIConsoleCmdProc", Init_pyGUIConsoleCmdProc_Type());
    PyModule_AddObject(module, "pfGUIPythonScriptProc", Init_pyGUIPythonScriptProc_Type());
    PyModule_AddObject(module, "pfGUIColorScheme", Init_pyGUIColorScheme_Type());
    PyModule_AddObject(module, "pfGUIControlMod", Init_pyGUIControlMod_Type());
    PyModule_AddObject(module, "pfGUIValueCtrl", Init_pyGUIValueCtrl_Type());
    PyModule_AddObject(module, "pfGUIButtonMod", Init_pyGUIButtonMod_Type());
    PyModule_AddObject(module, "pfGUICheckBoxCtrl", Init_pyGUICheckBoxCtrl_Type());
    PyModule_AddObject(module, "pfGUIClickMapCtrl", Init_pyGUIClickMapCtrl_Type());
    PyModule_AddObject(module, "pfGUIDialogMod", Init_pyGUIDialogMod_Type());
    PyModule_AddObject(module, "pfGUIDialogProc", Init_pyGUIDialogProc_Type());
    PyModule_AddObject(module, "pfGUIDragBarCtrl", Init_pyGUIDragBarCtrl_Type());
    PyModule_AddObject(module, "pfGUIDraggableMod", Init_pyGUIDraggableMod_Type());
    PyModule_AddObject(module, "pfGUIDynDisplayCtrl", Init_pyGUIDynDisplayCtrl_Type());
    PyModule_AddObject(module, "pfGUIEditBoxMod", Init_pyGUIEditBoxMod_Type());
    PyModule_AddObject(module, "pfGUIKnobCtrl", Init_pyGUIKnobCtrl_Type());
    PyModule_AddObject(module, "pfGUIListBoxMod", Init_pyGUIListBoxMod_Type());
    PyModule_AddObject(module, "pfGUIMenuItem", Init_pyGUIMenuItem_Type());
    PyModule_AddObject(module, "pfGUIMultiLineEditCtrl", Init_pyGUIMultiLineEditCtrl_Type());
    PyModule_AddObject(module, "pfGUIPopUpMenu", Init_pyGUIPopUpMenu_Type());
    PyModule_AddObject(module, "pfGUIProgressCtrl", Init_pyGUIProgressCtrl_Type());
    PyModule_AddObject(module, "pfGUIRadioGroupCtrl", Init_pyGUIRadioGroupCtrl_Type());
    PyModule_AddObject(module, "pfGUISkin", Init_pyGUISkin_Type());
    PyModule_AddObject(module, "pfGUITextBoxMod", Init_pyGUITextBoxMod_Type());
    PyModule_AddObject(module, "pfGUIUpDownPairMod", Init_pyGUIUpDownPairMod_Type());
    PyModule_AddObject(module, "plImageLibMod", Init_pyImageLibMod_Type());
    PyModule_AddObject(module, "plWaveSetBase", Init_pyWaveSetBase_Type());
    PyModule_AddObject(module, "plWaveSet7", Init_pyWaveSet7_Type());
    PyModule_AddObject(module, "plSeekPointMod", Init_pySeekPointMod_Type());
    PyModule_AddObject(module, "plSoftVolume", Init_pySoftVolume_Type());
    PyModule_AddObject(module, "plSoftVolumeSimple", Init_pySoftVolumeSimple_Type());
    PyModule_AddObject(module, "plSoftVolumeComplex", Init_pySoftVolumeComplex_Type());
    PyModule_AddObject(module, "plSoftVolumeIntersect", Init_pySoftVolumeIntersect_Type());
    PyModule_AddObject(module, "plSoftVolumeInvert", Init_pySoftVolumeInvert_Type());
    PyModule_AddObject(module, "plSoftVolumeUnion", Init_pySoftVolumeUnion_Type());
    PyModule_AddObject(module, "plVisRegion", Init_pyVisRegion_Type());
    PyModule_AddObject(module, "plSound", Init_pySound_Type());
    PyModule_AddObject(module, "plWin32Sound", Init_pyWin32Sound_Type());
    PyModule_AddObject(module, "plWin32StreamingSound", Init_pyWin32StreamingSound_Type());
    PyModule_AddObject(module, "plWin32StaticSound", Init_pyWin32StaticSound_Type());
    PyModule_AddObject(module, "plShadowCaster", Init_pyShadowCaster_Type());
    PyModule_AddObject(module, "plSwimRegionInterface", Init_pySwimRegionInterface_Type());
    PyModule_AddObject(module, "plSwimCircularCurrentRegion", Init_pySwimCircularCurrentRegion_Type());
    PyModule_AddObject(module, "plSwimStraightCurrentRegion", Init_pySwimStraightCurrentRegion_Type());
    PyModule_AddObject(module, "plSimpleRegionSensor", Init_pySimpleRegionSensor_Type());
    PyModule_AddObject(module, "plSwimDetector", Init_pySwimDetector_Type());
    PyModule_AddObject(module, "plCameraBrain", Init_pyCameraBrain_Type());
    PyModule_AddObject(module, "plCameraBrain1", Init_pyCameraBrain1_Type());
    PyModule_AddObject(module, "plCameraBrain1_Avatar", Init_pyCameraBrain1_Avatar_Type());
    PyModule_AddObject(module, "plCameraBrain1_FirstPerson", Init_pyCameraBrain1_FirstPerson_Type());
    PyModule_AddObject(module, "plCameraBrain1_Fixed", Init_pyCameraBrain1_Fixed_Type());
    PyModule_AddObject(module, "plCameraBrain1_Circle", Init_pyCameraBrain1_Circle_Type());
    PyModule_AddObject(module, "plCameraRegionDetector", Init_pyCameraRegionDetector_Type());
    PyModule_AddObject(module, "plCameraModifier", Init_pyCameraModifier_Type());
    PyModule_AddObject(module, "plLineFollowMod", Init_pyLineFollowMod_Type());
    PyModule_AddObject(module, "plRailCameraMod", Init_pyRailCameraMod_Type());
    PyModule_AddObject(module, "plAvLadderMod", Init_pyAvLadderMod_Type());
    PyModule_AddObject(module, "plLadderModifier", Init_pyLadderModifier_Type());
    PyModule_AddObject(module, "plFogEnvironment", Init_pyFogEnvironment_Type());
    PyModule_AddObject(module, "plConvexVolume", Init_pyConvexVolume_Type());
    PyModule_AddObject(module, "plBoundInterface", Init_pyBoundInterface_Type());
    PyModule_AddObject(module, "plParticleEffect", Init_pyParticleEffect_Type());
    PyModule_AddObject(module, "plParticleCollisionEffect", Init_pyParticleCollisionEffect_Type());
    PyModule_AddObject(module, "plParticleCollisionEffectBeat", Init_pyParticleCollisionEffectBeat_Type());
    PyModule_AddObject(module, "plParticleCollisionEffectBounce", Init_pyParticleCollisionEffectBounce_Type());
    PyModule_AddObject(module, "plParticleCollisionEffectDie", Init_pyParticleCollisionEffectDie_Type());
    PyModule_AddObject(module, "plParticleFadeOutEffect", Init_pyParticleFadeOutEffect_Type());
    PyModule_AddObject(module, "plParticleFadeVolumeEffect", Init_pyParticleFadeVolumeEffect_Type());
    PyModule_AddObject(module, "plParticleFlockEffect", Init_pyParticleFlockEffect_Type());
    PyModule_AddObject(module, "plParticleFollowSystemEffect", Init_pyParticleFollowSystemEffect_Type());
    PyModule_AddObject(module, "plParticleWindEffect", Init_pyParticleWindEffect_Type());
    PyModule_AddObject(module, "plParticleLocalWind", Init_pyParticleLocalWind_Type());
    PyModule_AddObject(module, "plParticleUniformWind", Init_pyParticleUniformWind_Type());
    PyModule_AddObject(module, "plParticleGenerator", Init_pyParticleGenerator_Type());
    PyModule_AddObject(module, "plOneTimeParticleGenerator", Init_pyOneTimeParticleGenerator_Type());
    PyModule_AddObject(module, "plSimpleParticleGenerator", Init_pySimpleParticleGenerator_Type());
    PyModule_AddObject(module, "plParticleEmitter", Init_pyParticleEmitter_Type());
    PyModule_AddObject(module, "plParticleSystem", Init_pyParticleSystem_Type());
    PyModule_AddObject(module, "plHKSubWorld", Init_pyHKSubWorld_Type());
    PyModule_AddObject(module, "plFilterCoordInterface", Init_pyFilterCoordInterface_Type());
    PyModule_AddObject(module, "plRidingAnimatedPhysicalDetector", Init_pyRidingAnimatedPhysicalDetector_Type());
    PyModule_AddObject(module, "plDynaDecalMgr", Init_pyDynaDecalMgr_Type());
    PyModule_AddObject(module, "plDynaBulletMgr", Init_pyDynaBulletMgr_Type());
    PyModule_AddObject(module, "plDynaFootMgr", Init_pyDynaFootMgr_Type());
    PyModule_AddObject(module, "plDynaRippleMgr", Init_pyDynaRippleMgr_Type());
    PyModule_AddObject(module, "plDynaRippleVSMgr", Init_pyDynaRippleVSMgr_Type());
    PyModule_AddObject(module, "plDynaTorpedoMgr", Init_pyDynaTorpedoMgr_Type());
    PyModule_AddObject(module, "plDynaTorpedoVSMgr", Init_pyDynaTorpedoVSMgr_Type());
    PyModule_AddObject(module, "plDynaPuddleMgr", Init_pyDynaPuddleMgr_Type());
    PyModule_AddObject(module, "plDynaWakeMgr", Init_pyDynaWakeMgr_Type());
    PyModule_AddObject(module, "plFont", Init_pyFont_Type());
    PyModule_AddObject(module, "plPrintShape", Init_pyPrintShape_Type());
    PyModule_AddObject(module, "plActivePrintShape", Init_pyActivePrintShape_Type());
    PyModule_AddObject(module, "plGrassShaderMod", Init_pyGrassShaderMod_Type());

    PyModule_AddObject(module, "plSharedMesh", Init_pySharedMesh_Type());
    PyModule_AddObject(module, "plSpaceTree", Init_pySpaceTree_Type());
    PyModule_AddObject(module, "plController", Init_pyController_Type());
    PyModule_AddObject(module, "plCompoundController", Init_pyCompoundController_Type());
    PyModule_AddObject(module, "plTMController", Init_pyTMController_Type());
    PyModule_AddObject(module, "plPosController", Init_pyPosController_Type());
    PyModule_AddObject(module, "plSimplePosController", Init_pySimplePosController_Type());
    PyModule_AddObject(module, "plCompoundPosController", Init_pyCompoundPosController_Type());
    PyModule_AddObject(module, "plRotController", Init_pyRotController_Type());
    PyModule_AddObject(module, "plSimpleRotController", Init_pySimpleRotController_Type());
    PyModule_AddObject(module, "plCompoundRotController", Init_pyCompoundRotController_Type());
    PyModule_AddObject(module, "plScaleController", Init_pyScaleController_Type());
    PyModule_AddObject(module, "plSimpleScaleController", Init_pySimpleScaleController_Type());
    PyModule_AddObject(module, "plLeafController", Init_pyLeafController_Type());
    PyModule_AddObject(module, "plEaseController", Init_pyEaseController_Type());
    PyModule_AddObject(module, "plMatrix33Controller", Init_pyMatrix33Controller_Type());
    PyModule_AddObject(module, "plMatrix44Controller", Init_pyMatrix44Controller_Type());
    PyModule_AddObject(module, "plPoint3Controller", Init_pyPoint3Controller_Type());
    PyModule_AddObject(module, "plQuatController", Init_pyQuatController_Type());
    PyModule_AddObject(module, "plScalarController", Init_pyScalarController_Type());
    PyModule_AddObject(module, "plScaleValueController", Init_pyScaleValueController_Type());
    PyModule_AddObject(module, "plATCEaseCurve", Init_pyATCEaseCurve_Type());
    PyModule_AddObject(module, "plSplineEaseCurve", Init_pySplineEaseCurve_Type());
    PyModule_AddObject(module, "plConstAccelEaseCurve", Init_pyConstAccelEaseCurve_Type());
    PyModule_AddObject(module, "plAnimTimeConvert", Init_pyAnimTimeConvert_Type());
    PyModule_AddObject(module, "plMessage", Init_pyMessage_Type());
    PyModule_AddObject(module, "plCursorChangeMsg", Init_pyCursorChangeMsg_Type());
    PyModule_AddObject(module, "plEventCallbackMsg", Init_pyEventCallbackMsg_Type());
    PyModule_AddObject(module, "plResponderEnableMsg", Init_pyResponderEnableMsg_Type());
    PyModule_AddObject(module, "plAGApplicator", Init_pyAGApplicator_Type());
    PyModule_AddObject(module, "plAGChannel", Init_pyAGChannel_Type());
    PyModule_AddObject(module, "plSoundVolumeApplicator", Init_pySoundVolumeApplicator_Type());
    PyModule_AddObject(module, "plLightAmbientApplicator", Init_pyLightAmbientApplicator_Type());
    PyModule_AddObject(module, "plLightDiffuseApplicator", Init_pyLightDiffuseApplicator_Type());
    PyModule_AddObject(module, "plLightSpecularApplicator", Init_pyLightSpecularApplicator_Type());
    PyModule_AddObject(module, "plOmniApplicator", Init_pyOmniApplicator_Type());
    PyModule_AddObject(module, "plOmniCutoffApplicator", Init_pyOmniCutoffApplicator_Type());
    PyModule_AddObject(module, "plOmniSqApplicator", Init_pyOmniSqApplicator_Type());
    PyModule_AddObject(module, "plSpotInnerApplicator", Init_pySpotInnerApplicator_Type());
    PyModule_AddObject(module, "plSpotOuterApplicator", Init_pySpotOuterApplicator_Type());
    PyModule_AddObject(module, "plMatrixChannel", Init_pyMatrixChannel_Type());
    PyModule_AddObject(module, "plMatrixBlend", Init_pyMatrixBlend_Type());
    PyModule_AddObject(module, "plMatrixConstant", Init_pyMatrixConstant_Type());
    PyModule_AddObject(module, "plMatrixControllerCacheChannel", Init_pyMatrixControllerCacheChannel_Type());
    PyModule_AddObject(module, "plMatrixControllerChannel", Init_pyMatrixControllerChannel_Type());
    PyModule_AddObject(module, "plMatrixTimeScale", Init_pyMatrixTimeScale_Type());
    PyModule_AddObject(module, "plQuatPointCombine", Init_pyQuatPointCombine_Type());
    PyModule_AddObject(module, "plMatrixChannelApplicator", Init_pyMatrixChannelApplicator_Type());
    PyModule_AddObject(module, "plMatrixDelayedCorrectionApplicator", Init_pyMatrixDelayedCorrectionApplicator_Type());
    PyModule_AddObject(module, "plMatrixDifferenceApp", Init_pyMatrixDifferenceApp_Type());
    PyModule_AddObject(module, "plRelativeMatrixChannelApplicator", Init_pyRelativeMatrixChannelApplicator_Type());
    PyModule_AddObject(module, "plPointChannel", Init_pyPointChannel_Type());
    PyModule_AddObject(module, "plPointBlend", Init_pyPointBlend_Type());
    PyModule_AddObject(module, "plPointConstant", Init_pyPointConstant_Type());
    PyModule_AddObject(module, "plPointControllerCacheChannel", Init_pyPointControllerCacheChannel_Type());
    PyModule_AddObject(module, "plPointControllerChannel", Init_pyPointControllerChannel_Type());
    PyModule_AddObject(module, "plPointTimeScale", Init_pyPointTimeScale_Type());
    PyModule_AddObject(module, "plPointChannelApplicator", Init_pyPointChannelApplicator_Type());
    PyModule_AddObject(module, "plQuatChannel", Init_pyQuatChannel_Type());
    PyModule_AddObject(module, "plQuatBlend", Init_pyQuatBlend_Type());
    PyModule_AddObject(module, "plQuatConstant", Init_pyQuatConstant_Type());
    PyModule_AddObject(module, "plQuatTimeScale", Init_pyQuatTimeScale_Type());
    PyModule_AddObject(module, "plQuatChannelApplicator", Init_pyQuatChannelApplicator_Type());
    PyModule_AddObject(module, "plScalarChannel", Init_pyScalarChannel_Type());
    PyModule_AddObject(module, "plScalarBlend", Init_pyScalarBlend_Type());
    PyModule_AddObject(module, "plScalarConstant", Init_pyScalarConstant_Type());
    PyModule_AddObject(module, "plScalarControllerCacheChannel", Init_pyScalarControllerCacheChannel_Type());
    PyModule_AddObject(module, "plScalarControllerChannel", Init_pyScalarControllerChannel_Type());
    PyModule_AddObject(module, "plScalarTimeScale", Init_pyScalarTimeScale_Type());
    PyModule_AddObject(module, "plScalarSDLChannel", Init_pyScalarSDLChannel_Type());
    PyModule_AddObject(module, "plATCChannel", Init_pyATCChannel_Type());
    PyModule_AddObject(module, "plScalarChannelApplicator", Init_pyScalarChannelApplicator_Type());
    PyModule_AddObject(module, "plAnimStage", Init_pyAnimStage_Type());
    PyModule_AddObject(module, "plLinkToAgeMsg", Init_pyLinkToAgeMsg_Type());
    PyModule_AddObject(module, "plNotifyMsg", Init_pyNotifyMsg_Type());
    PyModule_AddObject(module, "plArmatureEffectStateMsg", Init_pyArmatureEffectStateMsg_Type());
    PyModule_AddObject(module, "plResponderMsg", Init_pyResponderMsg_Type());
    PyModule_AddObject(module, "plOneShotMsg", Init_pyOneShotMsg_Type());
    PyModule_AddObject(module, "plMessageWithCallbacks", Init_pyMessageWithCallbacks_Type());
    PyModule_AddObject(module, "plAnimCmdMsg", Init_pyAnimCmdMsg_Type());
    PyModule_AddObject(module, "plTimerCallbackMsg", Init_pyTimerCallbackMsg_Type());
    PyModule_AddObject(module, "plWarpMsg", Init_pyWarpMsg_Type());
    PyModule_AddObject(module, "plEnableMsg", Init_pyEnableMsg_Type());
    PyModule_AddObject(module, "plExcludeRegionMsg", Init_pyExcludeRegionMsg_Type());
    PyModule_AddObject(module, "plVolumeIsect", Init_pyVolumeIsect_Type());
    PyModule_AddObject(module, "plConvexIsect", Init_pyConvexIsect_Type());
    PyModule_AddObject(module, "plSoundMsg", Init_pySoundMsg_Type());
    PyModule_AddObject(module, "plSwimMsg", Init_pySwimMsg_Type());
    PyModule_AddObject(module, "plCameraMsg", Init_pyCameraMsg_Type());
    PyModule_AddObject(module, "plAnimPath", Init_pyAnimPath_Type());
    PyModule_AddObject(module, "plParticleApplicator", Init_pyParticleApplicator_Type());
    PyModule_AddObject(module, "plParticleAngleApplicator", Init_pyParticleAngleApplicator_Type());
    PyModule_AddObject(module, "plParticleLifeMinApplicator", Init_pyParticleLifeMinApplicator_Type());
    PyModule_AddObject(module, "plParticleLifeMaxApplicator", Init_pyParticleLifeMaxApplicator_Type());
    PyModule_AddObject(module, "plParticlePPSApplicator", Init_pyParticlePPSApplicator_Type());
    PyModule_AddObject(module, "plParticleScaleMinApplicator", Init_pyParticleScaleMinApplicator_Type());
    PyModule_AddObject(module, "plParticleScaleMaxApplicator", Init_pyParticleScaleMaxApplicator_Type());
    PyModule_AddObject(module, "plParticleVelMinApplicator", Init_pyParticleVelMinApplicator_Type());
    PyModule_AddObject(module, "plParticleVelMaxApplicator", Init_pyParticleVelMaxApplicator_Type());
    PyModule_AddObject(module, "plSimulationMsg", Init_pySimulationMsg_Type());
    PyModule_AddObject(module, "plSubWorldMsg", Init_pySubWorldMsg_Type());
    PyModule_AddObject(module, "plRideAnimatedPhysMsg", Init_pyRideAnimatedPhysMsg_Type());
    PyModule_AddObject(module, "plSimSuppressMsg", Init_pySimSuppressMsg_Type());

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
