#ifndef _PFPRCHELPER_H
#define _PFPRCHELPER_H

#include "CoreLib/hsStream.h"
#include "CoreLib/hsTList.hpp"

DllClass pfPrcHelper {
public:
    enum PrcExclude {
        kExcludeTextureData = 0x1,
        kExcludeVertexData = 0x2
    };

private:
    int iLvl;
    bool inTag;
    hsTList<const char*> openTags;
    hsStream* file;
    hsUint32 excludes;

    void startPrc();
    void finalize();
    void writeTabbed(const char* str);

public:
    pfPrcHelper(hsStream* S);
    ~pfPrcHelper();

    hsStream* getStream();
    void exclude(PrcExclude excl);
    bool isExcluded(PrcExclude excl);

    void startTag(const char* name);
    void writeParam(const char* name, const char* value);
    void writeParam(const char* name, int value);
    void writeParam(const char* name, long value);
    void writeParam(const char* name, unsigned int value);
    void writeParam(const char* name, unsigned long value);
    void writeParam(const char* name, float value);
    void writeParam(const char* name, double value);
    void writeParam(const char* name, bool value);
    void writeParamHex(const char* name, unsigned char value);
    void writeParamHex(const char* name, unsigned short value);
    void writeParamHex(const char* name, unsigned int value);
    void writeParamHex(const char* name, unsigned long value);
    void endTag(bool isShort = false);
    void endTagNoBreak();
    void writeSimpleTag(const char* name, bool isShort = false);
    void writeTagNoBreak(const char* name);
    void closeTag();
    void closeTagNoBreak();

    void writeComment(const char* comment);
};

#endif

