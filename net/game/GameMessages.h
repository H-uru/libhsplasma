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
    kCli2Game_PingRequest, kCli2Game_JoinAgeRequest, kCli2Game_PropagateBuffer,
    kCli2Game_GameMgrMsg, kCli2Game_LastMessage,
};

enum /* Server -> Client */
{
    kGame2Cli_PingReply, kGame2Cli_JoinAgeReply, kGame2Cli_PropagateBuffer,
    kGame2Cli_GameMgrMsg, kGame2Cli_LastMessage,
};

PLASMANET_DLL const pnNetMsg* GET_Cli2Game(uint32_t msgId);
PLASMANET_DLL const pnNetMsg* GET_Game2Cli(uint32_t msgId);
