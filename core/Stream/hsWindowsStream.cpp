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

#include "hsWindowsStream.h"
#include "Debug/plDebug.h"

#ifdef _WIN32

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

bool hsWindowsStream::open(const ST::string& file, FileMode mode)
{
    DWORD access, disposition;
    switch (mode) {
    case FileMode::fmRead:
        access = GENERIC_READ;
        disposition = OPEN_EXISTING;
        break;
    case FileMode::fmWrite:
        access = GENERIC_WRITE;
        disposition = OPEN_ALWAYS;
        break;
    case FileMode::fmCreate:
        access = GENERIC_READ | GENERIC_WRITE;
        disposition = CREATE_ALWAYS;
        break;
    case FileMode::fmReadWrite:
        access = GENERIC_READ | GENERIC_WRITE;
        disposition = OPEN_EXISTING;
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Invalid mode");
    }

    F = CreateFileW(
        file.to_wchar().data(), access, FILE_SHARE_READ, nullptr,
        disposition, FILE_ATTRIBUTE_NORMAL, nullptr
    );
    if (F == INVALID_HANDLE_VALUE) {
        F = nullptr;
        if (mode == fmRead || mode == fmReadWrite)
            throw hsFileReadException(__FILE__, __LINE__, "File does not exist");
        return false;
    }
    fm = mode;
    return true;
}

void hsWindowsStream::close()
{
    CloseHandle(F);
    F = nullptr;
}

uint32_t hsWindowsStream::size() const
{
    if (F == nullptr)
        return 0;
    return GetFileSize(F, nullptr);
}

uint32_t hsWindowsStream::pos() const
{
    if (F == nullptr)
        return 0;
    return SetFilePointer(F, 0, nullptr, FILE_CURRENT);
}

bool hsWindowsStream::eof() const
{
    if (F == nullptr)
        return true;
    if (GetFileType(F) != FILE_TYPE_DISK)
        throw hsNotImplementedException(__FILE__, __LINE__);
    return GetFileSize(F, nullptr) == SetFilePointer(F, 0, nullptr, FILE_CURRENT);
}

void hsWindowsStream::seek(uint32_t pos)
{
    if (F == nullptr)
        return;
    SetFilePointer(F, (LONG)pos, nullptr, FILE_BEGIN);
}

void hsWindowsStream::skip(int32_t count)
{
    if (F == nullptr)
        return;
    SetFilePointer(F, count, nullptr, FILE_CURRENT);
}

void hsWindowsStream::fastForward()
{
    if (F == nullptr)
        return;
    SetFilePointer(F, 0, nullptr, FILE_END);
}

void hsWindowsStream::rewind()
{
    if (F == nullptr)
        return;
    SetFilePointer(F, 0, nullptr, FILE_BEGIN);
}

void hsWindowsStream::flush()
{
    if (F == nullptr)
        return;
    FlushFileBuffers(F);
}

size_t hsWindowsStream::read(size_t size, void* buf)
{
    if (F == nullptr || fm == fmWrite || fm == fmCreate)
        throw hsFileReadException(__FILE__, __LINE__);
    DWORD nread = 0;
    ReadFile(F, buf, size, &nread, nullptr);
    if (nread != size) {
        throw hsFileReadException(
            __FILE__, __LINE__,
            ST::format(
                "Read past end of file: {} bytes requested, {} available",
                size, nread
            ).c_str()
        );
    }
    return nread;
}

size_t hsWindowsStream::write(size_t size, const void* buf)
{
    if (F == nullptr || fm == fmRead)
        throw hsFileWriteException(__FILE__, __LINE__);
    DWORD nwrite = 0;
    WriteFile(F, buf, size, &nwrite, nullptr);
    return nwrite;
}

#endif
