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

#ifndef _HSCOLORRGBA_H
#define _HSCOLORRGBA_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

struct PLASMA_DLL hsColorRGBA
{
public:
    static const hsColorRGBA kBlack;
    static const hsColorRGBA kWhite;
    static const hsColorRGBA kRed;
    static const hsColorRGBA kGreen;
    static const hsColorRGBA kBlue;
    static const hsColorRGBA kYellow;
    static const hsColorRGBA kMagenta;
    static const hsColorRGBA kCyan;
    static const hsColorRGBA kGray;
    static const hsColorRGBA kNone;

public:
    float r, g, b, a;

    hsColorRGBA(float red = 0.0f, float green = 0.0f, float blue = 0.0f,
                float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) { }

    void set(float red, float green, float blue, float alpha = 1.0f);
    void set(const hsColorRGBA& init);

    bool operator==(const hsColorRGBA& other) const;
    bool operator!=(const hsColorRGBA& other) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void readRGB(hsStream* S);
    void writeRGB(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


struct PLASMA_DLL hsColor32
{
public:
    union
    {
        struct
        {
            unsigned char b, g, r, a;
        };
        unsigned int color;
    };

    hsColor32(unsigned int color32 = 0xFF000000) : color(color32) { }
    hsColor32(unsigned char red, unsigned char green, unsigned char blue,
              unsigned char alpha = 255)
        : b(blue), g(green), r(red), a(alpha) { }

    bool operator==(const hsColor32& other) const;
    bool operator!=(const hsColor32& other) const;

    void read32(hsStream* S);
    void write32(hsStream* S);
    void readRGB8(hsStream* S);
    void writeRGB8(hsStream* S);
    void readRGBA8(hsStream* S);
    void writeRGBA8(hsStream*S );
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
