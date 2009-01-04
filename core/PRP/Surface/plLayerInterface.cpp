#include "plLayerInterface.h"

plLayerInterface::plLayerInterface()
                : fOpacity(1.0f), fUVWSrc(0), fLODBias(0.0f), fSpecularPower(0.0f) { }

plLayerInterface::~plLayerInterface() { }

IMPLEMENT_CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

void plLayerInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fUnderLay = mgr->readKey(S);
}

void plLayerInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fUnderLay);
}

void plLayerInterface::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("BaseLayer");
    fUnderLay->prcWrite(prc);
    prc->closeTag();
}

void plLayerInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BaseLayer") {
        if (tag->hasChildren())
            fUnderLay = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

plKey plLayerInterface::getUnderLay() const { return fUnderLay; }
plKey plLayerInterface::getTexture() const { return fTexture; }
plKey plLayerInterface::getVertexShader() const { return fVertexShader; }
plKey plLayerInterface::getPixelShader() const { return fPixelShader; }
void plLayerInterface::setUnderLay(plKey layer) { fUnderLay = layer; }
void plLayerInterface::setTexture(plKey tex) { fTexture = tex; }
void plLayerInterface::setVertexShader(plKey shader) { fVertexShader = shader; }
void plLayerInterface::setPixelShader(plKey shader) { fPixelShader = shader; }

hsMatrix44 plLayerInterface::getTransform() const { return fTransform; }
hsMatrix44 plLayerInterface::getBumpEnvTransform() const { return fBumpEnvXfm; }
void plLayerInterface::setTransform(const hsMatrix44& xform) { fTransform = xform; }
void plLayerInterface::setBumpEnvTransform(const hsMatrix44& xform) { fBumpEnvXfm =  xform; }

hsColorRGBA plLayerInterface::getPreshade() const { return fPreshade; }
hsColorRGBA plLayerInterface::getRuntime() const { return fRuntime; }
hsColorRGBA plLayerInterface::getAmbient() const { return fAmbient; }
hsColorRGBA plLayerInterface::getSpecular() const { return fSpecular; }
void plLayerInterface::setPreshade(const hsColorRGBA& color) { fPreshade = color; }
void plLayerInterface::setRuntime(const hsColorRGBA& color) { fRuntime = color; }
void plLayerInterface::setAmbient(const hsColorRGBA& color) { fAmbient = color; }
void plLayerInterface::setSpecular(const hsColorRGBA& color) { fSpecular = color; }

float plLayerInterface::getOpacity() const { return fOpacity; }
unsigned int plLayerInterface::getUVWSrc() const { return fUVWSrc; }
float plLayerInterface::getLODBias() const { return fLODBias; }
float plLayerInterface::getSpecularPower() const { return fSpecularPower; }
void plLayerInterface::setOpacity(float opac) { fOpacity = opac; }
void plLayerInterface::setUVWSrc(unsigned int src) { fUVWSrc = src; }
void plLayerInterface::setLODBias(float bias) { fLODBias = bias; }
void plLayerInterface::setSpecularPower(float power) { fSpecularPower = power; }

hsGMatState& plLayerInterface::getState() { return fState; }
void plLayerInterface::setState(hsGMatState& state) { fState = state; }
