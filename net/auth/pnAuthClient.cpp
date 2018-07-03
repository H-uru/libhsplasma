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
#include <cstring>

static size_t CountFiles(uint32_t infoSize, const char16_t* infoBuffer)
{
    size_t count = 0;
    while (((int)infoSize) > 0 && *infoBuffer != 0) {
        size_t fnLen = ST::utf16_buffer::strlen(infoBuffer);
        infoBuffer += fnLen + 4;    // '\0', filesize, '\0'
        infoSize -= fnLen + 4;
        count++;
    }
    return count;
}

static void GetFileList(pnAuthFileItem* files, uint32_t infoSize,
                        const char16_t* infoBuffer)
{
    pnAuthFileItem* cur = files;
    while (((int)infoSize) > 0 && *infoBuffer != 0) {
        size_t fnLen = ST::utf16_buffer::strlen(infoBuffer);
        cur->fFilename = ST::string::from_utf16(infoBuffer, fnLen);
        infoBuffer += fnLen + 1;
        infoSize -= fnLen + 1;

        cur->fFileSize = (infoBuffer[0] << 16) | (infoBuffer[1] & 0xFFFF);
        infoBuffer += 3;
        infoSize -= 3;
        cur++;
    }
}


/* Dispatch */
bool pnAuthClient::Dispatch::dispatch(pnSocket* sock)
{
    uint16_t msgId;

    sock->recv(&msgId, sizeof(uint16_t));
    const pnNetMsg* msgDesc = GET_Auth2Cli(msgId);
    if (msgDesc == NULL) {
        plDebug::Error("Got invalid message ID ({})", msgId);
        return false;
    }

    msgparm_t* msgbuf = sock->recvMsg(msgDesc);
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
                        (const uint32_t*)msgbuf[5].fData);
        break;
    // case kAuth2Cli_AcctData:
    case kAuth2Cli_AcctPlayerInfo:
        fReceiver->onAcctPlayerInfo(msgbuf[0].fUint, msgbuf[1].fUint,
                        ST::string::from_utf16(msgbuf[2].fString),
                        ST::string::from_utf16(msgbuf[3].fString), msgbuf[4].fUint);
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
                        ST::string::from_utf16(msgbuf[4].fString),
                        ST::string::from_utf16(msgbuf[5].fString));
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
            ENetError result = (ENetError)msgbuf[1].fUint;
            pnVaultNode node;
            if (result == kNetSuccess)
                node.read(msgbuf[3].fData, msgbuf[2].fUint);
            fReceiver->onVaultNodeFetched(msgbuf[0].fUint, result, node);
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
                        msgbuf[2].fUint, (const uint32_t*)msgbuf[3].fData);
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
    case kAuth2Cli_AgeReplyEx:
        fReceiver->onAgeReplyEx(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                        msgbuf[2].fUint, NCGetUuid(msgbuf[3]),
                        msgbuf[4].fUint, ST::string::from_utf16(msgbuf[5].fString));
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
        fReceiver->sendFileDownloadChunkAck(msgbuf[0].fUint);
        fReceiver->onFileDownloadChunk(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                        msgbuf[2].fUint, msgbuf[3].fUint, msgbuf[4].fUint,
                        msgbuf[5].fData);
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
            const uint8_t* buf = msgbuf[3].fData;
            for (size_t i=0; i<scoreCount; i++) {
                scores[i].fScoreId     = NCReadBuffer<uint32_t>(buf);
                scores[i].fOwnerId     = NCReadBuffer<uint32_t>(buf);
                scores[i].fCreatedTime = NCReadBuffer<uint32_t>(buf);
                scores[i].fGameType    = NCReadBuffer<uint32_t>(buf);
                scores[i].fValue       = NCReadBuffer<int32_t>(buf);
                size_t strDataSize     = NCReadBuffer<uint32_t>(buf);
                scores[i].fGameName    = ST::string::from_utf16((const char16_t*)buf);
                buf += strDataSize;
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
            const uint8_t* buf = msgbuf[3].fData;
            for (size_t i=0; i<rankCount; i++) {
                ranks[i].fRank     = NCReadBuffer<uint32_t>(buf);
                ranks[i].fScore    = NCReadBuffer<uint32_t>(buf);
                size_t strDataSize = NCReadBuffer<uint32_t>(buf);
                ranks[i].fName     = ST::string::from_utf16((const char16_t*)buf);
                buf += strDataSize;
            }
            fReceiver->onScoreGetRanksReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint,
                            rankCount, ranks);
            delete[] ranks;
        }
        break;
    case kAuth2Cli_PropagateBuffer:
        {
            hsRAMStream rs(PlasmaVer::pvMoul);
            rs.copyFrom(msgbuf[2].fData, msgbuf[1].fUint);
            plCreatable* pCre = NULL;
            {
                std::lock_guard<plResManager> resMgrLock(*fReceiver->fResMgr);
                try {
                    pCre = fReceiver->fResMgr->ReadCreatable(&rs, true, msgbuf[1].fUint);
                } catch (hsException& ex) {
                    plDebug::Error("Error reading propagated message: {}\n", ex.what());
                    delete pCre;
                    pCre = NULL;
                }
            }
            if (pCre != NULL) {
                fReceiver->onPropagateMessage(pCre);
                if (fDeleteMsgs)
                    delete pCre;
            } else {
                plDebug::Error("Ignored propagated message [{_04X}]{}",
                                pdUnifiedTypeMap::PlasmaToMapped(msgbuf[0].fUint, PlasmaVer::pvMoul),
                                pdUnifiedTypeMap::ClassName(msgbuf[0].fUint, PlasmaVer::pvMoul));
            }
        }
        break;
    }
    NCFreeMessage(msgbuf, msgDesc);
    return true;
}


/* pnAuthClient */
pnAuthClient::~pnAuthClient()
{
    delete fIface;
    delete fDispatch;
    delete fSock;
}

void pnAuthClient::setKeys(const unsigned char* keyX, const unsigned char* keyN, bool littleEndian)
{
    fLittleEndianKeys = littleEndian;
    memcpy(fKeyX, keyX, 64);
    memcpy(fKeyN, keyN, 64);
}

void pnAuthClient::setClientInfo(uint32_t buildId, uint32_t buildType,
                                 uint32_t branchId, const plUuid& productId)
{
    fBuildId = buildId;
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

ENetError pnAuthClient::connect(const char* host, short port)
{
    fSock = new pnRC4Socket();
    if (!fSock->connect(host, port)) {
        plDebug::Error("Error connecting to auth server\n");
        delete fSock;
        return kNetErrConnectFailed;
    }
    return performConnect();
}

ENetError pnAuthClient::connect(int sockFd)
{
    fSock = new pnRC4Socket(sockFd);
    return performConnect();
}

void pnAuthClient::disconnect()
{
    delete fIface;
    delete fDispatch;
    delete fSock;
    fIface = NULL;
    fSock = NULL;
    fDispatch = NULL;
}

ENetError pnAuthClient::performConnect()
{
    hsRAMStream connectHeader;
    /* Begin ConnectHeader */
    connectHeader.writeByte(kConnTypeCliToAuth);
    connectHeader.writeShort(31);
    connectHeader.writeInt(fBuildId);
    connectHeader.writeInt(fBuildType);
    connectHeader.writeInt(fBranchId);
    fProductId.write(&connectHeader);
    /* Begin AuthConnectHeader */
    connectHeader.writeInt(20);
    plUuid::Null.write(&connectHeader);
    fSock->send(connectHeader.data(), connectHeader.size());

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error establishing Auth connection");
        return kNetErrConnectFailed;
    }

    /* Set up encryption */
    uint8_t y_data[64];
    pnBigInteger clientSeed;
    {
        pnBigInteger X(fKeyX, 64, fLittleEndianKeys);
        pnBigInteger N(fKeyN, 64, fLittleEndianKeys);
        pnBigInteger b = pnBigInteger::Random(512);
        clientSeed = X.PowMod(b, N);
        pnBigInteger serverSeed = pnBigInteger(fKeyG).PowMod(b, N);
        serverSeed.getData(y_data, 64);
    }

    hsRAMStream cryptHeader;
    cryptHeader.writeByte(kNetCliCli2SrvConnect);
    cryptHeader.writeByte(66);
    cryptHeader.write(64, y_data);
    fSock->send(cryptHeader.data(), cryptHeader.size());

    uint8_t msg, len;
    if (fSock->recv(&msg, 1) <= 0 || fSock->recv(&len, 1) <= 0) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error negotiating Auth connection");
        return kNetErrConnectFailed;
    }

    if (msg == kNetCliSrv2CliEncrypt) {
        uint8_t serverSeed[7];
        fSock->recv(serverSeed, 7);
        uint8_t seedData[64];
        clientSeed.getData(seedData, 64);
        for (size_t i=0; i<7; i++)
            serverSeed[i] ^= seedData[i];
        fSock->init(7, serverSeed);
    } else if (msg == kNetCliSrv2CliError) {
        uint32_t errorCode;
        fSock->recv(&errorCode, sizeof(uint32_t));
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error connecting to Auth server: {}",
                       GetNetErrorString(errorCode));
        return (ENetError)errorCode;
    } else {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Got junk response from server");
        return kNetErrConnectFailed;
    }
    fDispatch = new Dispatch(this, fDeleteMsgs);
    if (fThreaded)
        fIface = new pnThreadedSocket(fDispatch, fSock);
    else
        fIface = new pnPolledSocket(fDispatch, fSock);
    fIface->run();
    return kNetSuccess;
}

uint32_t pnAuthClient::sendPingRequest(uint32_t pingTimeMs)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PingRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
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

void pnAuthClient::sendClientSetCCRLevel(uint32_t level)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ClientSetCCRLevel);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = level;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

uint32_t pnAuthClient::sendAcctExistsRequest(const ST::string& acctName)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctExistsRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctLoginRequest(uint32_t serverChallenge,
                uint32_t clientChallenge, const ST::string& acctName,
                const ST::string& password, const ST::string& authToken,
                const ST::string& os)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctLoginRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = clientChallenge;
    msg[2].fString = NCCopyString(acctName);
    pnSha1Hash hash;
    if (acctName.find('@') != -1 && acctName.find("@gametap") == -1
        && acctName.find("@magiquest") == -1) {
        hash = NCHashLoginInfo(acctName, password, serverChallenge, clientChallenge);
    } else {
        hash = pnSha1Hash::Sha1(password.c_str(), password.size());
        hash.swapBytes();   // Cyan uses a different byte order for this case
    }
    memcpy(msg[3].fData, &hash, sizeof(hash));
    msg[4].fString = NCCopyString(authToken);
    msg[5].fString = NCCopyString(os);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctSetPlayerRequest(uint32_t playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetPlayerRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctCreateRequest(const ST::string& acctName,
                const ST::string& password, uint32_t acctFlags,
                uint32_t billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctCreateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    msg[3].fUint = acctFlags;
    msg[4].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctChangePasswordRequest(const ST::string& acctName,
                const ST::string& password)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctChangePasswordRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctSetRolesRequest(const ST::string& acctName, uint32_t acctFlags)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetRolesRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    msg[2].fUint = acctFlags;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctSetBillingTypeRequest(const ST::string& acctName, uint32_t billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctSetBillingTypeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    msg[2].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctActivateRequest(const plUuid& activationKey)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctActivateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    activationKey.write(msg[1].fData);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAcctCreateFromKeyRequest(const ST::string& acctName,
                const ST::string& password, const plUuid& key, uint32_t billingType)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctCreateFromKeyRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(acctName);
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    key.write(msg[3].fData);
    msg[4].fUint = billingType;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendPlayerDeleteRequest(uint32_t playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PlayerDeleteRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendPlayerCreateRequest(const ST::string& playerName,
                const ST::string& playerShape, const ST::string& friendInvite)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_PlayerCreateRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(playerName);
    msg[2].fString = NCCopyString(playerShape);
    msg[3].fString = NCCopyString(friendInvite);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendUpgradeVisitorRequest(uint32_t playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_UpgradeVisitorRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendSetPlayerBanStatusRequest(uint32_t playerId, uint32_t banned)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SetPlayerBanStatusRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    msg[2].fUint = banned;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendKickPlayer(uint32_t playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_KickPlayer);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

uint32_t pnAuthClient::sendChangePlayerNameRequest(uint32_t playerId, const ST::string& name)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ChangePlayerNameRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = playerId;
    msg[2].fString = NCCopyString(name);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendFriendInviteRequest(const plUuid& invite, const ST::string& email,
                const ST::string& sendTo)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SendFriendInviteRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    invite.write(msg[1].fData);
    msg[2].fString = NCCopyString(email);
    msg[3].fString = NCCopyString(sendTo);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeCreate(const pnVaultNode& node)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeCreate);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = node.bufferSize();
    msg[2].fData = new uint8_t[msg[1].fUint];
    node.write(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeFetch(uint32_t nodeId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeFetch);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeSave(uint32_t nodeId, const plUuid& revisionId,
                const pnVaultNode& node)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeSave);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    revisionId.write(msg[2].fData);
    msg[3].fUint = node.bufferSize();
    msg[4].fData = new uint8_t[msg[3].fUint];
    node.write(msg[4].fData, msg[3].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeAdd(uint32_t parent, uint32_t child, uint32_t owner)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeAdd);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = parent;
    msg[2].fUint = child;
    msg[3].fUint = owner;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeRemove(uint32_t parent, uint32_t child)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeRemove);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = parent;
    msg[2].fUint = child;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultFetchNodeRefs(uint32_t nodeId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultFetchNodeRefs);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = nodeId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultInitAgeRequest(const plUuid& ageUuid, const ST::string& filename,
                const ST::string& instanceName, const ST::string& userDefinedName,
                const ST::string& description, uint32_t sequence, uint32_t language,
                const plUuid& parentUuid)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultInitAgeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    ageUuid.write(msg[1].fData);
    parentUuid.write(msg[2].fData);
    msg[3].fString = NCCopyString(filename);
    msg[4].fString = NCCopyString(instanceName);
    msg[5].fString = NCCopyString(userDefinedName);
    msg[6].fString = NCCopyString(description);
    msg[7].fUint = sequence;
    msg[8].fUint = language;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendVaultNodeFind(const pnVaultNode& templateNode)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultNodeFind);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = templateNode.bufferSize();
    msg[2].fData = new uint8_t[msg[1].fUint];
    templateNode.write(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendVaultSetSeen(uint32_t parent, uint32_t child, uint8_t seen)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultSetSeen);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = parent;
    msg[1].fUint = child;
    msg[2].fUint = seen;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendVaultSendNode(uint32_t nodeId, uint32_t playerId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_VaultSendNode);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = nodeId;
    msg[1].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

uint32_t pnAuthClient::sendAgeRequest(const ST::string& ageName, const plUuid& ageUuid)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AgeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(ageName);
    ageUuid.write(msg[2].fData);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendAgeRequestEx(const ST::string& ageName, const plUuid& ageUuid)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AgeRequestEx);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(ageName);
    ageUuid.write(msg[2].fData);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendFileListRequest(const ST::string& directory, const ST::string& ext)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileListRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(directory);
    msg[2].fString = NCCopyString(ext);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendFileDownloadRequest(const ST::string& filename)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileDownloadRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(filename);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendFileDownloadChunkAck(uint32_t transId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_FileDownloadChunkAck);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = transId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

uint32_t pnAuthClient::sendGetPublicAgeList(const ST::string& filename)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_GetPublicAgeList);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = NCCopyString(filename);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnAuthClient::sendSetAgePublic(uint32_t ageInfoId, uint8_t isPublic)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_SetAgePublic);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = ageInfoId;
    msg[1].fUint = isPublic;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendLogPythonTraceback(const ST::string& traceback)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_LogPythonTraceback);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fString = NCCopyString(traceback);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::sendLogStackDump(const ST::string& stackdump)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_LogStackDump);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fString = NCCopyString(stackdump);
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

uint32_t pnAuthClient::sendScoreCreate(uint32_t owner, const ST::string& gameName,
            uint32_t gameType, uint32_t scoreValue)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreCreate);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = owner;
    msg[2].fString = NCCopyString(gameName);
    msg[3].fUint = gameType;
    msg[4].fUint = scoreValue;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreDelete(uint32_t scoreId)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreDelete);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreGetScores(uint32_t owner, const ST::string& gameName)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreGetScores);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = owner;
    msg[2].fString = NCCopyString(gameName);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreAddPoints(uint32_t scoreId, uint32_t points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreAddPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    msg[2].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreTransferPoints(uint32_t source, uint32_t dest, uint32_t points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreTransferPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = source;
    msg[2].fUint = dest;
    msg[3].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreSetPoints(uint32_t scoreId, uint32_t points)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreSetPoints);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = scoreId;
    msg[2].fUint = points;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnAuthClient::sendScoreGetRanks(uint32_t ownerId, uint32_t group, uint32_t parent,
                const ST::string& gameName, uint32_t timePeriod, uint32_t numResults,
                uint32_t pageNumber, uint32_t sortDesc)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_ScoreGetRanks);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = ownerId;
    msg[2].fUint = group;
    msg[3].fUint = parent;
    msg[4].fString = NCCopyString(gameName);
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
    msg[0].fUint = pCre->ClassIndex(PlasmaVer::pvMoul);
    hsRAMStream rs(PlasmaVer::pvMoul);
    {
        std::lock_guard<plResManager> resMgrLock(*fResMgr);
        fResMgr->WriteCreatable(&rs, pCre);
    }
    msg[1].fUint = rs.size();
    msg[2].fData = new uint8_t[msg[1].fUint];
    rs.copyTo(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnAuthClient::onPingReply(uint32_t transId, uint32_t pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PingReply");
}

void pnAuthClient::onServerAddr(uint32_t address, const plUuid& token)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ServerAddr");
}

void pnAuthClient::onNotifyNewBuild(uint32_t buildId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_NotifyNewBuild");
}

void pnAuthClient::onClientRegisterReply(uint32_t serverChallenge)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ClientRegisterReply");
}

void pnAuthClient::onAcctExistsReply(uint32_t transId, ENetError result, bool exists)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctExistsReply");
}

void pnAuthClient::onAcctLoginReply(uint32_t transId, ENetError result,
                        const plUuid& acctUuid, uint32_t acctFlags,
                        uint32_t billingType, const uint32_t* encryptionKey)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctLoginReply");
}

void pnAuthClient::onAcctPlayerInfo(uint32_t transId, uint32_t playerId,
                        const ST::string& playerName, const ST::string& avatarModel,
                        uint32_t explorer)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctPlayerInfo");
}

void pnAuthClient::onAcctSetPlayerReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetPlayerReply");
}

void pnAuthClient::onAcctCreateReply(uint32_t transId, ENetError result,
                        const plUuid& accountUuid)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctCreateReply");
}

void pnAuthClient::onAcctChangePasswordReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctChangePasswordReply");
}

void pnAuthClient::onAcctSetRolesReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetRolesReply");
}

void pnAuthClient::onAcctSetBillingTypeReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctSetBillingTypeReply");
}

void pnAuthClient::onAcctActivateReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctActivateReply");
}

void pnAuthClient::onAcctCreateFromKeyReply(uint32_t transId, ENetError result,
                        const plUuid& acctUuid, const plUuid& activationKey)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AcctCreateFromKeyReply");
}

void pnAuthClient::onPlayerCreateReply(uint32_t transId, ENetError result,
                        uint32_t playerId, uint32_t explorer,
                        const ST::string& playerName, const ST::string& avatarShape)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PlayerCreateReply");
}

void pnAuthClient::onPlayerDeleteReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PlayerDeleteReply");
}

void pnAuthClient::onUpgradeVisitorReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_UpgradeVisitorReply");
}

void pnAuthClient::onSetPlayerBanStatusReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_SetPlayerBanStatusReply");
}

void pnAuthClient::onChangePlayerNameReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ChangePlayerNameReply");
}

void pnAuthClient::onSendFriendInviteReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_SendFriendInviteReply");
}

void pnAuthClient::onVaultNodeCreated(uint32_t transId, ENetError result,
                        uint32_t nodeId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeCreated");
}

void pnAuthClient::onVaultNodeFetched(uint32_t transId, ENetError result,
                        const pnVaultNode& node)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeFetched");
}

void pnAuthClient::onVaultNodeChanged(uint32_t nodeId, const plUuid& revisionId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeChanged");
}

void pnAuthClient::onVaultNodeDeleted(uint32_t nodeId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeDeleted");
}

void pnAuthClient::onVaultNodeAdded(uint32_t parent, uint32_t child, uint32_t owner)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeAdded");
}

void pnAuthClient::onVaultNodeRemoved(uint32_t parent, uint32_t child)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeRemoved");
}

void pnAuthClient::onVaultNodeRefsFetched(uint32_t transId, ENetError result,
                        size_t count, const pnVaultNodeRef* refs)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeRefsFetched");
}

void pnAuthClient::onVaultInitAgeReply(uint32_t transId, ENetError result,
                        uint32_t ageId, uint32_t ageInfoId)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultInitAgeReply");
}

void pnAuthClient::onVaultNodeFindReply(uint32_t transId, ENetError result,
                        size_t count, const uint32_t* nodes)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultNodeFindReply");
}

void pnAuthClient::onVaultSaveNodeReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultSaveNodeReply");
}

void pnAuthClient::onVaultAddNodeReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultAddNodeReply");
}

void pnAuthClient::onVaultRemoveNodeReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_VaultRemoveNodeReply");
}

void pnAuthClient::onAgeReply(uint32_t transId, ENetError result, uint32_t mcpId,
                        const plUuid& ageInstanceId, uint32_t ageVaultId,
                        uint32_t gameServerAddress)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AgeReply");
}

void pnAuthClient::onAgeReplyEx(uint32_t transId, ENetError result, uint32_t mcpId,
                        const plUuid& ageInstanceId, uint32_t ageVaultId,
                        const ST::string& gameServerAddress)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_AgeReplyEx");
}

void pnAuthClient::onFileListReply(uint32_t transId, ENetError result,
                        size_t count, const pnAuthFileItem* files)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_FileListReply");
}

void pnAuthClient::onFileDownloadChunk(uint32_t transId, ENetError result,
                        uint32_t totalSize, uint32_t chunkOffset, size_t chunkSize,
                        const unsigned char* chunkData)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_FileDownloadChunk");
}

void pnAuthClient::onKickedOff(uint32_t reason)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_KickedOff");
}

void pnAuthClient::onPublicAgeList(uint32_t transId, ENetError result,
                        size_t count, const pnNetAgeInfo* ages)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PublicAgeList");
}

void pnAuthClient::onScoreCreateReply(uint32_t transId, ENetError result,
                        uint32_t scoreId, uint32_t createdTime)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreCreateReply");
}

void pnAuthClient::onScoreDeleteReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreDeleteReply");
}

void pnAuthClient::onScoreGetScoresReply(uint32_t transId, ENetError result,
                        size_t count, const pnNetGameScore* scores)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreGetScoresReply");
}

void pnAuthClient::onScoreAddPointsReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreAddPointsReply");
}

void pnAuthClient::onScoreTransferPointsReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreTransferPointsReply");
}

void pnAuthClient::onScoreSetPointsReply(uint32_t transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreSetPointsReply");
}

void pnAuthClient::onScoreGetRanksReply(uint32_t transId, ENetError result,
                        size_t count, const pnNetGameRank* ranks)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_ScoreGetRanksReply");
}

void pnAuthClient::onPropagateMessage(plCreatable* msg)
{
    plDebug::Warning("Warning: Ignoring Auth2Cli_PropagateBuffer");
}
