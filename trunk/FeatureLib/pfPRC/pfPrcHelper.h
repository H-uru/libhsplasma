#ifndef _PFPRCHELPER_H
#define _PFPRCHELPER_H

#include "../../CoreLib/hsStream.h"
#include <list>

DllClass pfPrcHelper {
private:
    int iLvl;
    bool inTag;
    std::list<const char*> openTags;

    void writeTabbed(hsStream* S, const char* str);

public:
    pfPrcHelper();
    ~pfPrcHelper();

    void startTag(hsStream* S, const char* name);
    void writeParam(hsStream* S, const char* name, const char* value);
    void writeParam(hsStream* S, const char* name, const int value);
    void writeParam(hsStream* S, const char* name, const unsigned int value);
    void writeParam(hsStream* S, const char* name, const float value);
    void writeParam(hsStream* S, const char* name, const double value);
    void writeParam(hsStream* S, const char* name, const bool value);
    void finishTag(hsStream* S, bool isShort = false);
    void writeSimpleTag(hsStream* S, const char* name, bool isShort = false);
    void endTag(hsStream* S);

    void writeComment(hsStream* S, const char* comment);

    void startPrc(hsStream* S);
    void finalize(hsStream* S);
};

#endif

