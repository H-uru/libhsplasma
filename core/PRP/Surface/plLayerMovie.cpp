#include "plLayerMovie.h"

/* plLayerMovie */
plLayerMovie::plLayerMovie()
            : fCurrentFrame(0), fLength(0.0f), fWidth(32), fHeight(32) {
    fOwnedChannels |= kTexture;
}

plLayerMovie::~plLayerMovie() { }

IMPLEMENT_CREATABLE(plLayerMovie, kLayerMovie, plLayerAnimation)

void plLayerMovie::read(hsStream* S, plResManager* mgr) {
    plLayerAnimation::read(S, mgr);

    int len = S->readInt();
    fMovieName = S->readStr(len);
}

void plLayerMovie::write(hsStream* S, plResManager* mgr) {
    plLayerAnimation::write(S, mgr);

    S->writeInt(fMovieName.len());
    S->writeStr(fMovieName);
}

void plLayerMovie::IPrcWrite(pfPrcHelper* prc) {
    plLayerAnimation::IPrcWrite(prc);

    prc->startTag("MovieName");
    prc->writeParam("value", fMovieName);
    prc->endTag(true);
}

void plLayerMovie::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MovieName") {
        fMovieName = tag->getParam("value", "");
    } else {
        plLayerAnimation::IPrcParse(tag, mgr);
    }
}


/* plLayerAVI */
IMPLEMENT_CREATABLE(plLayerAVI, kLayerAVI, plLayerMovie)


/* plLayerBink */
IMPLEMENT_CREATABLE(plLayerBink, kLayerBink, plLayerMovie)
