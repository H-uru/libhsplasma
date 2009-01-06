#include "pfPrcHelper.h"

pfPrcHelper::pfPrcHelper(hsStream* S)
           : iLvl(0), inTag(false), file(S), excludes(0) {
    startPrc();
}

pfPrcHelper::~pfPrcHelper() {
    finalize();
}

hsStream* pfPrcHelper::getStream() { return file; }

void pfPrcHelper::exclude(PrcExclude excl) {
    excludes |= excl;
}

bool pfPrcHelper::isExcluded(PrcExclude excl) {
    return (excludes & excl) != 0;
}

void pfPrcHelper::writeTabbed(const char* str) {
    for (int i=0; i<iLvl; i++) file->writeStr("\t");
    file->writeStr(str);
}

void pfPrcHelper::startTag(const char* name) {
    if (inTag) endTag();
    char buf[256];
    snprintf(buf, 256, "<%s", name);
    writeTabbed(buf);
    openTags.push(name);
    inTag = true;
}

void pfPrcHelper::writeParam(const char* name, const char* value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%s\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, int value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%d\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, long value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%ld\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, unsigned int value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%u\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, unsigned long value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%lu\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, float value) {
    writeParam(name, (double)value);
}

void pfPrcHelper::writeParam(const char* name, double value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%.10g\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, bool value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%s\"", name, value ? "True" : "False");
    file->writeStr(buf);
}

void pfPrcHelper::writeParamHex(const char* name, unsigned char value) {
    char buf[256];
    // %hhX is non-standard:
    unsigned short pval = (unsigned short)value;
    snprintf(buf, 256, " %s=\"0x%02hX\"", name, pval);
    file->writeStr(buf);
}

void pfPrcHelper::writeParamHex(const char* name, unsigned short value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"0x%04hX\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParamHex(const char* name, unsigned int value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"0x%08X\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParamHex(const char* name, unsigned long value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"0x%08lX\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::endTag(bool isShort) {
    char buf[6];
    snprintf(buf, 6, "%s>\n", isShort ? " /" : "");
    file->writeStr(buf);
    if (!isShort)
        iLvl++;
    else
        openTags.pop();
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
    snprintf(buf, 256, "</%s>\n", openTags.pop());
    writeTabbed(buf);
}

void pfPrcHelper::closeTagNoBreak() {
    char buf[256];
    iLvl--;
    snprintf(buf, 256, "</%s>\n", openTags.pop());
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

static bool goodChar(unsigned char ch) {
    return (ch >= 0x20) && (ch < 0x7F)
        && (ch != (unsigned char)'<') && (ch != (unsigned char)'>');
}

void pfPrcHelper::writeHexStream(size_t length, const unsigned char* data) {
    // Remember that the comments need to remain valid UTF-8, so only characters
    // between 0x20 and 0x7F can be displayed...

    size_t i;
    for (i=0; i<(length / 16); i++) {
        const unsigned char* ln = &data[i * 16];
        file->writeStr(
            plString::Format("%02X %02X %02X %02X %02X %02X %02X %02X "
                             "%02X %02X %02X %02X %02X %02X %02X %02X ",
                             ln[0x0], ln[0x1], ln[0x2], ln[0x3], ln[0x4], ln[0x5], ln[0x6], ln[0x7],
                             ln[0x8], ln[0x9], ln[0xA], ln[0xB], ln[0xC], ln[0xD], ln[0xE], ln[0xF]
                             ));
        file->writeStr(
            plString::Format("    <!-- %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c -->\n",
                             goodChar(ln[0x0]) ? ln[0x0] : '.',
                             goodChar(ln[0x1]) ? ln[0x1] : '.',
                             goodChar(ln[0x2]) ? ln[0x2] : '.',
                             goodChar(ln[0x3]) ? ln[0x3] : '.',
                             goodChar(ln[0x4]) ? ln[0x4] : '.',
                             goodChar(ln[0x5]) ? ln[0x5] : '.',
                             goodChar(ln[0x6]) ? ln[0x6] : '.',
                             goodChar(ln[0x7]) ? ln[0x7] : '.',
                             goodChar(ln[0x8]) ? ln[0x8] : '.',
                             goodChar(ln[0x9]) ? ln[0x9] : '.',
                             goodChar(ln[0xA]) ? ln[0xA] : '.',
                             goodChar(ln[0xB]) ? ln[0xB] : '.',
                             goodChar(ln[0xC]) ? ln[0xC] : '.',
                             goodChar(ln[0xD]) ? ln[0xD] : '.',
                             goodChar(ln[0xE]) ? ln[0xE] : '.',
                             goodChar(ln[0xF]) ? ln[0xF] : '.'
                             ));
    }
    if ((length % 16) != 0) {
        const unsigned char* ln = &data[(length / 16) * 16];
        for (i=0; i<(length % 16); i++)
            file->writeStr(plString::Format("%02X ", ln[i]));
        for (; i<16; i++)
            file->writeStr("   ");

        file->writeStr("    <!-- ");
        for (i=0; i<(length % 16); i++)
            file->writeStr(
                plString::Format("%c", goodChar(ln[i]) ? ln[i] : '.'));
        for (; i<16; i++)
            file->writeStr(" ");
        file->writeStr(" -->\n");
    }
}
