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

#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "PRP/Surface/plMipmap.h"

extern "C" {
#include <jpeglib.h>
}

class hsJPEGException : public hsException
{
public:
    inline hsJPEGException(const char* file, unsigned long line,
                           const char* message = nullptr) HS_NOEXCEPT
        : hsException(ST_LITERAL("libJPEG error"), file, line)
    {
        if (message != nullptr)
            fWhat += ST_LITERAL(": ") + message;
    }
};


class PLASMA_DLL plJPEG
{
private:
    jpeg_compress_struct cinfo;
    jpeg_decompress_struct dinfo;
    jpeg_error_mgr jerr;

public:
    static void DecompressJPEG(hsStream* S, void* buf, size_t size);
    static void CompressJPEG(hsStream* S, void* buf, size_t size);

private:
    plJPEG();
    ~plJPEG();

    static plJPEG& Instance();
};

#endif
