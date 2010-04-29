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
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Ping time
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_PingRequest)

static pnNetMsgField Cli2Auth_ClientRegisterRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Build ID
};
MAKE_NETMSG(Cli2Auth_ClientRegisterRequest)

static pnNetMsgField Cli2Auth_ClientSetCCRLevel_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // CCR Level
};
MAKE_NETMSG(Cli2Auth_ClientSetCCRLevel)

static pnNetMsgField Cli2Auth_AcctLoginRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Client Challenge
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldRawData,   20, sizeof(hsUbyte)    },  // Password Hash
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Auth Token
    { kFieldString,     8, sizeof(pl_wchar_t) },  // OS
};
MAKE_NETMSG(Cli2Auth_AcctLoginRequest)

static pnNetMsgField Cli2Auth_AcctSetPlayerRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_AcctSetPlayerRequest)

static pnNetMsgField Cli2Auth_AcctCreateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldRawData,   20, sizeof(hsUbyte)    },  // Password Hash
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Account Flags
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctCreateRequest)

static pnNetMsgField Cli2Auth_AcctChangePasswordRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldRawData,   20, sizeof(hsUbyte)    },  // Password Hash
};
MAKE_NETMSG(Cli2Auth_AcctChangePasswordRequest)

static pnNetMsgField Cli2Auth_AcctSetRolesRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Account Flags
};
MAKE_NETMSG(Cli2Auth_AcctSetRolesRequest)

static pnNetMsgField Cli2Auth_AcctSetBillingTypeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctSetBillingTypeRequest)

static pnNetMsgField Cli2Auth_AcctActivateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Activation Key (UUID)
};
MAKE_NETMSG(Cli2Auth_AcctActivateRequest)

static pnNetMsgField Cli2Auth_AcctCreateFromKeyRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Account Name
    { kFieldRawData,   20, sizeof(hsUbyte)    },  // Password Hash
    { kFieldData,      16, sizeof(hsUbyte)    },  // Key (UUID)
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Billing Type
};
MAKE_NETMSG(Cli2Auth_AcctCreateFromKeyRequest)

static pnNetMsgField Cli2Auth_PlayerDeleteRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_PlayerDeleteRequest)

static pnNetMsgField Cli2Auth_PlayerCreateRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    40, sizeof(pl_wchar_t) },  // Player Name
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Avatar Shape
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Friend Invite
};
MAKE_NETMSG(Cli2Auth_PlayerCreateRequest)

static pnNetMsgField Cli2Auth_UpgradeVisitorRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_UpgradeVisitorRequest)

static pnNetMsgField Cli2Auth_SetPlayerBanStatusRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Banned
};
MAKE_NETMSG(Cli2Auth_SetPlayerBanStatusRequest)

static pnNetMsgField Cli2Auth_KickPlayer_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_KickPlayer)

static pnNetMsgField Cli2Auth_ChangePlayerNameRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
    { kFieldString,    40, sizeof(pl_wchar_t) },  // Player Name
};
MAKE_NETMSG(Cli2Auth_ChangePlayerNameRequest)

static pnNetMsgField Cli2Auth_SendFriendInviteRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Invite UUID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Email address
    { kFieldString,    40, sizeof(pl_wchar_t) },  // To Name
};
MAKE_NETMSG(Cli2Auth_SendFriendInviteRequest)

static pnNetMsgField Cli2Auth_VaultNodeCreate_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeCreate)

static pnNetMsgField Cli2Auth_VaultNodeFetch_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeFetch)

static pnNetMsgField Cli2Auth_VaultNodeSave_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Revision ID
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeSave)

static pnNetMsgField Cli2Auth_VaultNodeAdd_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Child ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Owner ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeAdd)

static pnNetMsgField Cli2Auth_VaultNodeRemove_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Child ID
};
MAKE_NETMSG(Cli2Auth_VaultNodeRemove)

static pnNetMsgField Cli2Auth_VaultFetchNodeRefs_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
};
MAKE_NETMSG(Cli2Auth_VaultFetchNodeRefs)

static pnNetMsgField Cli2Auth_VaultInitAgeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Age Instance UUID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Parent Age UUID
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Age Filename
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Age Instance Name
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Age User Name
    { kFieldString,  1024, sizeof(pl_wchar_t) },  // Age Description
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Sequence Number
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Language
};
MAKE_NETMSG(Cli2Auth_VaultInitAgeRequest)

static pnNetMsgField Cli2Auth_VaultNodeFind_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_VaultNodeFind)

static pnNetMsgField Cli2Auth_VaultSetSeen_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Child ID
    { kFieldInteger,    0, sizeof(hsUbyte)    },  // Seen
};
MAKE_NETMSG(Cli2Auth_VaultSetSeen)

static pnNetMsgField Cli2Auth_VaultSendNode_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
};
MAKE_NETMSG(Cli2Auth_VaultSendNode)

static pnNetMsgField Cli2Auth_AgeRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    40, sizeof(pl_wchar_t) },  // Age Name
    { kFieldData,      16, sizeof(hsUbyte)    },  // Age UUID
};
MAKE_NETMSG(Cli2Auth_AgeRequest)

static pnNetMsgField Cli2Auth_FileListRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,   260, sizeof(pl_wchar_t) },  // Directory
    { kFieldString,   256, sizeof(pl_wchar_t) },  // Extension
};
MAKE_NETMSG(Cli2Auth_FileListRequest)

static pnNetMsgField Cli2Auth_FileDownloadRequest_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,   260, sizeof(pl_wchar_t) },  // File Name
};
MAKE_NETMSG(Cli2Auth_FileDownloadRequest)

static pnNetMsgField Cli2Auth_FileDownloadChunkAck_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
};
MAKE_NETMSG(Cli2Auth_FileDownloadChunkAck)

static pnNetMsgField Cli2Auth_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Type
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Buffer Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Cli2Auth_PropagateBuffer)

static pnNetMsgField Cli2Auth_GetPublicAgeList_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Age Filename
};
MAKE_NETMSG(Cli2Auth_GetPublicAgeList)

static pnNetMsgField Cli2Auth_SetAgePublic_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Info ID
    { kFieldInteger,    0, sizeof(hsUbyte)    },  // Public
};
MAKE_NETMSG(Cli2Auth_SetAgePublic)

static pnNetMsgField Cli2Auth_LogPythonTraceback_Fields[] = {
    { kFieldString,  1024, sizeof(pl_wchar_t) },  // Traceback
};
MAKE_NETMSG(Cli2Auth_LogPythonTraceback)

static pnNetMsgField Cli2Auth_LogStackDump_Fields[] = {
    { kFieldString,  1024, sizeof(pl_wchar_t) },  // Stackdump
};
MAKE_NETMSG(Cli2Auth_LogStackDump)

static pnNetMsgField Cli2Auth_LogClientDebuggerConnect_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Unused
};
MAKE_NETMSG(Cli2Auth_LogClientDebuggerConnect)

static pnNetMsgField Cli2Auth_ScoreCreate_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Owner ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Game Name
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Game Type
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score Value
};
MAKE_NETMSG(Cli2Auth_ScoreCreate)

static pnNetMsgField Cli2Auth_ScoreDelete_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)    }, // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)    }, // Score ID
};
MAKE_NETMSG(Cli2Auth_ScoreDelete)

static pnNetMsgField Cli2Auth_ScoreGetScores_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Owner ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Game Name
};
MAKE_NETMSG(Cli2Auth_ScoreGetScores)

static pnNetMsgField Cli2Auth_ScoreAddPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreAddPoints)

static pnNetMsgField Cli2Auth_ScoreTransferPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Source Score ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Dest Score ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreTransferPoints)

static pnNetMsgField Cli2Auth_ScoreSetPoints_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Num Points
};
MAKE_NETMSG(Cli2Auth_ScoreSetPoints)

static pnNetMsgField Cli2Auth_ScoreGetRanks_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Owner ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score Group
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent Folder ID
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Game Name
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Time Period
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Num Results
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Page Number
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Sort Desc
};
MAKE_NETMSG(Cli2Auth_ScoreGetRanks)


/* Server -> Client */
static pnNetMsgField Auth2Cli_PingReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Ping time
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Payload
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_PingReply)

static pnNetMsgField Auth2Cli_ServerAddr_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Server Address
    { kFieldData,      16, sizeof(hsUbyte)    },  // Token (UUID)
};
MAKE_NETMSG(Auth2Cli_ServerAddr)

static pnNetMsgField Auth2Cli_NotifyNewBuild_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // "foo"
};
MAKE_NETMSG(Auth2Cli_NotifyNewBuild)

static pnNetMsgField Auth2Cli_ClientRegisterReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Server Challenge
};
MAKE_NETMSG(Auth2Cli_ClientRegisterReply)

static pnNetMsgField Auth2Cli_AcctLoginReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldData,      16, sizeof(hsUbyte)    },  // Account UUID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Account Flags
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Billing Type
    { kFieldInteger,    4, sizeof(hsUint32)   },  // NTD Encryption Key
};
MAKE_NETMSG(Auth2Cli_AcctLoginReply)

static pnNetMsgField Auth2Cli_AcctPlayerInfo_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
    { kFieldString,    40, sizeof(pl_wchar_t) },  // Player Name
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Avatar Model
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Explorer
};
MAKE_NETMSG(Auth2Cli_AcctPlayerInfo)

static pnNetMsgField Auth2Cli_AcctSetPlayerReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetPlayerReply)

static pnNetMsgField Auth2Cli_AcctCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldData,      16, sizeof(hsUbyte)    },  // Account UUID
};
MAKE_NETMSG(Auth2Cli_AcctCreateReply)

static pnNetMsgField Auth2Cli_AcctChangePasswordReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctChangePasswordReply)

static pnNetMsgField Auth2Cli_AcctSetRolesReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetRolesReply)

static pnNetMsgField Auth2Cli_AcctSetBillingTypeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctSetBillingTypeReply)

static pnNetMsgField Auth2Cli_AcctActivateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_AcctActivateReply)

static pnNetMsgField Auth2Cli_AcctCreateFromKeyReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldData,      16, sizeof(hsUbyte)    },  // Account UUID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Activation Key
};
MAKE_NETMSG(Auth2Cli_AcctCreateFromKeyReply)

static pnNetMsgField Auth2Cli_PlayerCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Player ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Explorer
    { kFieldString,    40, sizeof(pl_wchar_t) },  // Player Name
    { kFieldString,    64, sizeof(pl_wchar_t) },  // Avatar Model
};
MAKE_NETMSG(Auth2Cli_PlayerCreateReply)

static pnNetMsgField Auth2Cli_PlayerDeleteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_PlayerDeleteReply)

static pnNetMsgField Auth2Cli_UpgradeVisitorReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_UpgradeVisitorReply)

static pnNetMsgField Auth2Cli_SetPlayerBanStatusReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_SetPlayerBanStatusReply)

static pnNetMsgField Auth2Cli_ChangePlayerNameReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ChangePlayerNameReply)

static pnNetMsgField Auth2Cli_SendFriendInviteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_SendFriendInviteReply)

static pnNetMsgField Auth2Cli_VaultNodeCreated_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeCreated)

static pnNetMsgField Auth2Cli_VaultNodeFetched_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Node Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_VaultNodeFetched)

static pnNetMsgField Auth2Cli_VaultNodeChanged_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Revision Uuid
};
MAKE_NETMSG(Auth2Cli_VaultNodeChanged)

static pnNetMsgField Auth2Cli_VaultNodeDeleted_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Node ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeDeleted)

static pnNetMsgField Auth2Cli_VaultNodeAdded_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Child ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Owner ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeAdded)

static pnNetMsgField Auth2Cli_VaultNodeRemoved_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Parent ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Child ID
};
MAKE_NETMSG(Auth2Cli_VaultNodeRemoved)

static pnNetMsgField Auth2Cli_VaultNodeRefsFetched_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)         },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)         },  // Result
    { kFieldVarCount,   0, pnVaultNodeRef::Stride   },  // Node Refs
    { kFieldVarPtr,     0, 0                        },
};
MAKE_NETMSG(Auth2Cli_VaultNodeRefsFetched)

static pnNetMsgField Auth2Cli_VaultInitAgeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Vault ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Info Vault ID
};
MAKE_NETMSG(Auth2Cli_VaultInitAgeReply)

static pnNetMsgField Auth2Cli_VaultNodeFindReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldVarCount,   0, sizeof(hsUint32)   },  // Node ID List
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_VaultNodeFindReply)

static pnNetMsgField Auth2Cli_VaultSaveNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultSaveNodeReply)

static pnNetMsgField Auth2Cli_VaultAddNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultAddNodeReply)

static pnNetMsgField Auth2Cli_VaultRemoveNodeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_VaultRemoveNodeReply)

static pnNetMsgField Auth2Cli_AgeReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age MCP ID
    { kFieldData,      16, sizeof(hsUbyte)    },  // Age Instance Uuid
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Age Vault ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Game Server Address
};
MAKE_NETMSG(Auth2Cli_AgeReply)

static pnNetMsgField Auth2Cli_FileListReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldVarCount,   0, sizeof(pl_wchar_t) },  // List Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_FileListReply)

static pnNetMsgField Auth2Cli_FileDownloadChunk_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Total Size
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Chunk Offset
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Chunk Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_FileDownloadChunk)

static pnNetMsgField Auth2Cli_PropagateBuffer_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Message Type
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Buffer Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_PropagateBuffer)

static pnNetMsgField Auth2Cli_KickedOff_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Reason
};
MAKE_NETMSG(Auth2Cli_KickedOff)

static pnNetMsgField Auth2Cli_PublicAgeList_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)     },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)     },  // Result
    { kFieldVarCount,   0, pnNetAgeInfo::Stride },  // Ages (NetAgeInfo)
    { kFieldVarPtr,     0, 0                    },
};
MAKE_NETMSG(Auth2Cli_PublicAgeList)

static pnNetMsgField Auth2Cli_ScoreCreateReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Created Time
};
MAKE_NETMSG(Auth2Cli_ScoreCreateReply)

static pnNetMsgField Auth2Cli_ScoreDeleteReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreDeleteReply)

static pnNetMsgField Auth2Cli_ScoreGetScoresReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Score Count
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Score Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_ScoreGetScoresReply)

static pnNetMsgField Auth2Cli_ScoreAddPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreAddPointsReply)

static pnNetMsgField Auth2Cli_ScoreTransferPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreTransferPointsReply)

static pnNetMsgField Auth2Cli_ScoreSetPointsReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
};
MAKE_NETMSG(Auth2Cli_ScoreSetPointsReply)

static pnNetMsgField Auth2Cli_ScoreGetRanksReply_Fields[] = {
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Trans ID
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Result
    { kFieldInteger,    0, sizeof(hsUint32)   },  // Rank Count
    { kFieldVarCount,   0, sizeof(hsUbyte)    },  // Rank Data
    { kFieldVarPtr,     0, 0                  },
};
MAKE_NETMSG(Auth2Cli_ScoreGetRanksReply)


const pnNetMsg* GET_Cli2Auth(hsUint32 msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Cli2Auth_PingRequest,
        &Cli2Auth_ClientRegisterRequest,
        &Cli2Auth_ClientSetCCRLevel,
        &Cli2Auth_AcctLoginRequest,
        NULL /* kCli2Auth_AcctSetEulaVersion */,
        NULL /* kCli2Auth_AcctSetDataRequest */,
        &Cli2Auth_AcctSetPlayerRequest,
        &Cli2Auth_AcctCreateRequest,
        &Cli2Auth_AcctChangePasswordRequest,
        &Cli2Auth_AcctSetRolesRequest,
        &Cli2Auth_AcctSetBillingTypeRequest,
        &Cli2Auth_AcctActivateRequest,
        &Cli2Auth_AcctCreateFromKeyRequest,
        &Cli2Auth_PlayerDeleteRequest,
        NULL /* kCli2Auth_PlayerUndeleteRequest */,
        NULL /* kCli2Auth_PlayerSelectRequest */,
        NULL /* kCli2Auth_PlayerRenameRequest */,
        &Cli2Auth_PlayerCreateRequest,
        NULL /* kCli2Auth_PlayerSetStatus */,
        NULL /* kCli2Auth_PlayerChat */,
        &Cli2Auth_UpgradeVisitorRequest,
        &Cli2Auth_SetPlayerBanStatusRequest,
        &Cli2Auth_KickPlayer,
        &Cli2Auth_ChangePlayerNameRequest,
        &Cli2Auth_SendFriendInviteRequest,
        &Cli2Auth_VaultNodeCreate,
        &Cli2Auth_VaultNodeFetch,
        &Cli2Auth_VaultNodeSave,
        NULL /* kCli2Auth_VaultNodeDelete */,
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
    };
    return (msgId < kCli2Auth_LastMessage ? s_messages[msgId] : NULL);
}

const pnNetMsg* GET_Auth2Cli(hsUint32 msgId)
{
    static const pnNetMsg* s_messages[] = {
        &Auth2Cli_PingReply,
        &Auth2Cli_ServerAddr,
        &Auth2Cli_NotifyNewBuild,
        &Auth2Cli_ClientRegisterReply,
        &Auth2Cli_AcctLoginReply,
        NULL /* kAuth2Cli_AcctData */,
        &Auth2Cli_AcctPlayerInfo,
        &Auth2Cli_AcctSetPlayerReply,
        &Auth2Cli_AcctCreateReply,
        &Auth2Cli_AcctChangePasswordReply,
        &Auth2Cli_AcctSetRolesReply,
        &Auth2Cli_AcctSetBillingTypeReply,
        &Auth2Cli_AcctActivateReply,
        &Auth2Cli_AcctCreateFromKeyReply,
        NULL /* kAuth2Cli_PlayerList */,
        NULL /* kAuth2Cli_PlayerChat */,
        &Auth2Cli_PlayerCreateReply,
        &Auth2Cli_PlayerDeleteReply,
        &Auth2Cli_UpgradeVisitorReply,
        &Auth2Cli_SetPlayerBanStatusReply,
        &Auth2Cli_ChangePlayerNameReply,
        &Auth2Cli_SendFriendInviteReply,
        NULL /* kAuth2Cli_FriendNotify */,
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
    };
    return (msgId < kAuth2Cli_LastMessage ? s_messages[msgId] : NULL);
}
