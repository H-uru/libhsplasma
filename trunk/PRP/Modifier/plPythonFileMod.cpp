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

plPythonParameter::plPythonParameter() : fID(0), fValueType(kNone) { }

plPythonParameter::~plPythonParameter() { }

void plPythonParameter::read(hsStream* S, plResManager* mgr) {
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
            fStrValue = "";
            return;
        }
        fStrValue = S->readStr(size);
        return;
    case kNone:
        return;
    default:
        fObjKey = mgr->readKey(S);
        return;
    }
}

void plPythonParameter::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fID);
    S->writeInt(MappedToPlasma(fValueType, S->getVer()));

    switch (fValueType) {
    case kInt:
        S->writeInt(fIntValue);
        return;
    case kBoolean:
        if (fBoolValue)
            S->writeInt(1);
        else
            S->writeInt(0);
        return;
    case kFloat:
        S->writeFloat(fFloatValue);
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        S->writeInt(fStrValue.len() + 1);
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

void plPythonParameter::prcWrite(pfPrcHelper* prc) {
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
        fObjKey->prcWrite(prc);
        prc->closeTag();
        return;
    }
}

void plPythonParameter::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "plPythonParameter")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fID = tag->getParam("ID", "0").toUint();
    plString valTypeName = tag->getParam("Type", "(Invalid)");
    fValueType = 0;
    for (size_t i=0; i<=kNone; i++) {
        if (valTypeName == ValueTypeNames[i])
            fValueType = i;
    }
    if (fValueType == 0)
        throw pfPrcParseException(__FILE__, __LINE__, "Invalid parameter type");

    switch (fValueType) {
    case kInt:
        fIntValue = tag->getParam("Value", "0").toInt();
        return;
    case kBoolean:
        fBoolValue = tag->getParam("Value", "false").toBool();
        return;
    case kFloat:
        fFloatValue = tag->getParam("Value", "0").toFloat();
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

unsigned int plPythonParameter::PlasmaToMapped(unsigned int type, PlasmaVer ver) {
    if (ver == pvUnknown)
        throw hsBadVersionException(__FILE__, __LINE__);
    if (type < 20)
        return type;
    if (ver >= pvEoa) {
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

unsigned int plPythonParameter::MappedToPlasma(unsigned int type, PlasmaVer ver) {
    if (ver == pvUnknown)
        throw hsBadVersionException(__FILE__, __LINE__);
    if (type < 20)
        return type;
    if (ver >= pvEoa) {
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
plPythonFileMod::plPythonFileMod() { }
plPythonFileMod::~plPythonFileMod() { }

IMPLEMENT_CREATABLE(plPythonFileMod, kPythonFileMod, plMultiModifier)

const plString& plPythonFileMod::getFilename() const { return fPythonFile; }
const hsTArray<plWeakKey>& plPythonFileMod::getReceivers() const { return fReceivers; }
const hsTArray<plPythonParameter>& plPythonFileMod::getParameters() const { return fParameters; }

void plPythonFileMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    fPythonFile = S->readSafeStr();

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);

    fParameters.setSize(S->readInt());
    for (size_t i=0; i<fParameters.getSize(); i++)
        fParameters[i].read(S, mgr);
}

void plPythonFileMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    S->writeSafeStr(fPythonFile);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);

    S->writeInt(fParameters.getSize());
    for (size_t i=0; i<fParameters.getSize(); i++)
        fParameters[i].write(S, mgr);
}

void plPythonFileMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("PythonFile");
    prc->writeParam("name", fPythonFile);
    prc->endTag(true);

    size_t i;
    prc->writeSimpleTag("Receivers");
    for (i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("Parameters");
    for (i=0; i<fParameters.getSize(); i++)
        fParameters[i].prcWrite(prc);
    prc->closeTag();
}

void plPythonFileMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if  (tag->getName() == "PythonFile") {
        fPythonFile = tag->getParam("name", "");
    } else if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Parameters") {
        fParameters.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fParameters.getSize(); i++) {
            fParameters[i].prcParse(tag, mgr);
            child = child->getNextSibling();
        }
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
