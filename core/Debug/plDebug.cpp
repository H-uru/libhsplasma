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

#include "plDebug.h"
#include <cstdarg>
#include <cstdlib>

hsStream* plDebug::fDebugStream = nullptr;
int plDebug::fDebugLevel = kDLWarning;
bool plDebug::fIOwnStream = false;
bool plDebug::fIsExitRegistered = false;
ST::string plDebug::fDebugFile;

void plDebug::Init(int level, hsStream* stream)
{
    DeInit();

    fDebugLevel = level;
    if (stream == nullptr) {
        fDebugStream = new hsStdioStream(true);
        fIOwnStream = true;
    } else {
        fDebugStream = stream;
        fIOwnStream = false;
    }

    // Register cleanup
    if (!fIsExitRegistered) {
        fIsExitRegistered = true;
        atexit(&plDebug::DeInit);
    }
}

void plDebug::InitFile(int level, const ST::string& filename)
{
    DeInit();

    fDebugLevel = level;
    fDebugFile = filename;

    // Register cleanup
    if (!fIsExitRegistered) {
        fIsExitRegistered = true;
        atexit(&plDebug::DeInit);
    }
}

void plDebug::DelayInit()
{
    if (fDebugFile.empty()) {
        // Nobody ever called Init(), so use stderr
        Init(kDLWarning, nullptr);
    } else {
        // Init to the provided filename
        fDebugStream = new hsFileStream();
        ((hsFileStream*)fDebugStream)->open(fDebugFile, fmCreate);
        fIOwnStream = true;
    }
}

void plDebug::DeInit()
{
    if (fIOwnStream)
        delete fDebugStream;
    fDebugStream = nullptr;
}

void plDebug::WriteLn(const ST::string& line)
{
    if (fDebugStream == nullptr)
        DelayInit();

    fDebugStream->writeLine(line);
    fDebugStream->flush();
}
