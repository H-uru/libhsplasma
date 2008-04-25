#include "plLayer.h"

/* plLayer */
plLayer::plLayer() { }
plLayer::~plLayer() { }

IMPLEMENT_CREATABLE(plLayer, kLayer, plLayerInterface)

void plLayer::read(hsStream* S, plResManager* mgr) {
    plLayerInterface::read(S, mgr);
    fState.read(S);
    fTransform.read(S);

    fPreshadeColor.read(S);
    fRuntimeColor.read(S);
    fAmbientColor.read(S);
    fSpecularColor.read(S);

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

    fPreshadeColor.write(S);
    fRuntimeColor.write(S);
    fAmbientColor.write(S);
    fSpecularColor.write(S);

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
      fPreshadeColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Runtime");
      fRuntimeColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Ambient");
      fAmbientColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
      fSpecularColor.prcWrite(prc);
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


/* plLayerDepth */
IMPLEMENT_CREATABLE(plLayerDepth, kLayerDepth, plLayer)
