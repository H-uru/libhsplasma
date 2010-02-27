#include "../pnNetMsg.h"

enum {
    /* Client -> Server */
    kCli2Game_PingRequest, kCli2Game_JoinAgeRequest, kCli2Game_PropagateBuffer,
    kCli2Game_GameMgrMsg, kCli2Game_LastMessage,
};

enum {
    /* Server -> Client */
    kGame2Cli_PingReply, kGame2Cli_JoinAgeReply, kGame2Cli_PropagateBuffer,
    kGame2Cli_GameMgrMsg, kGame2Cli_LastMessage,
};

DllExport const pnNetMsg* GET_Cli2Game(hsUint32 msgId);
DllExport const pnNetMsg* GET_Game2Cli(hsUint32 msgId);
