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

#include "hsThread.h"
#include "Debug/hsExceptions.hpp"

hsThread::~hsThread()
{
    wait();
    destroy();
}

void hsThread::threadEntry(hsThread* self)
{
    self->run();
    std::lock_guard<std::mutex> lock(self->fMutex);
    self->fState = kStateFinished;
}

void hsThread::start()
{
    std::lock_guard<std::mutex> lock(fMutex);
    if (fState == kStateRunning)
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");

    fState = kStateRunning;
    try {
        fThreadHandle = std::thread(&hsThread::threadEntry, this);
    } catch (std::system_error&) {
        fState = kStateFinished;
        throw;
    }
}

void hsThread::wait()
{
    if (fThreadHandle.joinable())
        fThreadHandle.join();
}

bool hsThread::isFinished()
{
    std::lock_guard<std::mutex> lock(fMutex);
    return fState == kStateFinished;
}
