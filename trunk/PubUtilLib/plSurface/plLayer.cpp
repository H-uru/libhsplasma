#include "plLayer.h"
#include "../plResMgr/plResManager.h"

plLayer::plLayer() {
    transform = new hsMatrix44();
    preshadeColor = new hsColorRGBA();
    runtimeColor = new hsColorRGBA();
    ambientColor = new hsColorRGBA();
    specularColor = new hsColorRGBA();
    state = new hsGMatState();

    opacity = new float;
    UVWSrc = new unsigned int;
    LODBias = new float;
    specularPower = new float;

    //texture = new plBitmap*;
    //vertexShader = new plShader*;
    //pixelShader = new plShader*;
    bumpEnvXfm = new hsMatrix44();
}

plLayer::~plLayer() {
    delete transform;
    delete preshadeColor;
    delete runtimeColor;
    delete ambientColor;
    delete specularColor;
    delete state;
    delete opacity;
    delete UVWSrc;
    delete LODBias;
    delete specularPower;
    //delete texture;
    //delete vertexShader;
    //delete pixelShader;
    delete bumpEnvXfm;
}

IMPLEMENT_CREATABLE(plLayer, kLayer, plLayerInterface)

void plLayer::read(hsStream* S, plResManager* mgr) {
    plLayerInterface::read(S, mgr);
    state->read(S);
    transform->read(S);

    preshadeColor->read(S);
    runtimeColor->read(S);
    ambientColor->read(S);
    specularColor->read(S);

    *UVWSrc = S->readInt();
    *opacity = S->readFloat();
    *LODBias = S->readFloat();
    *specularPower = S->readFloat();

    texture = mgr->readKey(S);
    vertexShader = mgr->readKey(S);
    pixelShader = mgr->readKey(S);
    bumpEnvXfm->read(S);
}

void plLayer::write(hsStream* S, plResManager* mgr) {
    plLayerInterface::write(S, mgr);
    state->write(S);
    transform->write(S);

    preshadeColor->write(S);
    runtimeColor->write(S);
    ambientColor->write(S);
    specularColor->write(S);

    S->writeInt(*UVWSrc);
    S->writeFloat(*opacity);
    S->writeFloat(*LODBias);
    S->writeFloat(*specularPower);

    mgr->writeKey(S, texture);
    mgr->writeKey(S, vertexShader);
    mgr->writeKey(S, pixelShader);
    bumpEnvXfm->write(S);
}

void plLayer::prcWrite(pfPrcHelper* prc) {
    plLayerInterface::prcWrite(prc);

    state->prcWrite(prc);
    prc->writeSimpleTag("Transform");
      transform->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Preshade");
      preshadeColor->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Runtime");
      runtimeColor->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Ambient");
      ambientColor->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
      specularColor->prcWrite(prc);
    prc->closeTag();

    prc->startTag("LayerParams");
    prc->writeParam("UVWSrc", *UVWSrc);
    prc->writeParam("Opacity", *opacity);
    prc->writeParam("LODBias", *LODBias);
    prc->writeParam("SpecularPower", *specularPower);
    prc->endTag(true);

    prc->writeSimpleTag("Texture");
      texture->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("VertexShader");
      vertexShader->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PixelShader");
      pixelShader->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("BumpEnvXfm");
      bumpEnvXfm->prcWrite(prc);
    prc->closeTag();
}
