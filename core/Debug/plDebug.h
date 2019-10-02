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

#include <string_theory/format>
#include "Stream/hsStdioStream.h"

class PLASMA_DLL plDebug
{
public:
    enum DebugLevel { kDLNone, kDLError, kDLWarning, kDLDebug, kDLAll };

private:
    static hsStream* fDebugStream;
    static int fDebugLevel;
    static bool fIOwnStream;
    static bool fIsExitRegistered;
    static ST::string fDebugFile;

public:
    static void Init(int level, hsStream* stream = nullptr);
    static void InitFile(int level, const ST::string& filename = ST_LITERAL("Plasma.log"));

    static void Error(const char* line)
    {
        if (fDebugLevel < kDLError)
            return;
        WriteLn(line);
    }

    static void Warning(const char* line)
    {
        if (fDebugLevel < kDLWarning)
            return;
        WriteLn(line);
    }

    static void Debug(const char* line)
    {
        if (fDebugLevel < kDLDebug)
            return;
        WriteLn(line);
    }

    template <typename... T_args>
    static void Error(const char* fmt, T_args&&... args)
    {
        if (fDebugLevel < kDLError)
            return;
        WriteLn(ST::format(fmt, std::forward<T_args>(args)...));
    }

    template <typename... T_args>
    static void Warning(const char* fmt, T_args&&... args)
    {
        if (fDebugLevel < kDLWarning)
            return;
        WriteLn(ST::format(fmt, std::forward<T_args>(args)...));
    }

    template <typename... T_args>
    static void Debug(const char* fmt, T_args&&... args)
    {
        if (fDebugLevel < kDLDebug)
            return;
        WriteLn(ST::format(fmt, std::forward<T_args>(args)...));
    }

private:
    static void WriteLn(const ST::string& line);
    static void DelayInit();
    static void DeInit();
};

#endif
