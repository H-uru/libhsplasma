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

#include "pnClient.h"
#include "pnSocketInterface.h"

pnClient::pnClient()
        : fIface(NULL)
{ }

pnClient::~pnClient()
{
    // we leave deleting fIface up to the subclass, since that's
    // where it was created in the first place.
}

void pnClient::run()
{
  fIface->run();
}

hsUint32 pnClient::nextTransId() {
    static hsUint32 s_transId = 0;
    static hsMutex s_tidMutex;

    s_tidMutex.lock();
    hsUint32 tid = ++s_transId;
    s_tidMutex.unlock();
    return tid;
}
