#include "plLayer.h"

/* plLayer */
void plLayer::read(hsStream* S, plResManager* mgr) {
    plLayerInterface::read(S, mgr);
    fState.read(S);
    fTransform.read(S);

    fPreshade.read(S);
    fRuntime.read(S);
    fAmbient.read(S);
    fSpecular.read(S);

    fUVWSrc = S->readInt();
    fOpacity = S->readFloat();
    fLODBias = S->readFloat();
    fSpecularPower = S->readFloat();

    fTexture = mgr->readKey(S);
    fVertexShader = mgr->readKey(S);
    fPixelShader = mgr->readKey(S);
    fBumpEnvXfm.read(S);
}

void plLayer::write(hsStream* S, plResManager* mgr) {
    plLayerInterface::write(S, mgr);
    fState.write(S);
    fTransform.write(S);

    fPreshade.write(S);
    fRuntime.write(S);
    fAmbient.write(S);
    fSpecular.write(S);

    S->writeInt(fUVWSrc);
    S->writeFloat(fOpacity);
    S->writeFloat(fLODBias);
    S->writeFloat(fSpecularPower);

    mgr->writeKey(S, fTexture);
    mgr->writeKey(S, fVertexShader);
    mgr->writeKey(S, fPixelShader);
    fBumpEnvXfm.write(S);
}

void plLayer::IPrcWrite(pfPrcHelper* prc) {
    plLayerInterface::IPrcWrite(prc);

    fState.prcWrite(prc);
    prc->writeSimpleTag("Transform");
      fTransform.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Preshade");
      fPreshade.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Runtime");
      fRuntime.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Ambient");
      fAmbient.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
      fSpecular.prcWrite(prc);
    prc->closeTag();

    prc->startTag("LayerParams");
    prc->writeParam("UVWSrc", fUVWSrc);
    prc->writeParam("Opacity", fOpacity);
    prc->writeParam("LODBias", fLODBias);
    prc->writeParam("SpecularPower", fSpecularPower);
    prc->endTag(true);

    prc->writeSimpleTag("Texture");
      fTexture->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("VertexShader");
      fVertexShader->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PixelShader");
      fPixelShader->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("BumpEnvXfm");
      fBumpEnvXfm.prcWrite(prc);
    prc->closeTag();
}

void plLayer::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "hsGMatState") {
        fState.prcParse(tag);
    } else if (tag->getName() == "Transform") {
        if (tag->hasChildren())
            fTransform.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Preshade") {
        if (tag->hasChildren())
            fPreshade.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Runtime") {
        if (tag->hasChildren())
            fRuntime.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Ambient") {
        if (tag->hasChildren())
            fAmbient.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Specular") {
        if (tag->hasChildren())
            fSpecular.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LayerParams") {
        fUVWSrc = tag->getParam("UVWSrc", "0").toUint();
        fOpacity = tag->getParam("Opacity", "0").toFloat();
        fLODBias = tag->getParam("LODBias", "0").toFloat();
        fSpecularPower = tag->getParam("SpecularPower", "0").toFloat();
    } else if (tag->getName() == "Texture") {
        if (tag->hasChildren())
            fTexture = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "VertexShader") {
        if (tag->hasChildren())
            fVertexShader = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "PixelShader") {
        if (tag->hasChildren())
            fPixelShader = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "BumpEnvXfm") {
        if (tag->hasChildren())
            fBumpEnvXfm.prcParse(tag->getFirstChild());
    } else {
        plLayerInterface::IPrcParse(tag, mgr);
    }
}
