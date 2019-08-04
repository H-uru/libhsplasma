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

#include "PlasmaDefs.h"
#include <mutex>
#include <thread>

class PLASMA_DLL hsThread
{
private:
    enum
    {
        kStatePending,
        kStateRunning,
        kStateFinished,
    };

    int fState;
    std::mutex fMutex;
    std::thread fThreadHandle;

public:
    hsThread() : fState(kStatePending) { }
    virtual ~hsThread();
    virtual void destroy() { }

    void start();
    void wait();
    bool isFinished();

protected:
    virtual void run() = 0;

private:
    static void threadEntry(hsThread* self);
};

#endif
