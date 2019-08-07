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
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include <cstring>

struct FileMsg_Header
{
    uint32_t fMsgSize;
    uint32_t fMsgId;
};


/* pnFileManifest */
const char16_t* pnFileManifest::read(const char16_t* src)
{
    size_t len = ST::utf16_buffer::strlen(src);
    fFilename = ST::string::from_utf16(src, len);
    src += (len + 1);

    len = ST::utf16_buffer::strlen(src);
    fDownloadName = ST::string::from_utf16(src, len);
    src += (len + 1);

    fHash.fromHex(ST::string::from_utf16(src).c_str());
    src += 33;

    fCompressedHash.fromHex(ST::string::from_utf16(src).c_str());
    src += 33;

    fFileSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fCompressedSize = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    fFlags = (src[0] << 16) | (src[1] & 0xFFFF);
    src += 3;

    return src;
}

char16_t* pnFileManifest::write(char16_t* dest)
{
    ST::utf16_buffer wsbuf = fFilename.to_utf16();
    memcpy(dest, wsbuf.data(), wsbuf.size() * sizeof(char16_t));
    dest[wsbuf.size()] = 0;
    dest += (wsbuf.size() + 1);

    wsbuf = fDownloadName.to_utf16();
    memcpy(dest, wsbuf.data(), wsbuf.size() * sizeof(char16_t));
    dest[wsbuf.size()] = 0;
    dest += (wsbuf.size() + 1);

    wsbuf = fHash.toHex().to_utf16();
    memcpy(dest, wsbuf.data(), 32 * sizeof(char16_t));
    dest[32] = 0;
    dest += 33;

    wsbuf = fCompressedHash.toHex().to_utf16();
    memcpy(dest, wsbuf.data(), 32 * sizeof(char16_t));
    dest[32] = 0;
    dest += 33;

    dest[0] = (char16_t)(fFileSize >> 16);
    dest[1] = (char16_t)(fFileSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (char16_t)(fCompressedSize >> 16);
    dest[1] = (char16_t)(fCompressedSize & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    dest[0] = (char16_t)(fFlags >> 16);
    dest[1] = (char16_t)(fFlags & 0xFFFF);
    dest[2] = 0;
    dest += 3;

    return dest;
}

size_t pnFileManifest::calcSize() const
{
    // 2 MD5 hashes, 3 uint32s, 2 pl_wchar strings, and \0 pads for each
    return 77 + fFilename.to_utf16().size() + fDownloadName.to_utf16().size();
}


/* Dispatch */
bool pnFileClient::Dispatch::dispatch(pnSocket* sock)
{
    FileMsg_Header header;

    sock->recv(&header.fMsgSize, sizeof(header.fMsgSize));
    sock->recv(&header.fMsgId, sizeof(header.fMsgId));
    uint8_t* msgbuf = new uint8_t[header.fMsgSize - 8];
    uint32_t read_data = 0;
    while (read_data < header.fMsgSize - 8)
        read_data += sock->recv(msgbuf, header.fMsgSize - 8 - read_data);

    switch (header.fMsgId) {
    case kFile2Cli_PingReply:
        fReceiver->onPingReply(*(uint32_t*)(msgbuf));
        break;
    case kFile2Cli_BuildIdReply:
        fReceiver->onBuildIdReply(*(uint32_t*)(msgbuf    ),
                      (ENetError)(*(uint32_t*)(msgbuf + 4)),
                                  *(uint32_t*)(msgbuf + 8));
        break;
    case kFile2Cli_BuildIdUpdate:
        fReceiver->onBuildIdUpdate(*(uint32_t*)(msgbuf));
        break;
    case kFile2Cli_ManifestReply:
        {
            pnFileManifest* files;
            size_t i = 0;
            uint32_t transId  = *(uint32_t*)(msgbuf     );
            uint32_t readerId = *(uint32_t*)(msgbuf +  8);
            size_t totalFiles = *(uint32_t*)(msgbuf + 12);
            if (fMfsOffset.find(transId) != fMfsOffset.end()) {
                files = fMfsQueue[transId];
                i = fMfsOffset[transId];
            } else {
                files = new pnFileManifest[totalFiles];
            }
            const char16_t* bufp = (char16_t*)(msgbuf + 20);
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
            fReceiver->onManifestReply(*(uint32_t*)(msgbuf     ),
                            (ENetError)(*(uint32_t*)(msgbuf +  4)),
                                        *(uint32_t*)(msgbuf +  8),
                                        totalFiles, files);
            if (fMfsOffset.find(transId) != fMfsOffset.end()) {
                fMfsQueue.erase(fMfsQueue.find(transId));
                fMfsOffset.erase(fMfsOffset.find(transId));
            }
            delete[] files;
        }
        break;
    case kFile2Cli_FileDownloadReply:
        fReceiver->onFileDownloadReply(*(uint32_t*)(msgbuf     ),
                            (ENetError)(*(uint32_t*)(msgbuf +  4)),
                                        *(uint32_t*)(msgbuf +  8),
                                        *(uint32_t*)(msgbuf + 12),
                                        *(uint32_t*)(msgbuf + 16),
                                        (const uint8_t*)(msgbuf + 20));
        fReceiver->sendFileDownloadChunkAck(*(uint32_t*)(msgbuf     ),
                                            *(uint32_t*)(msgbuf +  8));
        break;
    }
    delete[] msgbuf;
    return true;
}


/* pnFileClient */
pnFileClient::~pnFileClient()
{
    delete fIface;
    delete fDispatch;
    delete fSock;
}

void pnFileClient::setClientInfo(uint32_t buildType, uint32_t branchId,
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
    delete fIface;
    delete fDispatch;
    delete fSock;
    fIface = nullptr;
    fSock = nullptr;
    fDispatch = nullptr;
}

ENetError pnFileClient::performConnect()
{
    hsRAMStream connectHeader;
    /* Begin ConnectHeader */
    connectHeader.writeByte(kConnTypeCliToFile);
    connectHeader.writeShort(31);
    connectHeader.writeInt(0);
    connectHeader.writeInt(fBuildType);
    connectHeader.writeInt(fBranchId);
    fProductId.write(&connectHeader);
    /* Begin FileConnectHeader */
    connectHeader.writeInt(12);
    connectHeader.writeInt(0);
    connectHeader.writeInt(0);
    fSock->send(connectHeader.data(), connectHeader.size());

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = nullptr;
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

void pnFileClient::sendPingRequest(uint32_t pingTimeMs)
{
    uint8_t msgbuf[12];
    *(uint32_t*)(msgbuf    ) = 12;                      // Msg size
    *(uint32_t*)(msgbuf + 4) = kCli2File_PingRequest;   // Msg ID
    *(uint32_t*)(msgbuf + 8) = pingTimeMs;              // Ping time
    fSock->send(msgbuf, 12);
}

uint32_t pnFileClient::sendBuildIdRequest()
{
    uint32_t transId = nextTransId();
    uint8_t msgbuf[12];
    *(uint32_t*)(msgbuf    ) = 12;                          // Msg size
    *(uint32_t*)(msgbuf + 4) = kCli2File_BuildIdRequest;    // Msg ID
    *(uint32_t*)(msgbuf + 8) = transId;                     // Trans ID
    fSock->send(msgbuf, 12);
    return transId;
}

uint32_t pnFileClient::sendManifestRequest(const ST::string& group, uint32_t buildId)
{
    ST::utf16_buffer wgroup = group.to_utf16();
    size_t len = wgroup.size() + 1;

    uint32_t transId = nextTransId();
    uint8_t msgbuf[536];
    *(uint32_t*)(msgbuf    ) = 536;                         // Msg size
    *(uint32_t*)(msgbuf + 4) = kCli2File_ManifestRequest;   // Msg ID
    *(uint32_t*)(msgbuf + 8) = transId;                     // Trans ID
    memcpy(msgbuf + 12, wgroup.data(), (len >= 260 ? 259 : len) * sizeof(char16_t));
    *(char16_t*)(msgbuf + 530) = 0;                         // Nul terminator
    *(uint32_t*)(msgbuf + 532) = buildId;                   // Build ID
    fSock->send(msgbuf, 536);
    return transId;
}

uint32_t pnFileClient::sendFileDownloadRequest(const ST::string& filename, uint32_t buildId)
{
    ST::utf16_buffer wfilename = filename.to_utf16();
    size_t len = wfilename.size() + 1;

    uint32_t transId = nextTransId();
    uint8_t msgbuf[536];
    *(uint32_t*)(msgbuf    ) = 536;                             // Msg size
    *(uint32_t*)(msgbuf + 4) = kCli2File_FileDownloadRequest;   // Msg ID
    *(uint32_t*)(msgbuf + 8) = transId;                         // Trans ID
    memcpy(msgbuf + 12, wfilename.data(), (len >= 260 ? 259 : len) * sizeof(char16_t));
    *(char16_t*)(msgbuf + 530) = 0;                             // Nul terminator
    *(uint32_t*)(msgbuf + 532) = buildId;                       // Build ID
    fSock->send(msgbuf, 536);
    return transId;
}

void pnFileClient::sendManifestEntryAck(uint32_t transId, uint32_t readerId)
{
    uint8_t msgbuf[16];
    *(uint32_t*)(msgbuf     ) = 16;                         // Msg size
    *(uint32_t*)(msgbuf +  4) = kCli2File_ManifestEntryAck; // Msg ID
    *(uint32_t*)(msgbuf +  8) = transId;                    // Trans ID
    *(uint32_t*)(msgbuf + 12) = readerId;                   // Reader ID
    fSock->send(msgbuf, 16);
}

void pnFileClient::sendFileDownloadChunkAck(uint32_t transId, uint32_t readerId)
{
    uint8_t msgbuf[16];
    *(uint32_t*)(msgbuf     ) = 16;                             // Msg size
    *(uint32_t*)(msgbuf +  4) = kCli2File_FileDownloadChunkAck; // Msg ID
    *(uint32_t*)(msgbuf +  8) = transId;                        // Trans ID
    *(uint32_t*)(msgbuf + 12) = readerId;                       // Reader ID
    fSock->send(msgbuf, 16);
}

void pnFileClient::onPingReply(uint32_t pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring File2Cli_PingReply");
}

void pnFileClient::onBuildIdReply(uint32_t transId, ENetError result, uint32_t buildId)
{
    plDebug::Warning("Warning: Ignoring File2Cli_BuildIdReply");
}

void pnFileClient::onBuildIdUpdate(uint32_t buildId)
{
    plDebug::Warning("Warning: Ignoring File2Cli_BuildIdUpdate");
}

void pnFileClient::onManifestReply(uint32_t transId, ENetError result,
            uint32_t readerId, size_t numFiles, const pnFileManifest* files)
{
    plDebug::Warning("Warning: Ignoring File2Cli_ManifestReply");
}

void pnFileClient::onFileDownloadReply(uint32_t transId, ENetError result,
            uint32_t readerId, uint32_t totalSize, size_t bufferSize,
            const uint8_t* bufferData)
{
    plDebug::Warning("Warning: Ignoring File2Cli_FileDownloadReply");
}
