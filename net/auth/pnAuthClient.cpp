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

#include "pnAuthClient.h"
#include "AuthMessages.h"
#include "Debug/plDebug.h"
#include "Stream/hsRAMStream.h"
#include "crypt/pnBigInteger.h"
#include "crypt/pnSha1.h"

static size_t CountFiles(hsUint32 infoSize, const pl_wchar_t* infoBuffer)
{
    size_t count = 0;
    while (((int)infoSize) > 0 && *infoBuffer != 0) {
        size_t fnLen = plwcslen(infoBuffer);
        infoBuffer += fnLen + 4;    // '\0', filesize, '\0'
        infoSize -= fnLen + 4;
        count++;
    }
    return count;
}

static void GetFileList(pnAuthFileItem* files, hsUint32 infoSize,
                        const pl_wchar_t* infoBuffer)
{
    pnAuthFileItem* cur = files;
    while (((int)infoSize) > 0 && *infoBuffer != 0) {
        size_t fnLen = plwcslen(infoBuffer);
        cur->fFilename = plString(infoBuffer, fnLen);
        infoBuffer += fnLen + 1;
        infoSize -= fnLen + 1;

        cur->fFileSize = (infoBuffer[0] << 16) | (infoBuffer[1] & 0xFFFF);
        infoBuffer += 3;
        infoSize -= 3;
        cur++;
    }
}


/* Dispatch */
pnAuthClient::Dispatch::Dispatch(pnRC4Socket* sock, pnAuthClient* self)
            : fReceiver(self), fSock(sock)
{ }

void pnAuthClient::Dispatch::run()
{
    hsUint16 msgId;
    while (fSock->isConnected()) {
        if (!fSock->waitForData()) {
            // Got an error
            break;
        }

        fSock->recv(&msgId, sizeof(hsUint16));
        const pnNetMsg* msgDesc = GET_Auth2Cli(msgId);
        if (msgDesc == NULL) {
            plDebug::Error("Got invalid message ID (%u)", msgId);
            break;
        }

        msgparm_t* msgbuf = fSock->recvMsg(msgDesc);
        switch (msgId) {
        case kAuth2Cli_PingReply:
            fReceiver->onPingReply(msgbuf[1].fUint, msgbuf[0].fUint);
            if (msgbuf[2].fUint != 0)
                plDebug::Debug("Got non-zero payload");
            break;
        case kAuth2Cli_ServerAddr:
            fReceiver->onServerAddr(msgbuf[0].fUint, NCGetUuid(msgbuf[1]));
            break;
        case kAuth2Cli_NotifyNewBuild:
            fReceiver->onNotifyNewBuild(msgbuf[0].fUint);
            break;
        case kAuth2Cli_ClientRegisterReply:
            fReceiver->onClientRegisterReply(msgbuf[0].fUint);
            break;
        case kAuth2Cli_AcctExistsReply:
            fReceiver->onAcctExistsReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                         msgbuf[2].fUint != 0);
            break;
        case kAuth2Cli_AcctLoginReply:
            fReceiver->onAcctLoginReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            NCGetUuid(msgbuf[2]), msgbuf[3].fUint, msgbuf[4].fUint,
                            (const hsUint32*)msgbuf[5].fData);
            break;
        // case kAuth2Cli_AcctData:
        case kAuth2Cli_AcctPlayerInfo:
            fReceiver->onAcctPlayerInfo(msgbuf[0].fUint, msgbuf[1].fUint,
                            msgbuf[2].fString, msgbuf[3].fString, msgbuf[4].fUint);
            break;
        case kAuth2Cli_AcctSetPlayerReply:
            fReceiver->onAcctSetPlayerReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AcctCreateReply:
            fReceiver->onAcctCreateReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            NCGetUuid(msgbuf[2]));
            break;
        case kAuth2Cli_AcctChangePasswordReply:
            fReceiver->onAcctChangePasswordReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AcctSetRolesReply:
            fReceiver->onAcctSetRolesReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AcctSetBillingTypeReply:
            fReceiver->onAcctSetBillingTypeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AcctActivateReply:
            fReceiver->onAcctActivateReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AcctCreateFromKeyReply:
            fReceiver->onAcctCreateFromKeyReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            NCGetUuid(msgbuf[2]), NCGetUuid(msgbuf[3]));
            break;
        //case kAuth2Cli_PlayerList:
        //case kAuth2Cli_PlayerChat:
        case kAuth2Cli_PlayerCreateReply:
            fReceiver->onPlayerCreateReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, msgbuf[3].fUint,
                            msgbuf[4].fString, msgbuf[5].fString);
            break;
        case kAuth2Cli_PlayerDeleteReply:
            fReceiver->onPlayerDeleteReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_UpgradeVisitorReply:
            fReceiver->onUpgradeVisitorReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_SetPlayerBanStatusReply:
            fReceiver->onSetPlayerBanStatusReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_ChangePlayerNameReply:
            fReceiver->onChangePlayerNameReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_SendFriendInviteReply:
            fReceiver->onSendFriendInviteReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        //case kAuth2Cli_FriendNotify:
        case kAuth2Cli_VaultNodeCreated:
            fReceiver->onVaultNodeCreated(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint);
            break;
        case kAuth2Cli_VaultNodeFetched:
            {
                pnVaultNode node;
                node.read(msgbuf[3].fData, msgbuf[2].fUint);
                fReceiver->onVaultNodeFetched(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint, node);
            }
            break;
        case kAuth2Cli_VaultNodeChanged:
            fReceiver->onVaultNodeChanged(msgbuf[0].fUint, NCGetUuid(msgbuf[1]));
            break;
        case kAuth2Cli_VaultNodeDeleted:
            fReceiver->onVaultNodeDeleted(msgbuf[0].fUint);
            break;
        case kAuth2Cli_VaultNodeAdded:
            fReceiver->onVaultNodeAdded(msgbuf[0].fUint, msgbuf[1].fUint, msgbuf[2].fUint);
            break;
        case kAuth2Cli_VaultNodeRemoved:
            fReceiver->onVaultNodeRemoved(msgbuf[0].fUint, msgbuf[1].fUint);
            break;
        case kAuth2Cli_VaultNodeRefsFetched:
            {
                size_t numRefs = msgbuf[2].fUint;
                pnVaultNodeRef* refs = new pnVaultNodeRef[numRefs];
                for (size_t i=0; i<numRefs; i++)
                    refs[i].read(msgbuf[3].fData + (i * pnVaultNodeRef::Stride));
                fReceiver->onVaultNodeRefsFetched(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                numRefs, refs);
                delete[] refs;
            }
            break;
        case kAuth2Cli_VaultInitAgeReply:
            fReceiver->onVaultInitAgeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, msgbuf[3].fUint);
            break;
        case kAuth2Cli_VaultNodeFindReply:
            fReceiver->onVaultNodeFindReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, (const hsUint32*)msgbuf[3].fData);
            break;
        case kAuth2Cli_VaultSaveNodeReply:
            fReceiver->onVaultSaveNodeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_VaultAddNodeReply:
            fReceiver->onVaultAddNodeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_VaultRemoveNodeReply:
            fReceiver->onVaultRemoveNodeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_AgeReply:
            fReceiver->onAgeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, NCGetUuid(msgbuf[3]),
                            msgbuf[4].fUint, msgbuf[5].fUint);
            break;
        case kAuth2Cli_FileListReply:
            {
                size_t count = CountFiles(msgbuf[2].fUint, msgbuf[3].fString);
                pnAuthFileItem* files = new pnAuthFileItem[count];
                GetFileList(files, msgbuf[2].fUint, msgbuf[3].fString);
                fReceiver->onFileListReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                count, files);
                delete[] files;
            }
            break;
        case kAuth2Cli_FileDownloadChunk:
            fReceiver->onFileDownloadChunk(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, msgbuf[3].fUint, msgbuf[4].fUint,
                            msgbuf[5].fData);
            fReceiver->sendFileDownloadChunkAck(msgbuf[0].fUint);
            break;
        case kAuth2Cli_KickedOff:
            fReceiver->onKickedOff(msgbuf[0].fUint);
            break;
        case kAuth2Cli_PublicAgeList:
            {
                size_t ageCount = msgbuf[2].fUint;
                pnNetAgeInfo* ages = new pnNetAgeInfo[ageCount];
                for (size_t i=0; i<ageCount; i++)
                    ages[i].read(msgbuf[3].fData + (i * pnNetAgeInfo::Stride));
                fReceiver->onPublicAgeList(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                ageCount, ages);
                delete[] ages;
            }
            break;
        case kAuth2Cli_ScoreCreateReply:
            fReceiver->onScoreCreateReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            msgbuf[2].fUint, msgbuf[3].fUint);
            break;
        case kAuth2Cli_ScoreDeleteReply:
            fReceiver->onScoreDeleteReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_ScoreGetScoresReply:
            {
                size_t scoreCount = msgbuf[2].fUint;
                pnNetGameScore* scores = new pnNetGameScore[scoreCount];
                const hsUbyte* buf = msgbuf[3].fData;
                for (size_t i=0; i<scoreCount; i++) {
                    scores[i].fScoreId     = *(hsUint32*)(buf     );
                    scores[i].fOwnerId     = *(hsUint32*)(buf +  4);
                    scores[i].fCreatedTime = *(hsUint32*)(buf +  8);
                    scores[i].fGameType    = *(hsUint32*)(buf + 12);
                    scores[i].fValue       = *(hsInt32* )(buf + 16);
                    size_t strDataSize     = *(hsUint32*)(buf + 20);
                    scores[i].fGameName    = (const pl_wchar_t*)(buf + 24);
                    buf += 24 + strDataSize;
                }
                fReceiver->onScoreGetScoresReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                scoreCount, scores);
                delete[] scores;
            }
            break;
        case kAuth2Cli_ScoreAddPointsReply:
            fReceiver->onScoreAddPointsReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_ScoreTransferPointsReply:
            fReceiver->onScoreTransferPointsReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_ScoreSetPointsReply:
            fReceiver->onScoreSetPointsReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kAuth2Cli_ScoreGetRanksReply:
            {
                size_t rankCount = msgbuf[2].fUint;
                pnNetGameRank* ranks = new pnNetGameRank[rankCount];
                const hsUbyte* buf = msgbuf[3].fData;
                for (size_t i=0; i<rankCount; i++) {
                    ranks[i].fRank     = *(hsUint32*)(buf    );
                    ranks[i].fScore    = *(hsUint32*)(buf + 4);
                    size_t strDataSize = *(hsUint32*)(buf + 8);
                    ranks[i].fName     = (const pl_wchar_t*)(buf + 12);
                    buf += 12 + strDataSize;
                }
                fReceiver->onScoreGetRanksReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                                rankCount, ranks);
                delete[] ranks;
            }
            break;
        case kAuth2Cli_PropagateBuffer:
            {
                hsRAMStream rs(pvLive);
                rs.copyFrom(msgbuf[2].fData, msgbuf[1].fUint);
                fReceiver->fResMgr->lock();
                plCreatable* pCre = NULL;
                try {
                    pCre = fReceiver->fResMgr->ReadCreatable(&rs, true, msgbuf[1].fUint);
                } catch (hsException& ex) {
                    plDebug::Error("Error reading propagated message: %s\n", ex.what());
                    delete pCre;
                    pCre = NULL;
                }
                fReceiver->fResMgr->unlock();
                if (pCre != NULL) {
                    fReceiver->onPropagateMessage(pCre);
                    delete pCre;
                } else {
                    plDebug::Error("Ignored propagated message [%04X]%s",
                                   pdUnifiedTypeMap::PlasmaToMapped(msgbuf[0].fUint, pvLive),
                                   pdUnifiedTypeMap::ClassName(msgbuf[0].fUint, pvLive));
                }
            }
            break;
        }
        NCFreeMessage(msgbuf, msgDesc);
        fSock->signalStatus();
    } /* while connected */
}


/* pnAuthClient */
pnAuthClient::pnAuthClient(plResManager* mgr)
            : fSock(NULL), fResMgr(mgr), fDispatch(NULL)
{ }

pnAuthClient::~pnAuthClient()
{
    if (fSock != NULL)
        fSock->close();
    delete fDispatch;
    delete fSock;
}

void pnAuthClient::setKeys(const unsigned char* keyX, const unsigned char* keyN)
{
    memcpy(fKeyX, keyX, 64);
    memcpy(fKeyN, keyN, 64);
}

void pnAuthClient::setClientInfo(hsUint32 buildId, hsUint32 buildType,
                                 hsUint32 branchId, const plUuid& productId)
{
    fBuildId = buildId;
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

ENetError pnAuthClient::connect(const char* host, short port)
{
    pnSocket* sock = new pnSocket();
    if (!sock->connect(host, port)) {
        plDebug::Error("Error connecting to auth server\n");
        delete sock;
        return kNetErrConnectFailed;
    }
    return performConnect(sock);
}

ENetError pnAuthClient::connect(int sockFd)
{
    pnSocket* sock = new pnSocket(sockFd);
    return performConnect(sock);
}

void pnAuthClient::disconnect()
{
    if (fSock != NULL)
        fSock->close();
    delete fDispatch;
    delete fSock;
    fSock = NULL;
    fDispatch = NULL;
}

ENetError pnAuthClient::performConnect(pnSocket* sock)
{
    fSock = new pnRC4Socket(sock);

    hsUbyte connectHeader[51];  // ConnectHeader + AuthConnectHeader
    /* Begin ConnectHeader */
    *(hsUbyte* )(connectHeader     ) = kConnTypeCliToAuth;
    *(hsUint16*)(connectHeader +  1) = 31;
    *(hsUint32*)(connectHeader +  3) = fBuildId;
    *(hsUint32*)(connectHeader +  7) = fBuildType;
    *(hsUint32*)(connectHeader + 11) = fBranchId;
    fProductId.write(connectHeader + 15);
    /* Begin AuthConnectHeader */
    *(hsUint32*)(connectHeader + 31) = 20;
    memset(connectHeader + 35, 0, 16);
    fSock->send(connectHeader, 51);

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error establishing Auth connection");
        return kNetErrConnectFailed;
    }

    /* Set up encryption */
    hsUbyte y_data[64];
    pnBigInteger clientSeed;
    {
        pnBigInteger X(fKeyX, 64);
        pnBigInteger N(fKeyN, 64);
        pnBigInteger b = pnBigInteger::Random(512);
        clientSeed = X.PowMod(b, N);
        pnBigInteger serverSeed = pnBigInteger(41).PowMod(b, N);
        serverSeed.getData(y_data, 64);
    }

    hsUbyte cryptHeader[66];
    *(hsUbyte*)(cryptHeader    ) = kNetCliCli2SrvConnect;
    *(hsUbyte*)(cryptHeader + 1) = 66;
    memcpy(cryptHeader + 2, y_data, 64);
    fSock->send(cryptHeader, 66);

    hsUbyte msg, len;
    if (fSock->recv(&msg, 1) <= 0 || fSock->recv(&len, 1) <= 0) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error negotiating Auth connection");
        return kNetErrConnectFailed;
    }

    if (msg == kNetCliSrv2CliEncrypt) {
        hsUbyte serverSeed[7];
        fSock->recv(serverSeed, 7);
        hsUbyte seedData[64];
        clientSeed.getData(seedData, 64);
        for (size_t i=0; i<7; i++)
            serverSeed[i] ^= seedData[i];
        fSock->init(7, serverSeed);
    } else if (msg == kNetCliSrv2CliError) {
        hsUint32 errorCode;
        fSock->recv(&errorCode, sizeof(hsUint32));
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error connecting to Auth server: %s",
                       GetNetErrorString(errorCode));
        return (ENetError)errorCode;
    } else {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Got junk response from server");
        return kNetErrConnectFailed;
    }
    fDispatch = new Dispatch(fSock, this);
    fDispatch->start();
    return kNetSuccess;
}

hsUint32 pnAuthClient::sendPingRequest(hsUint32 pingTimeMs)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PingRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = pingTimeMs;
    msg[1].fUint = transId;
    msg[2].fUint = 0;
    msg[3].fData = NULL;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendClientRegisterRequest()
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ClientRegisterRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = fBuildId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendClientSetCCRLevel(hsUint32 level)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ClientSetCCRLevel);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = level;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnAuthClient::sendAcctExistsRequest(const plString& acctName)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctExistsRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctLoginRequest(hsUint32 serverChallenge,
                hsUint32 clientChallenge, const plString& acctName,
                const plString& password, const plString& authToken,
                const plString& os)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctLoginRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = clientChallenge;
    msg[2].fString = plwcsdup(acctName.wstr());
    pnSha1Hash hash = NCHashLoginInfo(acctName, password, serverChallenge, clientChallenge);
    memcpy(msg[3].fData, &hash, sizeof(hash));
    msg[4].fString = plwcsdup(authToken.wstr());
    msg[5].fString = plwcsdup(os.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctSetPlayerRequest(hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetPlayerRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctCreateRequest(const plString& acctName,
                const plString& password, hsUint32 acctFlags,
                hsUint32 billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctCreateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    msg[3].fUint = acctFlags;
    msg[4].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctChangePasswordRequest(const plString& acctName,
                const plString& password)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctChangePasswordRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctSetRolesRequest(const plString& acctName, hsUint32 acctFlags)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetRolesRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    msg[2].fUint = acctFlags;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctSetBillingTypeRequest(const plString& acctName, hsUint32 billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetBillingTypeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    msg[2].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctActivateRequest(const plUuid& activationKey)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctActivateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    activationKey.write(msg[1].fData);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendAcctCreateFromKeyRequest(const plString& acctName,
                const plString& password, const plUuid& key, hsUint32 billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctCreateFromKeyRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    key.write(msg[3].fData);
    msg[4].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendPlayerDeleteRequest(hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PlayerDeleteRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendPlayerCreateRequest(const plString& playerName,
                const plString& playerShape, const plString& friendInvite)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PlayerCreateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(playerName.wstr());
    msg[2].fString = plwcsdup(playerShape.wstr());
    msg[3].fString = plwcsdup(friendInvite.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendUpgradeVisitorRequest(hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_UpgradeVisitorRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendSetPlayerBanStatusRequest(hsUint32 playerId, hsUint32 banned)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SetPlayerBanStatusRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    msg[2].fUint = banned;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendKickPlayer(hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_KickPlayer);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnAuthClient::sendChangePlayerNameRequest(hsUint32 playerId, const plString& name)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ChangePlayerNameRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    msg[2].fString = plwcsdup(name.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendFriendInviteRequest(const plUuid& invite, const plString& email,
                const plString& sendTo)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SendFriendInviteRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    invite.write(msg[1].fData);
    msg[2].fString = plwcsdup(email.wstr());
    msg[3].fString = plwcsdup(sendTo.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeCreate(const pnVaultNode& node)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeCreate);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = node.bufferSize();
    msg[2].fData = new hsUbyte[msg[1].fUint];
    node.write(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeFetch(hsUint32 nodeId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeFetch);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeSave(hsUint32 nodeId, const plUuid& revisionId,
                const pnVaultNode& node)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeSave);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    revisionId.write(msg[2].fData);
    msg[3].fUint = node.bufferSize();
    msg[4].fData = new hsUbyte[msg[3].fUint];
    node.write(msg[4].fData, msg[3].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeAdd(hsUint32 parent, hsUint32 child, hsUint32 owner)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeAdd);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = parent;
    msg[2].fUint = child;
    msg[3].fUint = owner;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeRemove(hsUint32 parent, hsUint32 child)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeRemove);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = parent;
    msg[2].fUint = child;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultFetchNodeRefs(hsUint32 nodeId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultFetchNodeRefs);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultInitAgeRequest(const plUuid& ageUuid, const plString& filename,
                const plString& instanceName, const plString& userDefinedName,
                const plString& description, hsUint32 sequence, hsUint32 language,
                const plUuid& parentUuid)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultInitAgeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    ageUuid.write(msg[1].fData);
    parentUuid.write(msg[2].fData);
    msg[3].fString = plwcsdup(filename.wstr());
    msg[4].fString = plwcsdup(instanceName.wstr());
    msg[5].fString = plwcsdup(userDefinedName.wstr());
    msg[6].fString = plwcsdup(description.wstr());
    msg[7].fUint = sequence;
    msg[8].fUint = language;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendVaultNodeFind(const pnVaultNode& templateNode)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeFind);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = templateNode.bufferSize();
    msg[2].fData = new hsUbyte[msg[1].fUint];
    templateNode.write(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendVaultSetSeen(hsUint32 parent, hsUint32 child, hsUbyte seen)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultSetSeen);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = parent;
    msg[1].fUint = child;
    msg[2].fUint = seen;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendVaultSendNode(hsUint32 nodeId, hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultSendNode);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = nodeId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnAuthClient::sendAgeRequest(const plString& ageName, const plUuid& ageUuid)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AgeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(ageName.wstr());
    ageUuid.write(msg[2].fData);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendFileListRequest(const plString& directory, const plString& ext)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileListRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(directory.wstr());
    msg[2].fString = plwcsdup(ext.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendFileDownloadRequest(const plString& filename)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileDownloadRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(filename.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendFileDownloadChunkAck(hsUint32 transId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileDownloadChunkAck);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = transId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnAuthClient::sendGetPublicAgeList(const plString& filename)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_GetPublicAgeList);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(filename.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendSetAgePublic(hsUint32 ageInfoId, hsUbyte isPublic)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SetAgePublic);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = ageInfoId;
    msg[1].fUint = isPublic;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendLogPythonTraceback(const plString& traceback)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_LogPythonTraceback);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fString = plwcsdup(traceback.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendLogStackDump(const plString& stackdump)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_LogStackDump);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fString = plwcsdup(stackdump.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendLogClientDebuggerConnect()
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_LogClientDebuggerConnect);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = 0;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnAuthClient::sendScoreCreate(hsUint32 owner, const plString& gameName,
            hsUint32 gameType, hsUint32 scoreValue)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreCreate);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = owner;
    msg[2].fString = plwcsdup(gameName.wstr());
    msg[3].fUint = gameType;
    msg[4].fUint = scoreValue;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreDelete(hsUint32 scoreId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreDelete);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreGetScores(hsUint32 owner, const plString& gameName)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreGetScores);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = owner;
    msg[2].fString = plwcsdup(gameName.wstr());
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreAddPoints(hsUint32 scoreId, hsUint32 points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreAddPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    msg[2].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreTransferPoints(hsUint32 source, hsUint32 dest, hsUint32 points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreTransferPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = source;
    msg[2].fUint = dest;
    msg[3].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreSetPoints(hsUint32 scoreId, hsUint32 points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreSetPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    msg[2].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnAuthClient::sendScoreGetRanks(hsUint32 ownerId, hsUint32 group, hsUint32 parent,
                const plString& gameName, hsUint32 timePeriod, hsUint32 numResults,
                hsUint32 pageNumber, hsUint32 sortDesc)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreGetRanks);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = ownerId;
    msg[2].fUint = group;
    msg[3].fUint = parent;
    msg[4].fString = plwcsdup(gameName.wstr());
    msg[5].fUint = timePeriod;
    msg[6].fUint = numResults;
    msg[7].fUint = pageNumber;
    msg[8].fUint = sortDesc;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::propagateMessage(plCreatable* pCre)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PropagateBuffer);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = pCre->ClassIndex(pvLive);
    hsRAMStream rs(pvLive);
    fResMgr->lock();
    fResMgr->WriteCreatable(&rs, pCre);
    fResMgr->unlock();
    msg[1].fUint = rs.size();
    msg[2].fData = new hsUbyte[msg[1].fUint];
    rs.copyTo(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::onPingReply(hsUint32 transId, hsUint32 pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PingReply");
}

void pnAuthClient::onServerAddr(hsUint32 address, const plUuid& token)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ServerAddr");
}

void pnAuthClient::onNotifyNewBuild(hsUint32 buildId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_NotifyNewBuild");
}

void pnAuthClient::onClientRegisterReply(hsUint32 serverChallenge)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ClientRegisterReply");
}

void pnAuthClient::onAcctExistsReply(hsUint32 transId, ENetError result, bool exists)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctExistsReply");
}

void pnAuthClient::onAcctLoginReply(hsUint32 transId, ENetError result,
                        const plUuid& acctUuid, hsUint32 acctFlags,
                        hsUint32 billingType, const hsUint32* encryptionKey)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctLoginReply");
}

void pnAuthClient::onAcctPlayerInfo(hsUint32 transId, hsUint32 playerId,
                        const plString& playerName, const plString& avatarModel,
                        hsUint32 explorer)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctPlayerInfo");
}

void pnAuthClient::onAcctSetPlayerReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetPlayerReply");
}

void pnAuthClient::onAcctCreateReply(hsUint32 transId, ENetError result,
                        const plUuid& accountUuid)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctCreateReply");
}

void pnAuthClient::onAcctChangePasswordReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctChangePasswordReply");
}

void pnAuthClient::onAcctSetRolesReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetRolesReply");
}

void pnAuthClient::onAcctSetBillingTypeReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetBillingTypeReply");
}

void pnAuthClient::onAcctActivateReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctActivateReply");
}

void pnAuthClient::onAcctCreateFromKeyReply(hsUint32 transId, ENetError result,
                        const plUuid& acctUuid, const plUuid& activationKey)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctCreateFromKeyReply");
}

void pnAuthClient::onPlayerCreateReply(hsUint32 transId, ENetError result,
                        hsUint32 playerId, hsUint32 explorer,
                        const plString& playerName, const plString& avatarShape)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PlayerCreateReply");
}

void pnAuthClient::onPlayerDeleteReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PlayerDeleteReply");
}

void pnAuthClient::onUpgradeVisitorReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_UpgradeVisitorReply");
}

void pnAuthClient::onSetPlayerBanStatusReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_SetPlayerBanStatusReply");
}

void pnAuthClient::onChangePlayerNameReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ChangePlayerNameReply");
}

void pnAuthClient::onSendFriendInviteReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_SendFriendInviteReply");
}

void pnAuthClient::onVaultNodeCreated(hsUint32 transId, ENetError result,
                        hsUint32 nodeId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeCreated");
}

void pnAuthClient::onVaultNodeFetched(hsUint32 transId, ENetError result,
                        const pnVaultNode& node)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeFetched");
}

void pnAuthClient::onVaultNodeChanged(hsUint32 nodeId, const plUuid& revisionId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeChanged");
}

void pnAuthClient::onVaultNodeDeleted(hsUint32 nodeId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeDeleted");
}

void pnAuthClient::onVaultNodeAdded(hsUint32 parent, hsUint32 child, hsUint32 owner)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeAdded");
}

void pnAuthClient::onVaultNodeRemoved(hsUint32 parent, hsUint32 child)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeRemoved");
}

void pnAuthClient::onVaultNodeRefsFetched(hsUint32 transId, ENetError result,
                        size_t count, const pnVaultNodeRef* refs)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeRefsFetched");
}

void pnAuthClient::onVaultInitAgeReply(hsUint32 transId, ENetError result,
                        hsUint32 ageId, hsUint32 ageInfoId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultInitAgeReply");
}

void pnAuthClient::onVaultNodeFindReply(hsUint32 transId, ENetError result,
                        size_t count, const hsUint32* nodes)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeFindReply");
}

void pnAuthClient::onVaultSaveNodeReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultSaveNodeReply");
}

void pnAuthClient::onVaultAddNodeReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultAddNodeReply");
}

void pnAuthClient::onVaultRemoveNodeReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultRemoveNodeReply");
}

void pnAuthClient::onAgeReply(hsUint32 transId, ENetError result, hsUint32 mcpId,
                        const plUuid& ageInstanceId, hsUint32 ageVaultId,
                        hsUint32 gameServerAddress)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AgeReply");
}

void pnAuthClient::onFileListReply(hsUint32 transId, ENetError result,
                        size_t count, const pnAuthFileItem* files)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_FileListReply");
}

void pnAuthClient::onFileDownloadChunk(hsUint32 transId, ENetError result,
                        hsUint32 totalSize, hsUint32 chunkOffset, size_t chunkSize,
                        const unsigned char* chunkData)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_FileDownloadChunk");
}

void pnAuthClient::onKickedOff(hsUint32 reason)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_KickedOff");
}

void pnAuthClient::onPublicAgeList(hsUint32 transId, ENetError result,
                        size_t count, const pnNetAgeInfo* ages)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PublicAgeList");
}

void pnAuthClient::onScoreCreateReply(hsUint32 transId, ENetError result,
                        hsUint32 scoreId, hsUint32 createdTime)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreCreateReply");
}

void pnAuthClient::onScoreDeleteReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreDeleteReply");
}

void pnAuthClient::onScoreGetScoresReply(hsUint32 transId, ENetError result,
                        size_t count, const pnNetGameScore* scores)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreGetScoresReply");
}

void pnAuthClient::onScoreAddPointsReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreAddPointsReply");
}

void pnAuthClient::onScoreTransferPointsReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreTransferPointsReply");
}

void pnAuthClient::onScoreSetPointsReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreSetPointsReply");
}

void pnAuthClient::onScoreGetRanksReply(hsUint32 transId, ENetError result,
                        size_t count, const pnNetGameRank* ranks)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreGetRanksReply");
}

void pnAuthClient::onPropagateMessage(plCreatable* msg)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PropagateBuffer");
}
