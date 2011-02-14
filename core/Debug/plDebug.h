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

#ifndef _PLDEBUG_H
#define _PLDEBUG_H

#include "Stream/hsStdioStream.h"

class PLASMA_DLL plDebug {
public:
    enum DebugLevel { kDLNone, kDLError, kDLWarning, kDLDebug, kDLAll };

private:
    static hsStream* fDebugStream;
    static int fDebugLevel;
    static bool fIOwnStream;
    static bool fIsExitRegistered;
    static plString fDebugFile;

public:
    static void Init(int level, hsStream* stream = NULL);
    static void InitFile(int level, const char* filename = "Plasma.log");

    static void Error(const char* fmt, ...);
    static void Warning(const char* fmt, ...);
    static void Debug(const char* fmt, ...);

private:
    static void WriteLn(const char* fmt, va_list args);
    static void DelayInit();
    static void DeInit();
};

#endif
