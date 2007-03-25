#include "pfPrcHelper.h"

pfPrcHelper::pfPrcHelper(hsStream* S) : iLvl(0), inTag(false), file(S) {
    startPrc();
}

pfPrcHelper::~pfPrcHelper() {
    finalize();
}

void pfPrcHelper::writeTabbed(const char* str) {
    for (int i=0; i<iLvl; i++) file->writeStr("    ", 4);
    file->writeStr(str);
}

void pfPrcHelper::startTag(const char* name) {
    if (inTag) endTag();
    char buf[256];
    sprintf(buf, "<%s", name);
    writeTabbed(buf);
    openTags.push_back(name);
    inTag = true;
}

void pfPrcHelper::writeParam(const char* name, const char* value) {
    char buf[256];
    sprintf(buf, " %s=\"%s\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const int value) {
    char buf[256];
    sprintf(buf, " %s=\"%d\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const unsigned int value) {
    char buf[256];
    sprintf(buf, " %s=\"%u\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const float value) {
    writeParam(name, value);
}

void pfPrcHelper::writeParam(const char* name, const double value) {
    char buf[256];
    sprintf(buf, " %s=\"%g\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const bool value) {
    char buf[256];
    sprintf(buf, " %s=\"%s\"", name, value ? "True" : "False");
    file->writeStr(buf);
}

void pfPrcHelper::endTag(bool isShort) {
    char buf[6];
    sprintf(buf, "%s>\n", isShort ? " /" : "");
    file->writeStr(buf);
    if (!isShort)
        iLvl++;
    else
        openTags.pop_back();
    inTag = false;
}

void pfPrcHelper::endTagNoBreak() {
    file->writeStr(">");
    iLvl++;
    inTag = false;
}

void pfPrcHelper::writeSimpleTag(const char* name, bool isShort) {
    startTag(name);
    endTag(isShort);
}

void pfPrcHelper::writeTagNoBreak(const char* name) {
    startTag(name);
    endTagNoBreak();
}

void pfPrcHelper::closeTag() {
    char buf[256];
    iLvl--;
    sprintf(buf, "</%s>\n", openTags.back());
    openTags.pop_back();
    writeTabbed(buf);
}

void pfPrcHelper::closeTagNoBreak() {
    char buf[256];
    iLvl--;
    sprintf(buf, "</%s>\n", openTags.back());
    openTags.pop_back();
    file->writeStr(buf);
}

void pfPrcHelper::writeComment(const char* comment) {
    writeTabbed("<!-- ");
    file->writeStr(comment);
    file->writeStr(" -->\n");
}

void pfPrcHelper::startPrc() {
    file->writeStr("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n");
}

void pfPrcHelper::finalize() {
    if (inTag) endTag();
    while (!openTags.empty()) closeTag();
}

