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

#include "../pnNetMsg.h"

enum /* Client -> Server */
{
    kCli2GateKeeper_PingRequest, kCli2GateKeeper_FileSrvIpAddressRequest,
    kCli2GateKeeper_AuthSrvIpAddressRequest, kCli2GateKeeper_LastMessage,
};

enum /* Server -> Client */
{
    kGateKeeper2Cli_PingReply, kGateKeeper2Cli_FileSrvIpAddressReply,
    kGateKeeper2Cli_AuthSrvIpAddressReply, kGateKeeper2Cli_LastMessage,
};

PLASMANET_DLL const pnNetMsg* GET_Cli2GateKeeper(uint32_t msgId);
PLASMANET_DLL const pnNetMsg* GET_GateKeeper2Cli(uint32_t msgId);
