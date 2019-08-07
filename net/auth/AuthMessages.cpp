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

#include "AuthMessages.h"
#include "pnVaultNode.h"

/* Client -> Server */
static pnNetMsgField Cli2Auth_PingRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Ping time
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_PingRequest)

static pnNetMsgField Cli2Auth_ClientRegisterRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Build ID
};
MAKE_NETMSG(Cli2Auth_ClientRegisterRequest)

static pnNetMsgField Cli2Auth_ClientSetCCRLevel_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // CCR Level
};
MAKE_NETMSG(Cli2Auth_ClientSetCCRLevel)

static pnNetMsgField Cli2Auth_AcctLoginRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Client Challenge
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldRawData,   20, sizeof(uint8_t)    },  // Password Hash
    { kFieldString,    64, sizeof(char16_t)   },  // Auth Token
    { kFieldString,     8, sizeof(char16_t)   },  // OS
};
MAKE_NETMSG(Cli2Auth_AcctLoginRequest)

static pnNetMsgField Cli2Auth_AcctSetPlayerRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_AcctSetPlayerRequest)

static pnNetMsgField Cli2Auth_AcctCreateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldRawData,   20, sizeof(uint8_t)    },  // Password Hash
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Account Flags
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctCreateRequest)

static pnNetMsgField Cli2Auth_AcctChangePasswordRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldRawData,   20, sizeof(uint8_t)    },  // Password Hash
};
MAKE_NETMSG(Cli2Auth_AcctChangePasswordRequest)

static pnNetMsgField Cli2Auth_AcctSetRolesRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Account Flags
};
MAKE_NETMSG(Cli2Auth_AcctSetRolesRequest)

static pnNetMsgField Cli2Auth_AcctSetBillingTypeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctSetBillingTypeRequest)

static pnNetMsgField Cli2Auth_AcctActivateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Activation Key (UUID)
};
MAKE_NETMSG(Cli2Auth_AcctActivateRequest)

static pnNetMsgField Cli2Auth_AcctCreateFromKeyRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
    { kFieldRawData,   20, sizeof(uint8_t)    },  // Password Hash
    { kFieldData,      16, sizeof(uint8_t)    },  // Key (UUID)
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctCreateFromKeyRequest)

static pnNetMsgField Cli2Auth_PlayerDeleteRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_PlayerDeleteRequest)

static pnNetMsgField Cli2Auth_PlayerCreateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    40, sizeof(char16_t)   },  // Player Name
    { kFieldString,   260, sizeof(char16_t)   },  // Avatar Shape
    { kFieldString,   260, sizeof(char16_t)   },  // Friend Invite
};
MAKE_NETMSG(Cli2Auth_PlayerCreateRequest)

static pnNetMsgField Cli2Auth_UpgradeVisitorRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_UpgradeVisitorRequest)

static pnNetMsgField Cli2Auth_SetPlayerBanStatusRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Banned
};
MAKE_NETMSG(Cli2Auth_SetPlayerBanStatusRequest)

static pnNetMsgField Cli2Auth_KickPlayer_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_KickPlayer)

static pnNetMsgField Cli2Auth_ChangePlayerNameRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
    { kFieldString,    40, sizeof(char16_t)   },  // Player Name
};
MAKE_NETMSG(Cli2Auth_ChangePlayerNameRequest)

static pnNetMsgField Cli2Auth_SendFriendInviteRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Invite UUID
    { kFieldString,    64, sizeof(char16_t)   },  // Email address
    { kFieldString,    40, sizeof(char16_t)   },  // To Name
};
MAKE_NETMSG(Cli2Auth_SendFriendInviteRequest)

static pnNetMsgField Cli2Auth_VaultNodeCreate_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeCreate)

static pnNetMsgField Cli2Auth_VaultNodeFetch_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeFetch)

static pnNetMsgField Cli2Auth_VaultNodeSave_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Revision ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeSave)

static pnNetMsgField Cli2Auth_VaultNodeAdd_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Child ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Owner ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeAdd)

static pnNetMsgField Cli2Auth_VaultNodeRemove_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Child ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeRemove)

static pnNetMsgField Cli2Auth_VaultFetchNodeRefs_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
};
MAKE_NETMSG(Cli2Auth_VaultFetchNodeRefs)

static pnNetMsgField Cli2Auth_VaultInitAgeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Age Instance UUID
    { kFieldData,      16, sizeof(uint8_t)    },  // Parent Age UUID
    { kFieldString,   260, sizeof(char16_t)   },  // Age Filename
    { kFieldString,   260, sizeof(char16_t)   },  // Age Instance Name
    { kFieldString,   260, sizeof(char16_t)   },  // Age User Name
    { kFieldString,  1024, sizeof(char16_t)   },  // Age Description
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Sequence Number
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Language
};
MAKE_NETMSG(Cli2Auth_VaultInitAgeRequest)

static pnNetMsgField Cli2Auth_VaultNodeFind_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeFind)

static pnNetMsgField Cli2Auth_VaultSetSeen_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Child ID
    { kFieldInteger,    0, sizeof(uint8_t)    },  // Seen
};
MAKE_NETMSG(Cli2Auth_VaultSetSeen)

static pnNetMsgField Cli2Auth_VaultSendNode_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_VaultSendNode)

static pnNetMsgField Cli2Auth_AgeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Age Name
    { kFieldData,      16, sizeof(uint8_t)    },  // Age UUID
};
MAKE_NETMSG(Cli2Auth_AgeRequest)

static pnNetMsgField Cli2Auth_FileListRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,   260, sizeof(char16_t)   },  // Directory
    { kFieldString,   256, sizeof(char16_t)   },  // Extension
};
MAKE_NETMSG(Cli2Auth_FileListRequest)

static pnNetMsgField Cli2Auth_FileDownloadRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,   260, sizeof(char16_t)   },  // File Name
};
MAKE_NETMSG(Cli2Auth_FileDownloadRequest)

static pnNetMsgField Cli2Auth_FileDownloadChunkAck_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
};
MAKE_NETMSG(Cli2Auth_FileDownloadChunkAck)

static pnNetMsgField Cli2Auth_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Type
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Buffer Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_PropagateBuffer)

static pnNetMsgField Cli2Auth_GetPublicAgeList_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Age Filename
};
MAKE_NETMSG(Cli2Auth_GetPublicAgeList)

static pnNetMsgField Cli2Auth_SetAgePublic_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Info ID
    { kFieldInteger,    0, sizeof(uint8_t)    },  // Public
};
MAKE_NETMSG(Cli2Auth_SetAgePublic)

static pnNetMsgField Cli2Auth_LogPythonTraceback_Fields[] = {
    { kFieldString,  1024, sizeof(char16_t)   },  // Traceback
};
MAKE_NETMSG(Cli2Auth_LogPythonTraceback)

static pnNetMsgField Cli2Auth_LogStackDump_Fields[] = {
    { kFieldString,  1024, sizeof(char16_t)   },  // Stackdump
};
MAKE_NETMSG(Cli2Auth_LogStackDump)

static pnNetMsgField Cli2Auth_LogClientDebuggerConnect_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Unused
};
MAKE_NETMSG(Cli2Auth_LogClientDebuggerConnect)

static pnNetMsgField Cli2Auth_ScoreCreate_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Owner ID
    { kFieldString,    64, sizeof(char16_t)   },  // Game Name
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Game Type
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score Value
};
MAKE_NETMSG(Cli2Auth_ScoreCreate)

static pnNetMsgField Cli2Auth_ScoreDelete_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)    }, // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)    }, // Score ID
};
MAKE_NETMSG(Cli2Auth_ScoreDelete)

static pnNetMsgField Cli2Auth_ScoreGetScores_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Owner ID
    { kFieldString,    64, sizeof(char16_t)   },  // Game Name
};
MAKE_NETMSG(Cli2Auth_ScoreGetScores)

static pnNetMsgField Cli2Auth_ScoreAddPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreAddPoints)

static pnNetMsgField Cli2Auth_ScoreTransferPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Source Score ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Dest Score ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreTransferPoints)

static pnNetMsgField Cli2Auth_ScoreSetPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreSetPoints)

static pnNetMsgField Cli2Auth_ScoreGetRanks_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Owner ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score Group
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent Folder ID
    { kFieldString,    64, sizeof(char16_t)   },  // Game Name
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Time Period
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Num Results
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Page Number
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Sort Desc
};
MAKE_NETMSG(Cli2Auth_ScoreGetRanks)

static pnNetMsgField Cli2Auth_AcctExistsRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Account Name
};
MAKE_NETMSG(Cli2Auth_AcctExistsRequest)

static pnNetMsgField Cli2Auth_AgeRequestEx_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldString,    64, sizeof(char16_t)   },  // Age Name
    { kFieldData,      16, sizeof(uint8_t)    },  // Age UUID
};
MAKE_NETMSG(Cli2Auth_AgeRequestEx)


/* Server -> Client */
static pnNetMsgField Auth2Cli_PingReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Ping time
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_PingReply)

static pnNetMsgField Auth2Cli_ServerAddr_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Server Address
    { kFieldData,      16, sizeof(uint8_t)    },  // Token (UUID)
};
MAKE_NETMSG(Auth2Cli_ServerAddr)

static pnNetMsgField Auth2Cli_NotifyNewBuild_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // "foo"
};
MAKE_NETMSG(Auth2Cli_NotifyNewBuild)

static pnNetMsgField Auth2Cli_ClientRegisterReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Server Challenge
};
MAKE_NETMSG(Auth2Cli_ClientRegisterReply)

static pnNetMsgField Auth2Cli_AcctLoginReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldData,      16, sizeof(uint8_t)    },  // Account UUID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Account Flags
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Billing Type
    { kFieldInteger,    4, sizeof(uint32_t)   },  // NTD Encryption Key
};
MAKE_NETMSG(Auth2Cli_AcctLoginReply)

static pnNetMsgField Auth2Cli_AcctPlayerInfo_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
    { kFieldString,    40, sizeof(char16_t)   },  // Player Name
    { kFieldString,    64, sizeof(char16_t)   },  // Avatar Model
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Explorer
};
MAKE_NETMSG(Auth2Cli_AcctPlayerInfo)

static pnNetMsgField Auth2Cli_AcctSetPlayerReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetPlayerReply)

static pnNetMsgField Auth2Cli_AcctCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldData,      16, sizeof(uint8_t)    },  // Account UUID
};
MAKE_NETMSG(Auth2Cli_AcctCreateReply)

static pnNetMsgField Auth2Cli_AcctChangePasswordReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctChangePasswordReply)

static pnNetMsgField Auth2Cli_AcctSetRolesReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetRolesReply)

static pnNetMsgField Auth2Cli_AcctSetBillingTypeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetBillingTypeReply)

static pnNetMsgField Auth2Cli_AcctActivateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctActivateReply)

static pnNetMsgField Auth2Cli_AcctCreateFromKeyReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldData,      16, sizeof(uint8_t)    },  // Account UUID
    { kFieldData,      16, sizeof(uint8_t)    },  // Activation Key
};
MAKE_NETMSG(Auth2Cli_AcctCreateFromKeyReply)

static pnNetMsgField Auth2Cli_PlayerCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Player ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Explorer
    { kFieldString,    40, sizeof(char16_t)   },  // Player Name
    { kFieldString,    64, sizeof(char16_t)   },  // Avatar Model
};
MAKE_NETMSG(Auth2Cli_PlayerCreateReply)

static pnNetMsgField Auth2Cli_PlayerDeleteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_PlayerDeleteReply)

static pnNetMsgField Auth2Cli_UpgradeVisitorReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_UpgradeVisitorReply)

static pnNetMsgField Auth2Cli_SetPlayerBanStatusReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_SetPlayerBanStatusReply)

static pnNetMsgField Auth2Cli_ChangePlayerNameReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ChangePlayerNameReply)

static pnNetMsgField Auth2Cli_SendFriendInviteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_SendFriendInviteReply)

static pnNetMsgField Auth2Cli_VaultNodeCreated_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeCreated)

static pnNetMsgField Auth2Cli_VaultNodeFetched_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_VaultNodeFetched)

static pnNetMsgField Auth2Cli_VaultNodeChanged_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Revision Uuid
};
MAKE_NETMSG(Auth2Cli_VaultNodeChanged)

static pnNetMsgField Auth2Cli_VaultNodeDeleted_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Node ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeDeleted)

static pnNetMsgField Auth2Cli_VaultNodeAdded_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Child ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Owner ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeAdded)

static pnNetMsgField Auth2Cli_VaultNodeRemoved_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Parent ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Child ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeRemoved)

static pnNetMsgField Auth2Cli_VaultNodeRefsFetched_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)         },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)         },  // Result
    { kFieldVarCount,   0, pnVaultNodeRef::Stride   },  // Node Refs
    { kFieldVarPtr,     0, 0                        },
};
MAKE_NETMSG(Auth2Cli_VaultNodeRefsFetched)

static pnNetMsgField Auth2Cli_VaultInitAgeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Vault ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Info Vault ID
};
MAKE_NETMSG(Auth2Cli_VaultInitAgeReply)

static pnNetMsgField Auth2Cli_VaultNodeFindReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldVarCount,   0, sizeof(uint32_t)   },  // Node ID List
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_VaultNodeFindReply)

static pnNetMsgField Auth2Cli_VaultSaveNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultSaveNodeReply)

static pnNetMsgField Auth2Cli_VaultAddNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultAddNodeReply)

static pnNetMsgField Auth2Cli_VaultRemoveNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultRemoveNodeReply)

static pnNetMsgField Auth2Cli_AgeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age MCP ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Age Instance Uuid
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Vault ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Game Server Address
};
MAKE_NETMSG(Auth2Cli_AgeReply)

static pnNetMsgField Auth2Cli_FileListReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldVarCount,   0, sizeof(char16_t)   },  // List Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_FileListReply)

static pnNetMsgField Auth2Cli_FileDownloadChunk_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Total Size
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Chunk Offset
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Chunk Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_FileDownloadChunk)

static pnNetMsgField Auth2Cli_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Message Type
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Buffer Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_PropagateBuffer)

static pnNetMsgField Auth2Cli_KickedOff_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Reason
};
MAKE_NETMSG(Auth2Cli_KickedOff)

static pnNetMsgField Auth2Cli_PublicAgeList_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)     },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)     },  // Result
    { kFieldVarCount,   0, pnNetAgeInfo::Stride },  // Ages (NetAgeInfo)
    { kFieldVarPtr,     0, 0                    },
};
MAKE_NETMSG(Auth2Cli_PublicAgeList)

static pnNetMsgField Auth2Cli_ScoreCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Created Time
};
MAKE_NETMSG(Auth2Cli_ScoreCreateReply)

static pnNetMsgField Auth2Cli_ScoreDeleteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreDeleteReply)

static pnNetMsgField Auth2Cli_ScoreGetScoresReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Score Count
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Score Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_ScoreGetScoresReply)

static pnNetMsgField Auth2Cli_ScoreAddPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreAddPointsReply)

static pnNetMsgField Auth2Cli_ScoreTransferPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreTransferPointsReply)

static pnNetMsgField Auth2Cli_ScoreSetPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreSetPointsReply)

static pnNetMsgField Auth2Cli_ScoreGetRanksReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Rank Count
    { kFieldVarCount,   0, sizeof(uint8_t)    },  // Rank Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_ScoreGetRanksReply)

static pnNetMsgField Auth2Cli_AcctExistsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result?
    { kFieldInteger,    0, sizeof(uint8_t)    },  // Exists?
};
MAKE_NETMSG(Auth2Cli_AcctExistsReply)

static pnNetMsgField Auth2Cli_AgeReplyEx_Fields[] = {
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Trans ID
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Result
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age MCP ID
    { kFieldData,      16, sizeof(uint8_t)    },  // Age Instance Uuid
    { kFieldInteger,    0, sizeof(uint32_t)   },  // Age Vault ID
    { kFieldString,   256, sizeof(char16_t)   },  // Game Server Address
};
MAKE_NETMSG(Auth2Cli_AgeReplyEx)


const pnNetMsg* GET_Cli2Auth(uint32_t msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Cli2Auth_PingRequest,
        &Cli2Auth_ClientRegisterRequest,
        &Cli2Auth_ClientSetCCRLevel,
        &Cli2Auth_AcctLoginRequest,
        nullptr /* kCli2Auth_AcctSetEulaVersion */,
        nullptr /* kCli2Auth_AcctSetDataRequest */,
        &Cli2Auth_AcctSetPlayerRequest,
        &Cli2Auth_AcctCreateRequest,
        &Cli2Auth_AcctChangePasswordRequest,
        &Cli2Auth_AcctSetRolesRequest,
        &Cli2Auth_AcctSetBillingTypeRequest,
        &Cli2Auth_AcctActivateRequest,
        &Cli2Auth_AcctCreateFromKeyRequest,
        &Cli2Auth_PlayerDeleteRequest,
        nullptr /* kCli2Auth_PlayerUndeleteRequest */,
        nullptr /* kCli2Auth_PlayerSelectRequest */,
        nullptr /* kCli2Auth_PlayerRenameRequest */,
        &Cli2Auth_PlayerCreateRequest,
        nullptr /* kCli2Auth_PlayerSetStatus */,
        nullptr /* kCli2Auth_PlayerChat */,
        &Cli2Auth_UpgradeVisitorRequest,
        &Cli2Auth_SetPlayerBanStatusRequest,
        &Cli2Auth_KickPlayer,
        &Cli2Auth_ChangePlayerNameRequest,
        &Cli2Auth_SendFriendInviteRequest,
        &Cli2Auth_VaultNodeCreate,
        &Cli2Auth_VaultNodeFetch,
        &Cli2Auth_VaultNodeSave,
        nullptr /* kCli2Auth_VaultNodeDelete */,
        &Cli2Auth_VaultNodeAdd,
        &Cli2Auth_VaultNodeRemove,
        &Cli2Auth_VaultFetchNodeRefs,
        &Cli2Auth_VaultInitAgeRequest,
        &Cli2Auth_VaultNodeFind,
        &Cli2Auth_VaultSetSeen,
        &Cli2Auth_VaultSendNode,
        &Cli2Auth_AgeRequest,
        &Cli2Auth_FileListRequest,
        &Cli2Auth_FileDownloadRequest,
        &Cli2Auth_FileDownloadChunkAck,
        &Cli2Auth_PropagateBuffer,
        &Cli2Auth_GetPublicAgeList,
        &Cli2Auth_SetAgePublic,
        &Cli2Auth_LogPythonTraceback,
        &Cli2Auth_LogStackDump,
        &Cli2Auth_LogClientDebuggerConnect,
        &Cli2Auth_ScoreCreate,
        &Cli2Auth_ScoreDelete,
        &Cli2Auth_ScoreGetScores,
        &Cli2Auth_ScoreAddPoints,
        &Cli2Auth_ScoreTransferPoints,
        &Cli2Auth_ScoreSetPoints,
        &Cli2Auth_ScoreGetRanks,
        &Cli2Auth_AcctExistsRequest,
    };
    static const pnNetMsg* s_messagesEx[] = {
        &Cli2Auth_AgeRequestEx,
    };
    if (msgId >= 0x1000)
        return (msgId < kCli2Auth_LastExMessage ? s_messagesEx[msgId & 0x0FFF] : nullptr);
    else
        return (msgId < kCli2Auth_LastMessage ? s_messages[msgId] : nullptr);
}

const pnNetMsg* GET_Auth2Cli(uint32_t msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Auth2Cli_PingReply,
        &Auth2Cli_ServerAddr,
        &Auth2Cli_NotifyNewBuild,
        &Auth2Cli_ClientRegisterReply,
        &Auth2Cli_AcctLoginReply,
        nullptr /* kAuth2Cli_AcctData */,
        &Auth2Cli_AcctPlayerInfo,
        &Auth2Cli_AcctSetPlayerReply,
        &Auth2Cli_AcctCreateReply,
        &Auth2Cli_AcctChangePasswordReply,
        &Auth2Cli_AcctSetRolesReply,
        &Auth2Cli_AcctSetBillingTypeReply,
        &Auth2Cli_AcctActivateReply,
        &Auth2Cli_AcctCreateFromKeyReply,
        nullptr /* kAuth2Cli_PlayerList */,
        nullptr /* kAuth2Cli_PlayerChat */,
        &Auth2Cli_PlayerCreateReply,
        &Auth2Cli_PlayerDeleteReply,
        &Auth2Cli_UpgradeVisitorReply,
        &Auth2Cli_SetPlayerBanStatusReply,
        &Auth2Cli_ChangePlayerNameReply,
        &Auth2Cli_SendFriendInviteReply,
        nullptr /* kAuth2Cli_FriendNotify */,
        &Auth2Cli_VaultNodeCreated,
        &Auth2Cli_VaultNodeFetched,
        &Auth2Cli_VaultNodeChanged,
        &Auth2Cli_VaultNodeDeleted,
        &Auth2Cli_VaultNodeAdded,
        &Auth2Cli_VaultNodeRemoved,
        &Auth2Cli_VaultNodeRefsFetched,
        &Auth2Cli_VaultInitAgeReply,
        &Auth2Cli_VaultNodeFindReply,
        &Auth2Cli_VaultSaveNodeReply,
        &Auth2Cli_VaultAddNodeReply,
        &Auth2Cli_VaultRemoveNodeReply,
        &Auth2Cli_AgeReply,
        &Auth2Cli_FileListReply,
        &Auth2Cli_FileDownloadChunk,
        &Auth2Cli_PropagateBuffer,
        &Auth2Cli_KickedOff,
        &Auth2Cli_PublicAgeList,
        &Auth2Cli_ScoreCreateReply,
        &Auth2Cli_ScoreDeleteReply,
        &Auth2Cli_ScoreGetScoresReply,
        &Auth2Cli_ScoreAddPointsReply,
        &Auth2Cli_ScoreTransferPointsReply,
        &Auth2Cli_ScoreSetPointsReply,
        &Auth2Cli_ScoreGetRanksReply,
        &Auth2Cli_AcctExistsReply,
    };
    static const pnNetMsg* s_messagesEx[] = {
        &Auth2Cli_AgeReplyEx,
    };
    if (msgId >= 0x1000)
        return (msgId < kAuth2Cli_LastExMessage ? s_messagesEx[msgId & 0x0FFF] : nullptr);
    else
        return (msgId < kAuth2Cli_LastMessage ? s_messages[msgId] : nullptr);
}
