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

#include "GameMessages.h"

/* Client -> Server */
static pnNetMsgField Cli2Game_PingRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Ping time
};
MAKE_NETMSG(Cli2Game_PingRequest)

static pnNetMsgField Cli2Game_JoinAgeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32) },  // Age MCP ID
    { kFieldData,      16, sizeof(hsUbyte)  },  // Account Uuid
    { kFieldInteger,    0, sizeof(hsUint32) },  // Player ID
};
MAKE_NETMSG(Cli2Game_JoinAgeRequest)

static pnNetMsgField Cli2Game_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Message Type
    { kFieldVarCount,   0, sizeof(hsUbyte)  },  // Buffer Data
    { kFieldVarPtr,     0, 0                },
};
MAKE_NETMSG(Cli2Game_PropagateBuffer)

static pnNetMsgField Cli2Game_GameMgrMsg_Fields[] = {
    { kFieldVarCount,   0, sizeof(hsUbyte)  },  // Message Data
    { kFieldVarPtr,     0, 0                },
};
MAKE_NETMSG(Cli2Game_GameMgrMsg)


/* Server -> Client */
static pnNetMsgField Game2Cli_PingReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Ping time
};
MAKE_NETMSG(Game2Cli_PingReply)

static pnNetMsgField Game2Cli_JoinAgeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32) },  // Result
};
MAKE_NETMSG(Game2Cli_JoinAgeReply)

static pnNetMsgField Game2Cli_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32) },  // Message Type
    { kFieldVarCount,   0, sizeof(hsUbyte)  },  // Buffer Data
    { kFieldVarPtr,     0, 0                },
};
MAKE_NETMSG(Game2Cli_PropagateBuffer)

static pnNetMsgField Game2Cli_GameMgrMsg_Fields[] = {
    { kFieldVarCount,   0, sizeof(hsUbyte)  },  // Message Data
    { kFieldVarPtr,     0, 0                },
};
MAKE_NETMSG(Game2Cli_GameMgrMsg)


const pnNetMsg* GET_Cli2Game(hsUint32 msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Cli2Game_PingRequest,
        &Cli2Game_JoinAgeRequest,
        &Cli2Game_PropagateBuffer,
        &Cli2Game_GameMgrMsg,
    };
    return (msgId < kCli2Game_LastMessage ? s_messages[msgId] : NULL);
}

const pnNetMsg* GET_Game2Cli(hsUint32 msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Game2Cli_PingReply,
        &Game2Cli_JoinAgeReply,
        &Game2Cli_PropagateBuffer,
        &Game2Cli_GameMgrMsg,
    };
    return (msgId < kGame2Cli_LastMessage ? s_messages[msgId] : NULL);
}
