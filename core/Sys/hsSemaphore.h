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

#ifndef _HSSEMAPHORE_H
#define _HSSEMAPHORE_H

#include "PlasmaDefs.h"
#include "Debug/hsExceptions.h"

#ifdef WIN32
  #include <windows.h>
#else
  #include <sys/ipc.h>
  #include <sys/sem.h>
#endif

DllClass hsSemaphore {
private:
    #ifdef WIN32
    HANDLE fSemaH;
    #else
    int fSemaID;
    #endif

public:
    hsSemaphore(int initialValue, const char* name = "");
    ~hsSemaphore();

    bool wait();
    bool signal();
};

DllClass hsSemaphoreException : public hsException {
public:
    hsSemaphoreException(const char* file, unsigned long line) throw();
};

#endif
