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

#ifndef _PNAUTHCLIENT_H
#define _PNAUTHCLIENT_H

#include "pnClient.h"
#include "Sys/plUuid.h"
#include "PRP/plCreatable.h"
#include "pnNetMsg.h"
#include "pnVaultNode.h"
#include "crypt/pnRC4.h"
#include "pnSocketInterface.h"

DllStruct pnAuthFileItem {
    plString fFilename;
    hsUint32 fFileSize;
};

DllStruct pnNetGameScore {
    hsUint32 fScoreId, fOwnerId;
    hsUint32 fCreatedTime, fGameType;
    hsInt32 fValue;
    plString fGameName;
};

DllStruct pnNetGameRank {
    hsUint32 fRank;
    hsInt32 fScore;
    plString fName;
};

DllClass pnAuthClient : public pnClient {
public:
    pnAuthClient(plResManager* mgr, bool deleteMsgs = true, bool threaded=true);
    virtual ~pnAuthClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN,
                 bool littleEndian = true);
    void setClientInfo(hsUint32 buildId, hsUint32 buildType, hsUint32 branchId,
                       const plUuid& productId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual void disconnect();

    virtual bool isConnected() const
    { return (fSock != NULL) && fSock->isConnected(); }

//     virtual void signalStatus() { fSock->signalStatus(); }
//     virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    hsUint32 sendPingRequest(hsUint32 pingTimeMs);
    void sendClientRegisterRequest();
    void sendClientSetCCRLevel(hsUint32 level);
    hsUint32 sendAcctExistsRequest(const plString& acctName);
    hsUint32 sendAcctLoginRequest(hsUint32 serverChallenge, hsUint32 clientChallenge,
                const plString& acctName, const plString& password,
                const plString& authToken = "", const plString& os = "win");
    hsUint32 sendAcctSetPlayerRequest(hsUint32 playerId);
    hsUint32 sendAcctCreateRequest(const plString& acctName,
                const plString& password, hsUint32 acctFlags,
                hsUint32 billingType);
    hsUint32 sendAcctChangePasswordRequest(const plString& acctName,
                const plString& password);
    hsUint32 sendAcctSetRolesRequest(const plString& acctName, hsUint32 acctFlags);
    hsUint32 sendAcctSetBillingTypeRequest(const plString& acctName, hsUint32 billingType);
    hsUint32 sendAcctActivateRequest(const plUuid& activationKey);
    hsUint32 sendAcctCreateFromKeyRequest(const plString& acctName,
                const plString& password, const plUuid& key, hsUint32 billingType);
    hsUint32 sendPlayerDeleteRequest(hsUint32 playerId);
    hsUint32 sendPlayerCreateRequest(const plString& playerName,
                const plString& playerShape, const plString& friendInvite);
    hsUint32 sendUpgradeVisitorRequest(hsUint32 playerId);
    hsUint32 sendSetPlayerBanStatusRequest(hsUint32 playerId, hsUint32 banned);
    void sendKickPlayer(hsUint32 playerId);
    hsUint32 sendChangePlayerNameRequest(hsUint32 playerId, const plString& name);
    hsUint32 sendFriendInviteRequest(const plUuid& invite, const plString& email,
                const plString& sendTo);
    hsUint32 sendVaultNodeCreate(const pnVaultNode& node);
    hsUint32 sendVaultNodeFetch(hsUint32 nodeId);
    hsUint32 sendVaultNodeSave(hsUint32 nodeId, const plUuid& revisionId,
                const pnVaultNode& node);
    hsUint32 sendVaultNodeAdd(hsUint32 parent, hsUint32 child, hsUint32 owner = 0);
    hsUint32 sendVaultNodeRemove(hsUint32 parent, hsUint32 child);
    hsUint32 sendVaultFetchNodeRefs(hsUint32 nodeId);
    hsUint32 sendVaultInitAgeRequest(const plUuid& ageUuid, const plString& filename,
                const plString& instanceName, const plString& userDefinedName,
                const plString& description, hsUint32 sequence, hsUint32 language,
                const plUuid& parentUuid = plUuid());
    hsUint32 sendVaultNodeFind(const pnVaultNode& templateNode);
    void sendVaultSetSeen(hsUint32 parent, hsUint32 child, hsUbyte seen);
    void sendVaultSendNode(hsUint32 nodeId, hsUint32 playerId);
    hsUint32 sendAgeRequest(const plString& ageName, const plUuid& ageUuid);
    hsUint32 sendAgeRequestEx(const plString& ageName, const plUuid& ageUuid);
    hsUint32 sendFileListRequest(const plString& directory, const plString& ext);
    hsUint32 sendFileDownloadRequest(const plString& filename);
    hsUint32 sendGetPublicAgeList(const plString& filename);
    void sendSetAgePublic(hsUint32 ageInfoId, hsUbyte isPublic);
    void sendLogPythonTraceback(const plString& traceback);
    void sendLogStackDump(const plString& stackdump);
    void sendLogClientDebuggerConnect();
    hsUint32 sendScoreCreate(hsUint32 owner, const plString& gameName,
                hsUint32 gameType, hsUint32 scoreValue);
    hsUint32 sendScoreDelete(hsUint32 scoreId);
    hsUint32 sendScoreGetScores(hsUint32 owner, const plString& gameName);
    hsUint32 sendScoreAddPoints(hsUint32 scoreId, hsUint32 points);
    hsUint32 sendScoreTransferPoints(hsUint32 source, hsUint32 dest, hsUint32 points);
    hsUint32 sendScoreSetPoints(hsUint32 scoreId, hsUint32 points);
    hsUint32 sendScoreGetRanks(hsUint32 ownerId, hsUint32 group, hsUint32 parent,
                const plString& gameName, hsUint32 timePeriod, hsUint32 numResults,
                hsUint32 pageNumber, hsUint32 sortDesc);
    void propagateMessage(plCreatable* msg);

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(hsUint32 transId, hsUint32 pingTimeMs);
    virtual void onServerAddr(hsUint32 address, const plUuid& token);
    virtual void onNotifyNewBuild(hsUint32 buildId);
    virtual void onClientRegisterReply(hsUint32 serverChallenge);
    virtual void onAcctExistsReply(hsUint32 transId, ENetError result, bool exists);
    virtual void onAcctLoginReply(hsUint32 transId, ENetError result,
                    const plUuid& acctUuid, hsUint32 acctFlags,
                    hsUint32 billingType, const hsUint32* encryptionKey);
    virtual void onAcctPlayerInfo(hsUint32 transId, hsUint32 playerId,
                    const plString& playerName, const plString& avatarModel,
                    hsUint32 explorer);
    virtual void onAcctSetPlayerReply(hsUint32 transId, ENetError result);
    virtual void onAcctCreateReply(hsUint32 transId, ENetError result,
                    const plUuid& accountUuid);
    virtual void onAcctChangePasswordReply(hsUint32 transId, ENetError result);
    virtual void onAcctSetRolesReply(hsUint32 transId, ENetError result);
    virtual void onAcctSetBillingTypeReply(hsUint32 transId, ENetError result);
    virtual void onAcctActivateReply(hsUint32 transId, ENetError result);
    virtual void onAcctCreateFromKeyReply(hsUint32 transId, ENetError result,
                    const plUuid& acctUuid, const plUuid& activationKey);
    virtual void onPlayerCreateReply(hsUint32 transId, ENetError result,
                    hsUint32 playerId, hsUint32 explorer,
                    const plString& playerName, const plString& avatarShape);
    virtual void onPlayerDeleteReply(hsUint32 transId, ENetError result);
    virtual void onUpgradeVisitorReply(hsUint32 transId, ENetError result);
    virtual void onSetPlayerBanStatusReply(hsUint32 transId, ENetError result);
    virtual void onChangePlayerNameReply(hsUint32 transId, ENetError result);
    virtual void onSendFriendInviteReply(hsUint32 transId, ENetError result);
    virtual void onVaultNodeCreated(hsUint32 transId, ENetError result,
                    hsUint32 nodeId);
    virtual void onVaultNodeFetched(hsUint32 transId, ENetError result,
                    const pnVaultNode& node);
    virtual void onVaultNodeChanged(hsUint32 nodeId, const plUuid& revisionId);
    virtual void onVaultNodeDeleted(hsUint32 nodeId);
    virtual void onVaultNodeAdded(hsUint32 parent, hsUint32 child, hsUint32 owner);
    virtual void onVaultNodeRemoved(hsUint32 parent, hsUint32 child);
    virtual void onVaultNodeRefsFetched(hsUint32 transId, ENetError result,
                    size_t count, const pnVaultNodeRef* refs);
    virtual void onVaultInitAgeReply(hsUint32 transId, ENetError result,
                    hsUint32 ageId, hsUint32 ageInfoId);
    virtual void onVaultNodeFindReply(hsUint32 transId, ENetError result,
                    size_t count, const hsUint32* nodes);
    virtual void onVaultSaveNodeReply(hsUint32 transId, ENetError result);
    virtual void onVaultAddNodeReply(hsUint32 transId, ENetError result);
    virtual void onVaultRemoveNodeReply(hsUint32 transId, ENetError result);
    virtual void onAgeReply(hsUint32 transId, ENetError result, hsUint32 mcpId,
                    const plUuid& ageInstanceId, hsUint32 ageVaultId,
                    hsUint32 gameServerAddress);
    virtual void onAgeReplyEx(hsUint32 transId, ENetError result, hsUint32 mcpId,
                    const plUuid& ageInstanceId, hsUint32 ageVaultId,
                    const plString& gameServerAddress);
    virtual void onFileListReply(hsUint32 transId, ENetError result,
                    size_t count, const pnAuthFileItem* files);
    virtual void onFileDownloadChunk(hsUint32 transId, ENetError result,
                    hsUint32 totalSize, hsUint32 chunkOffset, size_t chunkSize,
                    const unsigned char* chunkData);
    virtual void onKickedOff(hsUint32 reason);
    virtual void onPublicAgeList(hsUint32 transId, ENetError result,
                    size_t count, const pnNetAgeInfo* ages);
    virtual void onScoreCreateReply(hsUint32 transId, ENetError result,
                    hsUint32 scoreId, hsUint32 createdTime);
    virtual void onScoreDeleteReply(hsUint32 transId, ENetError result);
    virtual void onScoreGetScoresReply(hsUint32 transId, ENetError result,
                    size_t count, const pnNetGameScore* scores);
    virtual void onScoreAddPointsReply(hsUint32 transId, ENetError result);
    virtual void onScoreTransferPointsReply(hsUint32 transId, ENetError result);
    virtual void onScoreSetPointsReply(hsUint32 transId, ENetError result);
    virtual void onScoreGetRanksReply(hsUint32 transId, ENetError result,
                    size_t count, const pnNetGameRank* ranks);
    virtual void onPropagateMessage(plCreatable* msg);

protected:
    pnRC4Socket* fSock;
    plResManager* fResMgr;
    bool fDeleteMsgs;
    bool fThreaded;

    hsUint32 fBuildId, fBuildType, fBranchId;
    plUuid fProductId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];
    bool fLittleEndianKeys;

    class Dispatch : public pnDispatcher {
    public:
        Dispatch(pnAuthClient* self, bool deleteMsgs);
        virtual ~Dispatch();
        virtual bool dispatch(pnSocket* sock);

    private:
        pnAuthClient* fReceiver;
        bool fDeleteMsgs;
    } *fDispatch;

    ENetError performConnect();
    void sendFileDownloadChunkAck(hsUint32 transId);
};

#endif
