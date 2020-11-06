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

#include "plPythonFileMod.h"

/* plPythonParameter */
const char* plPythonParameter::ValueTypeNames[] = {
    "(Invalid)",
    "Int", "Float", "Boolean", "String", "SceneObject", "SceneObjectList",
    "Activator", "Responder", "DynamicText", "GUIDialog", "ExcludeRegion",
    "Animation", "AnimationName", "Behavior", "Material", "GUIPopUpMenu",
    "GUISkin", "WaterComponent", "SwimCurrentInterface", "ClusterComponent",
    "MaterialAnimation", "GrassShaderComponent", "GlobalSDLVar", "Subtitle",
    "BlowerComponent", "None"
};

plPythonParameter& plPythonParameter::operator=(const plPythonParameter& init)
{
    fID = init.fID;
    fValueType = init.fValueType;

    switch (fValueType) {
    case kInt:
        fIntValue = init.fIntValue;
        break;
    case kBoolean:
        fBoolValue = init.fBoolValue;
        break;
    case kFloat:
        fFloatValue = init.fFloatValue;
        break;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        fStrValue = init.fStrValue;
        break;
    case kNone:
        break;
    default:
        fObjKey = init.fObjKey;
        break;
    }

    return *this;
}

void plPythonParameter::read(hsStream* S, plResManager* mgr)
{
    fID = S->readInt();
    fValueType = PlasmaToMapped(S->readInt(), S->getVer());
    if (fValueType > kNone || fValueType == 0)
        throw hsBadParamException(__FILE__, __LINE__);

    int size = 0;
    switch (fValueType) {
    case kInt:
        fIntValue = S->readInt();
        return;
    case kBoolean:
        fBoolValue = (S->readInt() != 0);
        return;
    case kFloat:
        fFloatValue = S->readFloat();
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        size = S->readInt();
        if (size == 0) {
            fStrValue = ST::string();
            return;
        }
        fStrValue = S->readStr(size - 1);
        S->readByte();
        return;
    case kNone:
        return;
    default:
        fObjKey = mgr->readKey(S);
        return;
    }
}

void plPythonParameter::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fID);
    S->writeInt(MappedToPlasma(fValueType, S->getVer()));

    switch (fValueType) {
    case kInt:
        S->writeInt(fIntValue);
        return;
    case kBoolean:
        S->writeInt(fBoolValue ? 1 : 0);
        return;
    case kFloat:
        S->writeFloat(fFloatValue);
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        S->writeInt(fStrValue.size() + 1);
        S->writeStr(fStrValue);
        S->writeByte(0);
        return;
    case kNone:
        return;
    default:
        mgr->writeKey(S, fObjKey);
        return;
    }
}

void plPythonParameter::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plPythonParameter");

    prc->writeParam("ID", fID);
    prc->writeParam("Type", ValueTypeNames[fValueType]);

    switch (fValueType) {
    case kInt:
        prc->writeParam("Value", fIntValue);
        prc->endTag(true);
        return;
    case kBoolean:
        prc->writeParam("Value", fBoolValue);
        prc->endTag(true);
        return;
    case kFloat:
        prc->writeParam("Value", fFloatValue);
        prc->endTag(true);
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        prc->writeParam("Value", fStrValue);
        prc->endTag(true);
        return;
    case kNone:
        prc->endTag(true);
        return;
    default:
        prc->endTag(false);
        plResManager::PrcWriteKey(prc, fObjKey);
        prc->closeTag();
        return;
    }
}

void plPythonParameter::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() != "plPythonParameter")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fID = tag->getParam("ID", "0").to_uint();
    ST::string valTypeName = tag->getParam("Type", "(Invalid)");
    fValueType = 0;
    for (size_t i=0; i<=kNone; i++) {
        if (valTypeName == ValueTypeNames[i])
            fValueType = i;
    }
    if (fValueType == 0)
        throw pfPrcParseException(__FILE__, __LINE__, "Invalid parameter type");

    switch (fValueType) {
    case kInt:
        fIntValue = tag->getParam("Value", "0").to_int();
        return;
    case kBoolean:
        fBoolValue = tag->getParam("Value", "false").to_bool();
        return;
    case kFloat:
        fFloatValue = tag->getParam("Value", "0").to_float();
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        fStrValue = tag->getParam("Value", "");
        return;
    case kNone:
        return;
    default:
        if (tag->hasChildren())
            fObjKey = mgr->prcParseKey(tag->getFirstChild());
        return;
    }
}

unsigned int plPythonParameter::PlasmaToMapped(unsigned int type, PlasmaVer ver)
{
    if (!ver.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (ver.isUniversal() || type < 20)
        return type;
    if (ver.isNewPlasma()) {
        switch (type) {
        case 20: return kGlobalSDLVar;
        case 21: return kMaterialAnimation;
        case 22: return kClusterComponent;
        case 23: return kSubtitle;
        case 24: return kBlowerComponent;
        case 25: return kGrassShaderComponent;
        case 26: return kNone;
        default: return 0;
        }
    } else {
        switch (type) {
        case 20: return kClusterComponent;
        case 21: return kMaterialAnimation;
        case 22: return kGrassShaderComponent;
        case 23: return kNone;
        default: return 0;
        }
    }
}

unsigned int plPythonParameter::MappedToPlasma(unsigned int type, PlasmaVer ver)
{
    if (!ver.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (ver.isUniversal() || type < 20)
        return type;
    if (ver.isNewPlasma()) {
        switch (type) {
        case kGlobalSDLVar: return 20;
        case kMaterialAnimation: return 21;
        case kClusterComponent: return 22;
        case kSubtitle: return 23;
        case kBlowerComponent: return 24;
        case kGrassShaderComponent: return 25;
        case kNone: return 26;
        default: return 0;
        }
    } else {
        switch (type) {
        case kClusterComponent: return 20;
        case kMaterialAnimation: return 21;
        case kGrassShaderComponent: return 22;
        case kNone: return 23;
        default: return 0;
        }
    }
}


/* plPythonFileMod */
void plPythonFileMod::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);
    fPythonFile = S->readSafeStr();

    fReceivers.resize(S->readInt());
    for (size_t i=0; i<fReceivers.size(); i++)
        fReceivers[i] = mgr->readKey(S);

    fParameters.resize(S->readInt());
    for (size_t i=0; i<fParameters.size(); i++)
        fParameters[i].read(S, mgr);
}

void plPythonFileMod::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);
    S->writeSafeStr(fPythonFile);

    S->writeInt(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        mgr->writeKey(S, fReceivers[i]);

    S->writeInt(fParameters.size());
    for (size_t i=0; i<fParameters.size(); i++)
        fParameters[i].write(S, mgr);
}

void plPythonFileMod::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("PythonFile");
    prc->writeParam("name", fPythonFile);
    prc->endTag(true);

    size_t i;
    prc->writeSimpleTag("Receivers");
    for (i=0; i<fReceivers.size(); i++)
        plResManager::PrcWriteKey(prc, fReceivers[i]);
    prc->closeTag();

    prc->writeSimpleTag("Parameters");
    for (i=0; i<fParameters.size(); i++)
        fParameters[i].prcWrite(prc);
    prc->closeTag();
}

void plPythonFileMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if  (tag->getName() == "PythonFile") {
        fPythonFile = tag->getParam("name", "");
    } else if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Parameters") {
        fParameters.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fParameters.size(); i++) {
            fParameters[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
