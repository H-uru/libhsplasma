#include "pfPrcHelper.h"

pfPrcHelper::pfPrcHelper() : iLvl(0), inTag(false) { }
pfPrcHelper::~pfPrcHelper() { }

void pfPrcHelper::writeTabbed(hsStream* S, const char* str) {
    for (int i=0; i<iLvl; i++) S->writeStr("    ", 4);
    S->writeStr(str);
}

void pfPrcHelper::startTag(hsStream* S, const char* name) {
    if (inTag) finishTag(S);
    char buf[256];
    sprintf(buf, "<%s", name);
    writeTabbed(S, buf);
    openTags.push_back(name);
    inTag = true;
}

void pfPrcHelper::writeParam(hsStream* S, const char* name, const char* value) {
    char buf[256];
    sprintf(buf, " %s=\"%s\"", name, value);
    S->writeStr(buf);
}

void pfPrcHelper::writeParam(hsStream* S, const char* name, const int value) {
    char buf[256];
    sprintf(buf, " %s=\"%d\"", name, value);
    S->writeStr(buf);
}

void pfPrcHelper::writeParam(hsStream* S, const char* name, const float value) {
    char buf[256];
    sprintf(buf, " %s=\"%f\"", name, value);
    S->writeStr(buf);
}

void pfPrcHelper::finishTag(hsStream* S, bool isShort) {
    char buf[6];
    sprintf(buf, "%s>\n", isShort ? " /" : "");
    S->writeStr(buf);
    if (!isShort)
        iLvl++;
    else
        openTags.pop_back();
    inTag = false;
}

void pfPrcHelper::writeSimpleTag(hsStream* S, const char* name, bool isShort) {
    startTag(S, name);
    finishTag(S, isShort);
}

void pfPrcHelper::endTag(hsStream* S) {
    char buf[256];
    iLvl--;
    sprintf(buf, "</%s>\n", openTags.back());
    openTags.pop_back();
    writeTabbed(S, buf);
}

void pfPrcHelper::startPrc(hsStream* S) {
    S->writeStr("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n");
}

void pfPrcHelper::finalize(hsStream* S) {
    if (inTag) finishTag(S);
    while (!openTags.empty()) endTag(S);
}

