#ifndef _PFPRCHELPER_H
#define _PFPRCHELPER_H

#include "../../CoreLib/hsStream.h"
#include <list>

DllClass pfPrcHelper {
private:
    int iLvl;
    bool inTag;
    std::list<const char*> openTags;
    hsStream* file;

    void startPrc();
    void finalize();
    void writeTabbed(const char* str);

public:
    pfPrcHelper(hsStream* S);
    ~pfPrcHelper();

    void startTag(const char* name);
    void writeParam(const char* name, const char* value);
    void writeParam(const char* name, const int value);
    void writeParam(const char* name, const unsigned int value);
    void writeParam(const char* name, const float value);
    void writeParam(const char* name, const double value);
    void writeParam(const char* name, const bool value);
    void endTag(bool isShort = false);
    void endTagNoBreak();
    void writeSimpleTag(const char* name, bool isShort = false);
    void writeTagNoBreak(const char* name);
    void closeTag();
    void closeTagNoBreak();

    void writeComment(const char* comment);
};

#endif

