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
    kCli2Auth_PingRequest, kCli2Auth_ClientRegisterRequest,
    kCli2Auth_ClientSetCCRLevel, kCli2Auth_AcctLoginRequest,
    kCli2Auth_AcctSetEulaVersion, kCli2Auth_AcctSetDataRequest,
    kCli2Auth_AcctSetPlayerRequest, kCli2Auth_AcctCreateRequest,
    kCli2Auth_AcctChangePasswordRequest, kCli2Auth_AcctSetRolesRequest,
    kCli2Auth_AcctSetBillingTypeRequest, kCli2Auth_AcctActivateRequest,
    kCli2Auth_AcctCreateFromKeyRequest, kCli2Auth_PlayerDeleteRequest,
    kCli2Auth_PlayerUndeleteRequest, kCli2Auth_PlayerSelectRequest,
    kCli2Auth_PlayerRenameRequest, kCli2Auth_PlayerCreateRequest,
    kCli2Auth_PlayerSetStatus, kCli2Auth_PlayerChat,
    kCli2Auth_UpgradeVisitorRequest, kCli2Auth_SetPlayerBanStatusRequest,
    kCli2Auth_KickPlayer, kCli2Auth_ChangePlayerNameRequest,
    kCli2Auth_SendFriendInviteRequest, kCli2Auth_VaultNodeCreate,
    kCli2Auth_VaultNodeFetch, kCli2Auth_VaultNodeSave,
    kCli2Auth_VaultNodeDelete, kCli2Auth_VaultNodeAdd,
    kCli2Auth_VaultNodeRemove, kCli2Auth_VaultFetchNodeRefs,
    kCli2Auth_VaultInitAgeRequest, kCli2Auth_VaultNodeFind,
    kCli2Auth_VaultSetSeen, kCli2Auth_VaultSendNode, kCli2Auth_AgeRequest,
    kCli2Auth_FileListRequest, kCli2Auth_FileDownloadRequest,
    kCli2Auth_FileDownloadChunkAck, kCli2Auth_PropagateBuffer,
    kCli2Auth_GetPublicAgeList, kCli2Auth_SetAgePublic,
    kCli2Auth_LogPythonTraceback, kCli2Auth_LogStackDump,
    kCli2Auth_LogClientDebuggerConnect, kCli2Auth_ScoreCreate,
    kCli2Auth_ScoreDelete, kCli2Auth_ScoreGetScores, kCli2Auth_ScoreAddPoints,
    kCli2Auth_ScoreTransferPoints, kCli2Auth_ScoreSetPoints,
    kCli2Auth_ScoreGetRanks, kCli2Auth_AcctExistsRequest,
    kCli2Auth_LastMessage,
    kCli2Auth_AgeRequestEx = 0x1000,
    kCli2Auth_LastExMessage,
};

enum /* Server -> Client */
{
    kAuth2Cli_PingReply, kAuth2Cli_ServerAddr, kAuth2Cli_NotifyNewBuild,
    kAuth2Cli_ClientRegisterReply, kAuth2Cli_AcctLoginReply, kAuth2Cli_AcctData,
    kAuth2Cli_AcctPlayerInfo, kAuth2Cli_AcctSetPlayerReply,
    kAuth2Cli_AcctCreateReply, kAuth2Cli_AcctChangePasswordReply,
    kAuth2Cli_AcctSetRolesReply, kAuth2Cli_AcctSetBillingTypeReply,
    kAuth2Cli_AcctActivateReply, kAuth2Cli_AcctCreateFromKeyReply,
    kAuth2Cli_PlayerList, kAuth2Cli_PlayerChat, kAuth2Cli_PlayerCreateReply,
    kAuth2Cli_PlayerDeleteReply, kAuth2Cli_UpgradeVisitorReply,
    kAuth2Cli_SetPlayerBanStatusReply, kAuth2Cli_ChangePlayerNameReply,
    kAuth2Cli_SendFriendInviteReply, kAuth2Cli_FriendNotify,
    kAuth2Cli_VaultNodeCreated, kAuth2Cli_VaultNodeFetched,
    kAuth2Cli_VaultNodeChanged, kAuth2Cli_VaultNodeDeleted,
    kAuth2Cli_VaultNodeAdded, kAuth2Cli_VaultNodeRemoved,
    kAuth2Cli_VaultNodeRefsFetched, kAuth2Cli_VaultInitAgeReply,
    kAuth2Cli_VaultNodeFindReply, kAuth2Cli_VaultSaveNodeReply,
    kAuth2Cli_VaultAddNodeReply, kAuth2Cli_VaultRemoveNodeReply,
    kAuth2Cli_AgeReply, kAuth2Cli_FileListReply, kAuth2Cli_FileDownloadChunk,
    kAuth2Cli_PropagateBuffer, kAuth2Cli_KickedOff, kAuth2Cli_PublicAgeList,
    kAuth2Cli_ScoreCreateReply, kAuth2Cli_ScoreDeleteReply,
    kAuth2Cli_ScoreGetScoresReply, kAuth2Cli_ScoreAddPointsReply,
    kAuth2Cli_ScoreTransferPointsReply, kAuth2Cli_ScoreSetPointsReply,
    kAuth2Cli_ScoreGetRanksReply, kAuth2Cli_AcctExistsReply,
    kAuth2Cli_LastMessage,
    kAuth2Cli_AgeReplyEx = 0x1000,
    kAuth2Cli_LastExMessage,
};

PLASMANET_DLL const pnNetMsg* GET_Cli2Auth(uint32_t msgId);
PLASMANET_DLL const pnNetMsg* GET_Auth2Cli(uint32_t msgId);
