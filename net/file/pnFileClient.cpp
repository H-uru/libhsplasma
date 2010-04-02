#include "pnFileClient.h"
#include "FileMessages.h"
#include "Debug/plDebug.h"

struct FileMsg_Header {
    hsUint32 fMsgSize;
    hsUint32 fMsgId;
};


/* pnFileManifest */
const NCchar_t* pnFileManifest::read(const NCchar_t* src)
{
    fFilename = NCstrToString(src);
    src += (NCstrlen(src) + 1);

    fDownloadName = NCstrToString(src);
    src += (NCstrlen(src) + 1);

    fHash.fromHex(NCstrToString(src));
    src += 33;

    fCompressedHash.fromHex(NCstrToString(src));
    src += 33;

    fFileSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fCompressedSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fFlags = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    return src;
}

NCchar_t* pnFileManifest::write(NCchar_t* dest)
{
    NCchar_t* strbuf = StringToNCstr(fFilename);
    size_t len = NCstrlen(strbuf);
    memcpy(dest, strbuf, len * sizeof(NCchar_t));
    dest[len] = 0;
    dest += (len + 1);
    delete[] strbuf;

    strbuf = StringToNCstr(fDownloadName);
    len = NCstrlen(strbuf);
    memcpy(dest, strbuf, len * sizeof(NCchar_t));
    dest[len] = 0;
    dest += (len + 1);
    delete[] strbuf;

    strbuf = StringToNCstr(fHash.toHex());
    memcpy(dest, strbuf, 32 * sizeof(NCchar_t));
    dest[32] = 0;
    dest += 33;
    delete[] strbuf;

    strbuf = StringToNCstr(fCompressedHash.toHex());
    memcpy(dest, strbuf, 32 * sizeof(NCchar_t));
    dest[32] = 0;
    dest += 33;
    delete[] strbuf;

    dest[0] = (NCchar_t)(fFileSize >> 16);
    dest[1] = (NCchar_t)(fFileSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (NCchar_t)(fCompressedSize >> 16);
    dest[1] = (NCchar_t)(fCompressedSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (NCchar_t)(fFlags >> 16);
    dest[1] = (NCchar_t)(fFlags & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    return dest;
}

size_t pnFileManifest::calcSize() const
{
    size_t result = 75;     // 2 MD5 hashes, 3 uint32s, and \0 pads for each

    NCchar_t* strbuf = StringToNCstr(fFilename);
    result += NCstrlen(strbuf) + 1;
    delete[] strbuf;

    strbuf = StringToNCstr(fDownloadName);
    result += NCstrlen(strbuf) + 1;
    delete[] strbuf;

    return result;
}


/* Dispatch */
pnFileClient::Dispatch::Dispatch(pnAsyncSocket* sock, pnFileClient* self)
            : fReceiver(self), fSock(sock)
{ }

void pnFileClient::Dispatch::run()
{
    FileMsg_Header header;
    while (fSock->isConnected()) {
        if (!fSock->waitForData()) {
            // Got an error
            break;
        }

        fSock->recv(&header.fMsgSize, sizeof(header.fMsgSize));
        fSock->recv(&header.fMsgId, sizeof(header.fMsgId));
        hsUbyte* msgbuf = new hsUbyte[header.fMsgSize - 8];
        fSock->recv(msgbuf, header.fMsgSize - 8);

        switch (header.fMsgId) {
        case kFile2Cli_PingReply:
            fReceiver->onPingReply(*(hsUint32*)(msgbuf));
            break;
        case kFile2Cli_BuildIdReply:
            fReceiver->onBuildIdReply(*(hsUint32*)(msgbuf    ),
                          (ENetError)(*(hsUint32*)(msgbuf + 4)),
                                      *(hsUint32*)(msgbuf + 8));
            break;
        case kFile2Cli_BuildIdUpdate:
            fReceiver->onBuildIdUpdate(*(hsUint32*)(msgbuf));
            break;
        case kFile2Cli_ManifestReply:
            {
                pnFileManifest* files;
                size_t i = 0;
                hsUint32 transId  = *(hsUint32*)(msgbuf     );
                hsUint32 readerId = *(hsUint32*)(msgbuf +  8);
                size_t totalFiles = *(hsUint32*)(msgbuf + 12);
                if (fMfsOffset.find(transId) != fMfsOffset.end()) {
                    files = fMfsQueue[transId];
                    i = fMfsOffset[transId];
                } else {
                    files = new pnFileManifest[totalFiles];
                }
                const NCchar_t* bufp = (NCchar_t*)(msgbuf + 20);
                for (; i<totalFiles; i++) {
                    if (*bufp == 0) {
                        fMfsQueue[transId] = files;
                        fMfsOffset[transId] = i;
                        break;
                    }
                    bufp = files[i].read(bufp);
                }
                fReceiver->sendManifestEntryAck(transId, readerId);
                if (i < totalFiles)
                    break;
                fReceiver->onManifestReply(*(hsUint32*)(msgbuf     ),
                               (ENetError)(*(hsUint32*)(msgbuf +  4)),
                                           *(hsUint32*)(msgbuf +  8),
                                           totalFiles, files);
                if (fMfsOffset.find(transId) != fMfsOffset.end()) {
                    fMfsQueue.erase(fMfsQueue.find(transId));
                    fMfsOffset.erase(fMfsOffset.find(transId));
                }
                delete[] files;
            }
            break;
        case kFile2Cli_FileDownloadReply:
            fReceiver->onFileDownloadReply(*(hsUint32*)(msgbuf     ),
                               (ENetError)(*(hsUint32*)(msgbuf +  4)),
                                           *(hsUint32*)(msgbuf +  8),
                                           *(hsUint32*)(msgbuf + 12),
                                           *(hsUint32*)(msgbuf + 16),
                                            (const hsUbyte*)(msgbuf + 20));
            fReceiver->sendFileDownloadChunkAck(*(hsUint32*)(msgbuf     ),
                                                *(hsUint32*)(msgbuf +  8));
            break;
        }
        delete[] msgbuf;
        fSock->signalStatus();
    } /* while connected */
}


/* pnFileClient */
pnFileClient::pnFileClient() : fSock(NULL), fDispatch(NULL)
{ }

pnFileClient::~pnFileClient()
{
    if (fSock != NULL)
        fSock->close();
    if (fDispatch != NULL)
        delete fDispatch;
    if (fSock != NULL)
        delete fSock;
}

void pnFileClient::setClientInfo(hsUint32 buildType, hsUint32 branchId,
                                 const plUuid& productId)
{
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

ENetError pnFileClient::connect(const char* host, short port)
{
    pnSocket* sock = new pnSocket();
    if (!sock->connect(host, port)) {
        plDebug::Error("Error connecting to file server\n");
        delete sock;
        return kNetErrConnectFailed;
    }
    return performConnect(sock);
}

ENetError pnFileClient::connect(int sockFd)
{
    pnSocket* sock = new pnSocket(sockFd);
    return performConnect(sock);
}

ENetError pnFileClient::performConnect(pnSocket* sock)
{
    fSock = new pnAsyncSocket(sock);

    hsUbyte connectHeader[43];  // ConnectHeader + FileConnectHeader
    /* Begin ConnectHeader */
    *(hsUbyte* )(connectHeader     ) = kConnTypeCliToFile;
    *(hsUint16*)(connectHeader +  1) = 31;
    *(hsUint32*)(connectHeader +  3) = 0;
    *(hsUint32*)(connectHeader +  7) = fBuildType;
    *(hsUint32*)(connectHeader + 11) = fBranchId;
    fProductId.write(connectHeader + 15);
    /* Begin FileConnectHeader */
    *(hsUint32*)(connectHeader + 31) = 12;
    *(hsUint32*)(connectHeader + 35) = 0;
    *(hsUint32*)(connectHeader + 39) = 0;
    fSock->send(connectHeader, 43);

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error establishing File connection");
        return kNetErrConnectFailed;
    }

    fDispatch = new Dispatch(fSock, this);
    fDispatch->start();
    return kNetSuccess;
}

void pnFileClient::sendPingRequest(hsUint32 pingTimeMs)
{
    hsUbyte msgbuf[12];
    *(hsUint32*)(msgbuf    ) = 12;                      // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_PingRequest;   // Msg ID
    *(hsUint32*)(msgbuf + 8) = pingTimeMs;              // Ping time
    fSock->send(msgbuf, 12);
}

hsUint32 pnFileClient::sendBuildIdRequest()
{
    hsUint32 transId = nextTransId();
    hsUbyte msgbuf[12];
    *(hsUint32*)(msgbuf    ) = 12;                          // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_BuildIdRequest;    // Msg ID
    *(hsUint32*)(msgbuf + 8) = transId;                     // Trans ID
    fSock->send(msgbuf, 12);
    return transId;
}

hsUint32 pnFileClient::sendManifestRequest(const plString& group, hsUint32 buildId)
{
    NCchar_t* wgroup = StringToNCstr(group);
    size_t wgroup_len = NCstrlen(wgroup) + 1;

    hsUint32 transId = nextTransId();
    hsUbyte msgbuf[536];
    *(hsUint32*)(msgbuf    ) = 536;                         // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_ManifestRequest;   // Msg ID
    *(hsUint32*)(msgbuf + 8) = transId;                     // Trans ID
    memcpy(msgbuf + 12, wgroup, (wgroup_len >= 260 ? 259 : wgroup_len) * sizeof(NCchar_t));
    *(NCchar_t*)(msgbuf + 530) = 0;                         // Nul terminator
    *(hsUint32*)(msgbuf + 532) = buildId;                   // Build ID
    fSock->send(msgbuf, 536);
    delete[] wgroup;
    return transId;
}

hsUint32 pnFileClient::sendFileDownloadRequest(const plString& filename, hsUint32 buildId)
{
    NCchar_t* wfilename = StringToNCstr(filename);
    size_t wfilename_len = NCstrlen(wfilename) + 1;

    hsUint32 transId = nextTransId();
    hsUbyte msgbuf[536];
    *(hsUint32*)(msgbuf    ) = 536;                             // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_FileDownloadRequest;   // Msg ID
    *(hsUint32*)(msgbuf + 8) = transId;                         // Trans ID
    memcpy(msgbuf + 12, wfilename, (wfilename_len >= 260 ? 259 : wfilename_len) * sizeof(NCchar_t));
    *(NCchar_t*)(msgbuf + 530) = 0;                             // Nul terminator
    *(hsUint32*)(msgbuf + 532) = buildId;                       // Build ID
    fSock->send(msgbuf, 536);
    delete[] wfilename;
    return transId;
}

void pnFileClient::sendManifestEntryAck(hsUint32 transId, hsUint32 readerId)
{
    hsUbyte msgbuf[16];
    *(hsUint32*)(msgbuf     ) = 16;                         // Msg size
    *(hsUint32*)(msgbuf +  4) = kCli2File_ManifestEntryAck; // Msg ID
    *(hsUint32*)(msgbuf +  8) = transId;                    // Trans ID
    *(hsUint32*)(msgbuf + 12) = readerId;                   // Reader ID
    fSock->send(msgbuf, 16);
}

void pnFileClient::sendFileDownloadChunkAck(hsUint32 transId, hsUint32 readerId)
{
    hsUbyte msgbuf[16];
    *(hsUint32*)(msgbuf     ) = 16;                             // Msg size
    *(hsUint32*)(msgbuf +  4) = kCli2File_FileDownloadChunkAck; // Msg ID
    *(hsUint32*)(msgbuf +  8) = transId;                        // Trans ID
    *(hsUint32*)(msgbuf + 12) = readerId;                       // Reader ID
    fSock->send(msgbuf, 16);
}

void pnFileClient::onPingReply(hsUint32 pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring File2Cli_PingReply");
}

void pnFileClient::onBuildIdReply(hsUint32 transId, ENetError result, hsUint32 buildId)
{
    plDebug::Warning("Warning: Ignoring File2Cli_BuildIdReply");
}

void pnFileClient::onBuildIdUpdate(hsUint32 buildId)
{
    plDebug::Warning("Warning: Ignoring File2Cli_BuildIdUpdate");
}

void pnFileClient::onManifestReply(hsUint32 transId, ENetError result,
            hsUint32 readerId, size_t numFiles, const pnFileManifest* files)
{
    plDebug::Warning("Warning: Ignoring File2Cli_ManifestReply");
}

void pnFileClient::onFileDownloadReply(hsUint32 transId, ENetError result,
            hsUint32 readerId, hsUint32 totalSize, size_t bufferSize,
            const hsUbyte* bufferData)
{
    plDebug::Warning("Warning: Ignoring File2Cli_FileDownloadReply");
}
