/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PFPRCHELPER_H
#define _PFPRCHELPER_H

#include "hsStream.h"
#include <stack>

class PLASMA_DLL pfPrcHelper
{
public:
    enum PrcExclude
    {
        kNone = 0,
        kExcludeTextureData = 0x1,
        kExcludeVertexData = 0x2
    };

private:
    int iLvl;
    bool inTag;
    std::stack<const char*> openTags;
    hsStream* file;
    uint32_t excludes;

    void startPrc();
    void finalize();
    void writeTabbed(const char* str);

public:
    pfPrcHelper(hsStream* S)
        : iLvl(), inTag(), file(S), excludes() { startPrc(); }
    ~pfPrcHelper() { finalize(); }

    void directWrite(const ST::string& text);
    void exclude(PrcExclude excl) { excludes |= excl; }
    bool isExcluded(PrcExclude excl) { return (excludes & excl) != 0; }

    void startTag(const char* name);
    void writeParam(const char* name, const ST::string& value);
    void writeParam(const char* name, const char* value);
    void writeParam(const char* name, int value);
    void writeParam(const char* name, long value);
    void writeParam(const char* name, long long value);
    void writeParam(const char* name, unsigned int value);
    void writeParam(const char* name, unsigned long value);
    void writeParam(const char* name, unsigned long long value);
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

    void writeHexStream(size_t length, const unsigned char* data);
};

#endif

