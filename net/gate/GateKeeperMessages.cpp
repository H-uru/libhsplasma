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

#include "GateKeeperMessages.h"

/* Client -> Server */
static pnNetMsgField Cli2GateKeeper_PingRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Ping time
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2GateKeeper_PingRequest)

static pnNetMsgField Cli2GateKeeper_FileSrvIpAddressRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID?
    { kFieldInteger,    0, sizeof(uint8_t)    },  // ???
};
MAKE_NETMSG(Cli2GateKeeper_FileSrvIpAddressRequest)

static pnNetMsgField Cli2GateKeeper_AuthSrvIpAddressRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID?
};
MAKE_NETMSG(Cli2GateKeeper_AuthSrvIpAddressRequest)


/* Server -> Client */
static pnNetMsgField GateKeeper2Cli_PingReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Ping time
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(GateKeeper2Cli_PingReply)

static pnNetMsgField GateKeeper2Cli_FileSrvIpAddressReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID?
    { kFieldString,    24, sizeof(char16_t)   },  // Address
};
MAKE_NETMSG(GateKeeper2Cli_FileSrvIpAddressReply)

static pnNetMsgField GateKeeper2Cli_AuthSrvIpAddressReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID?
    { kFieldString,    24, sizeof(char16_t)   },  // Address
};
MAKE_NETMSG(GateKeeper2Cli_AuthSrvIpAddressReply)


const pnNetMsg* GET_Cli2GateKeeper(uint32_t msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Cli2GateKeeper_PingRequest,
        &Cli2GateKeeper_FileSrvIpAddressRequest,
        &Cli2GateKeeper_AuthSrvIpAddressRequest,
    };
    return (msgId < kCli2GateKeeper_LastMessage ? s_messages[msgId] : nullptr);
}

const pnNetMsg* GET_GateKeeper2Cli(uint32_t msgId)
{
    static const pnNetMsg* s_messages[] = {
        &GateKeeper2Cli_PingReply,
        &GateKeeper2Cli_FileSrvIpAddressReply,
        &GateKeeper2Cli_AuthSrvIpAddressReply,
    };
    return (msgId < kGateKeeper2Cli_LastMessage ? s_messages[msgId] : nullptr);
}
