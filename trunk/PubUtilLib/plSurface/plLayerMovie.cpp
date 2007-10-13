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
    char* buf = new char[len+1];
    S->read(len, buf);
    buf[len] = 0;
    fMovieName = buf;
    delete[] buf;
}

void plLayerMovie::write(hsStream* S, plResManager* mgr) {
    plLayerAnimation::write(S, mgr);

    S->writeInt(fMovieName.len());
    S->write(fMovieName.len(), fMovieName.cstr());
}

void plLayerMovie::prcWrite(pfPrcHelper* prc) {
    plLayerAnimation::prcWrite(prc);

    prc->startTag("MovieName");
    prc->writeParam("value", fMovieName);
    prc->endTag(true);
}


/* plLayerAVI */
IMPLEMENT_CREATABLE(plLayerAVI, kLayerAVI, plLayerMovie)


/* plLayerBink */
IMPLEMENT_CREATABLE(plLayerBink, kLayerBink, plLayerMovie)
