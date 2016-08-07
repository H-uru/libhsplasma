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

#ifndef _HSTHREAD_H
#define _HSTHREAD_H

#include "../PlasmaDefs.h"

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  define S_THREADSTART DWORD WINAPI s_threadstart(LPVOID)
#else
#  define S_THREADSTART void* s_threadstart(void*)
#endif

class PLASMA_DLL hsThreadCondition {
protected:
    void* fConditionData;

public:
    hsThreadCondition();
    ~hsThreadCondition();

    void wait();
    void signal();
};

class PLASMA_DLL hsMutex {
protected:
    void* fMutexData;

public:
    hsMutex();
    ~hsMutex();

    void lock();
    void unlock();

private:
    friend class hsThread;
};

class PLASMA_DLL hsThread {
private:
    void* fThreadData;
    hsThreadCondition fFinishCondition;

public:
    hsThread();
    virtual ~hsThread();
    virtual void destroy();

    void start();
    void wait();
    bool isFinished() const;
    void terminate();

protected:
    virtual void run() = 0;

private:
    static S_THREADSTART;
};

#endif
