#include "plLayerMovie.h"

/* plLayerMovie */
plLayerMovie::plLayerMovie() { }
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

    prc->startTag("Movie");
    prc->writeParam("Name", fMovieName);
    prc->endTag(true);
}

void plLayerMovie::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Movie") {
        fMovieName = tag->getParam("Name", "");
    } else {
        plLayerAnimation::IPrcParse(tag, mgr);
    }
}

plString plLayerMovie::getMovieName() const { return fMovieName; }
void plLayerMovie::setMovieName(const plString& name) { fMovieName = name; }


/* plLayerAVI */
IMPLEMENT_CREATABLE(plLayerAVI, kLayerAVI, plLayerMovie)


/* plLayerBink */
IMPLEMENT_CREATABLE(plLayerBink, kLayerBink, plLayerMovie)
