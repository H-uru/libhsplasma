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

#include "hsStdioStream.h"

hsStdioStream::hsStdioStream(bool useStdErr) : hsFileStream(PlasmaVer::pvUnknown)
{
    if (useStdErr)
        setFiles(stdin, stderr);
    else
        setFiles(stdin, stdout);
    fm = fmReadWrite;
}

void hsStdioStream::seek(uint32_t pos)
{
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::skip(int32_t count)
{
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::flush()
{
    fflush(Fin);
    fflush(Fout);
}

size_t hsStdioStream::read(size_t size, void* buf)
{
    return fread(buf, size, 1, Fin);
}

size_t hsStdioStream::write(size_t size, const void* buf)
{
    return fwrite(buf, size, 1, Fout);
}
