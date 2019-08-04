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

#ifndef _PLPNG_H
#define _PLPNG_H

#include "PRP/Surface/plMipmap.h"

#include <png.h>

class hsPNGException : public hsException
{
public:
    inline hsPNGException(const char* file, unsigned long line,
                          const char* message = nullptr) HS_NOEXCEPT
        : hsException(ST_LITERAL("libPNG error"), file, line)
    {
        if (message != nullptr)
            fWhat += ST_LITERAL(": ") + message;
    }
};


class PLASMA_DLL plPNG
{
public:
    static void DecompressPNG(hsStream* S, void* buf, size_t size);
    static void CompressPNG(hsStream* S, const void* buf, size_t size,
                            uint32_t width, uint32_t height, int pixelSize);

private:
    plPNG() = delete;
};

#endif
