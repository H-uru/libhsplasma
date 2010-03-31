#include "../pnNetMsg.h"

enum {  /* Client -> Server */
    kCli2GateKeeper_PingRequest, kCli2GateKeeper_FileSrvIpAddressRequest,
    kCli2GateKeeper_AuthSrvIpAddressRequest, kCli2GateKeeper_LastMessage,
};

enum {  /* Server -> Client */
    kGateKeeper2Cli_PingReply, kGateKeeper2Cli_FileSrvIpAddressReply,
    kGateKeeper2Cli_AuthSrvIpAddressReply, kGateKeeper2Cli_LastMessage,
};

DllExport const pnNetMsg* GET_Cli2GateKeeper(hsUint32 msgId);
DllExport const pnNetMsg* GET_GateKeeper2Cli(hsUint32 msgId);
