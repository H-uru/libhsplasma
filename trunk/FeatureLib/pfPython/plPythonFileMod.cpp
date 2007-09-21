#include "plPythonFileMod.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

/* plPythonParameter */

const char* plPythonParameter::valueTypeNames[] = {
    "(Invalid)",
    "Int", "Float", "Boolean", "String", "SceneObject", "SceneObjectList",
    "Activator", "Responder", "DynamicText", "GUIDialog", "ExcludeRegion",
    "Animation", "AnimationName", "Behavior", "Material", "GUIPopUpMenu",
    "GUISkin", "WaterComponent", "SwimCurrentInterface", "ClusterComponent",
    "MaterialAnimation", "GrassShaderComponent", "GlobalSDLVar", "Subtitle",
    "BlowerComponent", "None"
};

plPythonParameter::plPythonParameter(PlasmaVer pv) : ID(0), valueType(kNone) { }

plPythonParameter::~plPythonParameter() { }

void plPythonParameter::read(hsStream* S, plResManager* mgr) {
    ID = S->readInt();
    valueType = PlasmaToMapped(S->readInt(), S->getVer());

    int size = 0;
    switch (valueType) {
    case kInt:
        intValue = S->readInt();
        return;
    case kBoolean:
        boolValue = (S->readInt() != 0);
        return;
    case kFloat:
        floatValue = S->readFloat();
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        size = S->readInt();
        if (size == 0) {
            strValue = "";
            return;
        }
        strValue = S->readStr(size);
        return;
    case kNone:
        return;
    default:
        objKey = mgr->readKey(S);
        return;
    }
}

void plPythonParameter::write(hsStream* S, plResManager* mgr) {
    S->writeInt(ID);
    S->writeInt(MappedToPlasma(valueType, S->getVer()));

    int lb = 0, size = 0;
    switch (valueType) {
    case kInt:
        S->writeInt(intValue);
        return;
    case kBoolean:
        if (boolValue) lb = 1;
        S->writeInt(lb);
        return;
    case kFloat:
        S->writeFloat(floatValue);
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        size = strlen(strValue);
        S->writeInt(size);
        S->write(size, strValue);
        return;
    case kNone:
        return;
    default:
        mgr->writeKey(S, objKey);
        return;
    }
}

void plPythonParameter::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plPythonParameter");
    
    prc->writeParam("ID", ID);
    prc->writeParam("Type", valueTypeNames[valueType]);
    
    switch (valueType) {
    case kInt:
        prc->writeParam("Value", intValue);
        prc->endTag(true);
        return;
    case kBoolean:
        prc->writeParam("Value", boolValue);
        prc->endTag(true);
        return;
    case kFloat:
        prc->writeParam("Value", floatValue);
        prc->endTag(true);
        return;
    case kString:
    case kAnimationName:
    case kGlobalSDLVar:
    case kSubtitle:
        prc->writeParam("Value", strValue);
        prc->endTag(true);
        return;
    case kNone:
        prc->endTag(true);
        return;
    default:
        prc->endTag(false);
        objKey->prcWrite(prc);
        prc->closeTag();
        return;
    }
}

unsigned int plPythonParameter::PlasmaToMapped(unsigned int type, PlasmaVer ver) {
    if (ver == pvUnknown)
        throw hsBadVersionException(__FILE__, __LINE__);
    if (type < 20)
        return type;
    if (ver == pvEoa) {
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
    if (ver == pvEoa) {
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

plString& plPythonFileMod::getFilename() { return pythonFile; }
hsTArray<plKey>& plPythonFileMod::getReceivers() { return receivers; }
hsTArray<plPythonParameter>& plPythonFileMod::getParameters() { return parameters; }

void plPythonFileMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    pythonFile = S->readSafeStr();

    size_t i, count = S->readInt();
    receivers.setSize(count);
    for (i=0; i<count; i++)
        receivers[i] = mgr->readKey(S);

    count = S->readInt();
    parameters.setSize(count);
    for (i=0; i<count; i++)
        parameters[i].read(S, mgr);
}

void plPythonFileMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    S->writeSafeStr(pythonFile);

    size_t i;
    S->writeInt(receivers.getSize());
    for (i=0; i<receivers.getSize(); i++)
        mgr->writeKey(S, receivers[i]);

    S->writeInt(parameters.getSize());
    for (i=0; i<parameters.getSize(); i++)
        parameters[i].write(S, mgr);
}

void plPythonFileMod::prcWrite(pfPrcHelper* prc) {
    plMultiModifier::prcWrite(prc);

    prc->startTag("PythonFile");
    prc->writeParam("name", pythonFile);
    prc->endTag(true);

    size_t i;
    prc->writeSimpleTag("Receivers");
    for (i=0; i<receivers.getSize(); i++)
        receivers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("Parameters");
    for (i=0; i<parameters.getSize(); i++)
        parameters[i].prcWrite(prc);
    prc->closeTag();
}
