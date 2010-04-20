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

#ifndef _PNFILECLIENT_H
#define _PNFILECLIENT_H

#include "pnClient.h"
#include "Sys/plUuid.h"
#include "Util/plMD5.h"
#include "pnSocket.h"

DllStruct pnFileManifest {
    plString fFilename, fDownloadName;
    plMD5Hash fHash, fCompressedHash;
    hsUint32 fFileSize, fCompressedSize, fFlags;

    const NCchar_t* read(const NCchar_t* src);
    NCchar_t* write(NCchar_t* dest);
    size_t calcSize() const;
};

DllClass pnFileClient : public pnClient {
public:
    pnFileClient();
    virtual ~pnFileClient();

    void setClientInfo(hsUint32 buildType, hsUint32 branchId, const plUuid& productId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual void disconnect();

    virtual bool isConnected() const
    { return (fSock != NULL) && fSock->isConnected(); }

    virtual void signalStatus() { fSock->signalStatus(); }
    virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    void sendPingRequest(hsUint32 pingTimeMs);
    hsUint32 sendBuildIdRequest();
    hsUint32 sendManifestRequest(const plString& group, hsUint32 buildId);
    hsUint32 sendFileDownloadRequest(const plString& filename, hsUint32 buildId);

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(hsUint32 pingTimeMs);
    virtual void onBuildIdReply(hsUint32 transId, ENetError result, hsUint32 buildId);
    virtual void onBuildIdUpdate(hsUint32 buildId);
    virtual void onManifestReply(hsUint32 transId, ENetError result,
                    hsUint32 readerId, size_t numFiles, const pnFileManifest* files);
    virtual void onFileDownloadReply(hsUint32 transId, ENetError result,
                    hsUint32 readerId, hsUint32 totalSize, size_t bufferSize,
                    const hsUbyte* bufferData);

protected:
    pnAsyncSocket* fSock;
    hsUint32 fBuildType, fBranchId;
    plUuid fProductId;

private:
    class Dispatch : public hsThread {
    public:
        Dispatch(pnAsyncSocket* sock, pnFileClient* self);

    private:
        virtual void run();

        pnFileClient* fReceiver;
        pnAsyncSocket* fSock;

    private:
        std::map<hsUint32, pnFileManifest*> fMfsQueue;
        std::map<hsUint32, size_t> fMfsOffset;
    } *fDispatch;

    ENetError performConnect(pnSocket* sock);
    void sendManifestEntryAck(hsUint32 transId, hsUint32 readerId);
    void sendFileDownloadChunkAck(hsUint32 transId, hsUint32 readerId);
};

#endif
