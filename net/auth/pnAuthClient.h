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

struct PLASMANET_DLL pnAuthFileItem
{
    ST::string fFilename;
    uint32_t fFileSize;
};

struct PLASMANET_DLL pnNetGameScore
{
    uint32_t fScoreId, fOwnerId;
    uint32_t fCreatedTime, fGameType;
    int32_t fValue;
    ST::string fGameName;
};

struct PLASMANET_DLL pnNetGameRank
{
    uint32_t fRank;
    int32_t fScore;
    ST::string fName;
};

class PLASMANET_DLL pnAuthClient : public pnClient
{
public:
    pnAuthClient(plResManager* mgr, bool deleteMsgs = true, bool threaded = true)
        : fSock(), fResMgr(mgr), fDeleteMsgs(deleteMsgs), fThreaded(threaded),
          fKeyG(41), fDispatch() { }
    ~pnAuthClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN,
                 bool littleEndian = true);
    void setKeyG(int g) { fKeyG = g; }
    void setClientInfo(uint32_t buildId, uint32_t buildType, uint32_t branchId,
                       const plUuid& productId);
    ENetError connect(const char* host, short port = 14617) HS_OVERRIDE;
    ENetError connect(int sockFd) HS_OVERRIDE;
    void disconnect() HS_OVERRIDE;

    bool isConnected() const HS_OVERRIDE
    {
        return fSock && fSock->isConnected();
    }

//     virtual void signalStatus() { fSock->signalStatus(); }
//     virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    uint32_t sendPingRequest(uint32_t pingTimeMs);
    void sendClientRegisterRequest();
    void sendClientSetCCRLevel(uint32_t level);
    uint32_t sendAcctExistsRequest(const ST::string& acctName);
    uint32_t sendAcctLoginRequest(uint32_t serverChallenge, uint32_t clientChallenge,
                const ST::string& acctName, const ST::string& password,
                const ST::string& authToken = "", const ST::string& os = "win");
    uint32_t sendAcctSetPlayerRequest(uint32_t playerId);
    uint32_t sendAcctCreateRequest(const ST::string& acctName,
                const ST::string& password, uint32_t acctFlags,
                uint32_t billingType);
    uint32_t sendAcctChangePasswordRequest(const ST::string& acctName,
                const ST::string& password);
    uint32_t sendAcctSetRolesRequest(const ST::string& acctName, uint32_t acctFlags);
    uint32_t sendAcctSetBillingTypeRequest(const ST::string& acctName, uint32_t billingType);
    uint32_t sendAcctActivateRequest(const plUuid& activationKey);
    uint32_t sendAcctCreateFromKeyRequest(const ST::string& acctName,
                const ST::string& password, const plUuid& key, uint32_t billingType);
    uint32_t sendPlayerDeleteRequest(uint32_t playerId);
    uint32_t sendPlayerCreateRequest(const ST::string& playerName,
                const ST::string& playerShape, const ST::string& friendInvite);
    uint32_t sendUpgradeVisitorRequest(uint32_t playerId);
    uint32_t sendSetPlayerBanStatusRequest(uint32_t playerId, uint32_t banned);
    void sendKickPlayer(uint32_t playerId);
    uint32_t sendChangePlayerNameRequest(uint32_t playerId, const ST::string& name);
    uint32_t sendFriendInviteRequest(const plUuid& invite, const ST::string& email,
                const ST::string& sendTo);
    uint32_t sendVaultNodeCreate(const pnVaultNode& node);
    uint32_t sendVaultNodeFetch(uint32_t nodeId);
    uint32_t sendVaultNodeSave(uint32_t nodeId, const plUuid& revisionId,
                const pnVaultNode& node);
    uint32_t sendVaultNodeAdd(uint32_t parent, uint32_t child, uint32_t owner = 0);
    uint32_t sendVaultNodeRemove(uint32_t parent, uint32_t child);
    uint32_t sendVaultFetchNodeRefs(uint32_t nodeId);
    uint32_t sendVaultInitAgeRequest(const plUuid& ageUuid, const ST::string& filename,
                const ST::string& instanceName, const ST::string& userDefinedName,
                const ST::string& description, uint32_t sequence, uint32_t language,
                const plUuid& parentUuid = plUuid());
    uint32_t sendVaultNodeFind(const pnVaultNode& templateNode);
    void sendVaultSetSeen(uint32_t parent, uint32_t child, uint8_t seen);
    void sendVaultSendNode(uint32_t nodeId, uint32_t playerId);
    uint32_t sendAgeRequest(const ST::string& ageName, const plUuid& ageUuid);
    uint32_t sendAgeRequestEx(const ST::string& ageName, const plUuid& ageUuid);
    uint32_t sendFileListRequest(const ST::string& directory, const ST::string& ext);
    uint32_t sendFileDownloadRequest(const ST::string& filename);
    uint32_t sendGetPublicAgeList(const ST::string& filename);
    void sendSetAgePublic(uint32_t ageInfoId, uint8_t isPublic);
    void sendLogPythonTraceback(const ST::string& traceback);
    void sendLogStackDump(const ST::string& stackdump);
    void sendLogClientDebuggerConnect();
    uint32_t sendScoreCreate(uint32_t owner, const ST::string& gameName,
                uint32_t gameType, uint32_t scoreValue);
    uint32_t sendScoreDelete(uint32_t scoreId);
    uint32_t sendScoreGetScores(uint32_t owner, const ST::string& gameName);
    uint32_t sendScoreAddPoints(uint32_t scoreId, uint32_t points);
    uint32_t sendScoreTransferPoints(uint32_t source, uint32_t dest, uint32_t points);
    uint32_t sendScoreSetPoints(uint32_t scoreId, uint32_t points);
    uint32_t sendScoreGetRanks(uint32_t ownerId, uint32_t group, uint32_t parent,
                const ST::string& gameName, uint32_t timePeriod, uint32_t numResults,
                uint32_t pageNumber, uint32_t sortDesc);
    void propagateMessage(plCreatable* msg);

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(uint32_t transId, uint32_t pingTimeMs);
    virtual void onServerAddr(uint32_t address, const plUuid& token);
    virtual void onNotifyNewBuild(uint32_t buildId);
    virtual void onClientRegisterReply(uint32_t serverChallenge);
    virtual void onAcctExistsReply(uint32_t transId, ENetError result, bool exists);
    virtual void onAcctLoginReply(uint32_t transId, ENetError result,
                    const plUuid& acctUuid, uint32_t acctFlags,
                    uint32_t billingType, const uint32_t* encryptionKey);
    virtual void onAcctPlayerInfo(uint32_t transId, uint32_t playerId,
                    const ST::string& playerName, const ST::string& avatarModel,
                    uint32_t explorer);
    virtual void onAcctSetPlayerReply(uint32_t transId, ENetError result);
    virtual void onAcctCreateReply(uint32_t transId, ENetError result,
                    const plUuid& accountUuid);
    virtual void onAcctChangePasswordReply(uint32_t transId, ENetError result);
    virtual void onAcctSetRolesReply(uint32_t transId, ENetError result);
    virtual void onAcctSetBillingTypeReply(uint32_t transId, ENetError result);
    virtual void onAcctActivateReply(uint32_t transId, ENetError result);
    virtual void onAcctCreateFromKeyReply(uint32_t transId, ENetError result,
                    const plUuid& acctUuid, const plUuid& activationKey);
    virtual void onPlayerCreateReply(uint32_t transId, ENetError result,
                    uint32_t playerId, uint32_t explorer,
                    const ST::string& playerName, const ST::string& avatarShape);
    virtual void onPlayerDeleteReply(uint32_t transId, ENetError result);
    virtual void onUpgradeVisitorReply(uint32_t transId, ENetError result);
    virtual void onSetPlayerBanStatusReply(uint32_t transId, ENetError result);
    virtual void onChangePlayerNameReply(uint32_t transId, ENetError result);
    virtual void onSendFriendInviteReply(uint32_t transId, ENetError result);
    virtual void onVaultNodeCreated(uint32_t transId, ENetError result,
                    uint32_t nodeId);
    virtual void onVaultNodeFetched(uint32_t transId, ENetError result,
                    const pnVaultNode& node);
    virtual void onVaultNodeChanged(uint32_t nodeId, const plUuid& revisionId);
    virtual void onVaultNodeDeleted(uint32_t nodeId);
    virtual void onVaultNodeAdded(uint32_t parent, uint32_t child, uint32_t owner);
    virtual void onVaultNodeRemoved(uint32_t parent, uint32_t child);
    virtual void onVaultNodeRefsFetched(uint32_t transId, ENetError result,
                    size_t count, const pnVaultNodeRef* refs);
    virtual void onVaultInitAgeReply(uint32_t transId, ENetError result,
                    uint32_t ageId, uint32_t ageInfoId);
    virtual void onVaultNodeFindReply(uint32_t transId, ENetError result,
                    size_t count, const uint32_t* nodes);
    virtual void onVaultSaveNodeReply(uint32_t transId, ENetError result);
    virtual void onVaultAddNodeReply(uint32_t transId, ENetError result);
    virtual void onVaultRemoveNodeReply(uint32_t transId, ENetError result);
    virtual void onAgeReply(uint32_t transId, ENetError result, uint32_t mcpId,
                    const plUuid& ageInstanceId, uint32_t ageVaultId,
                    uint32_t gameServerAddress);
    virtual void onAgeReplyEx(uint32_t transId, ENetError result, uint32_t mcpId,
                    const plUuid& ageInstanceId, uint32_t ageVaultId,
                    const ST::string& gameServerAddress);
    virtual void onFileListReply(uint32_t transId, ENetError result,
                    size_t count, const pnAuthFileItem* files);
    virtual void onFileDownloadChunk(uint32_t transId, ENetError result,
                    uint32_t totalSize, uint32_t chunkOffset, size_t chunkSize,
                    const unsigned char* chunkData);
    virtual void onKickedOff(uint32_t reason);
    virtual void onPublicAgeList(uint32_t transId, ENetError result,
                    size_t count, const pnNetAgeInfo* ages);
    virtual void onScoreCreateReply(uint32_t transId, ENetError result,
                    uint32_t scoreId, uint32_t createdTime);
    virtual void onScoreDeleteReply(uint32_t transId, ENetError result);
    virtual void onScoreGetScoresReply(uint32_t transId, ENetError result,
                    size_t count, const pnNetGameScore* scores);
    virtual void onScoreAddPointsReply(uint32_t transId, ENetError result);
    virtual void onScoreTransferPointsReply(uint32_t transId, ENetError result);
    virtual void onScoreSetPointsReply(uint32_t transId, ENetError result);
    virtual void onScoreGetRanksReply(uint32_t transId, ENetError result,
                    size_t count, const pnNetGameRank* ranks);
    virtual void onPropagateMessage(plCreatable* msg);

protected:
    pnRC4Socket* fSock;
    plResManager* fResMgr;
    bool fDeleteMsgs;
    bool fThreaded;

    uint32_t fBuildId, fBuildType, fBranchId;
    plUuid fProductId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];
    bool fLittleEndianKeys;
    int fKeyG;

    class Dispatch : public pnDispatcher
    {
    public:
        Dispatch(pnAuthClient* self, bool deleteMsgs)
            : fReceiver(self), fDeleteMsgs(deleteMsgs) { }
        ~Dispatch() { }
        bool dispatch(pnSocket* sock) HS_OVERRIDE;

    private:
        pnAuthClient* fReceiver;
        bool fDeleteMsgs;
    } *fDispatch;

    ENetError performConnect();
    void sendFileDownloadChunkAck(uint32_t transId);
};

#endif
