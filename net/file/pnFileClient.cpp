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

#include "pnFileClient.h"
#include "FileMessages.h"
#include "Debug/plDebug.h"

struct FileMsg_Header {
    hsUint32 fMsgSize;
    hsUint32 fMsgId;
};


/* pnFileManifest */
const pl_wchar_t* pnFileManifest::read(const pl_wchar_t* src)
{
    size_t len = plwcslen(src);
    fFilename = plString(src, len);
    src += (len + 1);

    len = plwcslen(src);
    fDownloadName = plString(src, len);
    src += (len + 1);

    fHash.fromHex(plString(src).cstr());
    src += 33;

    fCompressedHash.fromHex(plString(src).cstr());
    src += 33;

    fFileSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fCompressedSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fFlags = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    return src;
}

pl_wchar_t* pnFileManifest::write(pl_wchar_t* dest)
{
    plString::Wide wsbuf = fFilename.wstr();
    memcpy(dest, wsbuf.data(), wsbuf.len() * sizeof(pl_wchar_t));
    dest[wsbuf.len()] = 0;
    dest += (wsbuf.len() + 1);

    wsbuf = fDownloadName.wstr();
    memcpy(dest, wsbuf.data(), wsbuf.len() * sizeof(pl_wchar_t));
    dest[wsbuf.len()] = 0;
    dest += (wsbuf.len() + 1);

    wsbuf = fHash.toHex().wstr();
    memcpy(dest, wsbuf.data(), 32 * sizeof(pl_wchar_t));
    dest[32] = 0;
    dest += 33;

    wsbuf = fCompressedHash.toHex().wstr();
    memcpy(dest, wsbuf.data(), 32 * sizeof(pl_wchar_t));
    dest[32] = 0;
    dest += 33;

    dest[0] = (pl_wchar_t)(fFileSize >> 16);
    dest[1] = (pl_wchar_t)(fFileSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (pl_wchar_t)(fCompressedSize >> 16);
    dest[1] = (pl_wchar_t)(fCompressedSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (pl_wchar_t)(fFlags >> 16);
    dest[1] = (pl_wchar_t)(fFlags & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    return dest;
}

size_t pnFileManifest::calcSize() const
{
    // 2 MD5 hashes, 3 uint32s, 2 pl_wchar strings, and \0 pads for each
    return 77 + fFilename.wstr().len() + fDownloadName.wstr().len();
}


/* Dispatch */
pnFileClient::Dispatch::Dispatch(pnFileClient* self)
            : fReceiver(self)
{ }

pnFileClient::Dispatch::~Dispatch()
{ }


bool pnFileClient::Dispatch::dispatch(pnSocket* sock)
{
    FileMsg_Header header;

    sock->recv(&header.fMsgSize, sizeof(header.fMsgSize));
    sock->recv(&header.fMsgId, sizeof(header.fMsgId));
    hsUbyte* msgbuf = new hsUbyte[header.fMsgSize - 8];
    hsUint32 read_data = 0;
    while (read_data < header.fMsgSize - 8)
        read_data += sock->recv(msgbuf, header.fMsgSize - 8 - read_data);

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
            const pl_wchar_t* bufp = (pl_wchar_t*)(msgbuf + 20);
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
    return true;
}


/* pnFileClient */
pnFileClient::pnFileClient(bool threaded) : fSock(NULL), fThreaded(threaded), fDispatch(NULL)
{ }

pnFileClient::~pnFileClient()
{
    if (fSock != NULL)
        fSock->close();
    delete fIface;
    delete fDispatch;
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
    fSock = new pnSocket();
    if (!fSock->connect(host, port)) {
        plDebug::Error("Error connecting to file server\n");
        delete fSock;
        return kNetErrConnectFailed;
    }
    return performConnect();
}

ENetError pnFileClient::connect(int sockFd)
{
    fSock = new pnSocket(sockFd);
    return performConnect();
}

void pnFileClient::disconnect()
{
    if (fSock != NULL)
        fSock->close();
    delete fIface;
    delete fDispatch;
    delete fSock;
    fIface = NULL;
    fSock = NULL;
    fDispatch = NULL;
}

ENetError pnFileClient::performConnect()
{
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

    fDispatch = new Dispatch(this);
    if (fThreaded)
        fIface = new pnThreadedSocket(fDispatch, fSock);
    else
        fIface = new pnPolledSocket(fDispatch, fSock);
    fIface->run();
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
    plString::Wide wgroup = group.wstr();
    size_t len = wgroup.len() + 1;

    hsUint32 transId = nextTransId();
    hsUbyte msgbuf[536];
    *(hsUint32*)(msgbuf    ) = 536;                         // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_ManifestRequest;   // Msg ID
    *(hsUint32*)(msgbuf + 8) = transId;                     // Trans ID
    memcpy(msgbuf + 12, wgroup.data(), (len >= 260 ? 259 : len) * sizeof(pl_wchar_t));
    *(pl_wchar_t*)(msgbuf + 530) = 0;                       // Nul terminator
    *(hsUint32*)(msgbuf + 532) = buildId;                   // Build ID
    fSock->send(msgbuf, 536);
    return transId;
}

hsUint32 pnFileClient::sendFileDownloadRequest(const plString& filename, hsUint32 buildId)
{
    plString::Wide wfilename = filename.wstr();
    size_t len = wfilename.len() + 1;

    hsUint32 transId = nextTransId();
    hsUbyte msgbuf[536];
    *(hsUint32*)(msgbuf    ) = 536;                             // Msg size
    *(hsUint32*)(msgbuf + 4) = kCli2File_FileDownloadRequest;   // Msg ID
    *(hsUint32*)(msgbuf + 8) = transId;                         // Trans ID
    memcpy(msgbuf + 12, wfilename.data(), (len >= 260 ? 259 : len) * sizeof(pl_wchar_t));
    *(pl_wchar_t*)(msgbuf + 530) = 0;                           // Nul terminator
    *(hsUint32*)(msgbuf + 532) = buildId;                       // Build ID
    fSock->send(msgbuf, 536);
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
