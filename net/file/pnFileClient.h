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
#include "pnSocketInterface.h"

struct PLASMANET_DLL pnFileManifest {
    plString fFilename, fDownloadName;
    plMD5Hash fHash, fCompressedHash;
    uint32_t fFileSize, fCompressedSize, fFlags;

    const pl_wchar_t* read(const pl_wchar_t* src);
    pl_wchar_t* write(pl_wchar_t* dest);
    size_t calcSize() const;
};

class PLASMANET_DLL pnFileClient : public pnClient {
public:
    pnFileClient(bool threaded=true)
        : fSock(NULL), fThreaded(threaded), fDispatch(NULL) { }
    virtual ~pnFileClient();

    void setClientInfo(uint32_t buildType, uint32_t branchId, const plUuid& productId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual void disconnect();

    virtual bool isConnected() const
    { return (fSock != NULL) && fSock->isConnected(); }

//     virtual void signalStatus() { fSock->signalStatus(); }
//     virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    void sendPingRequest(uint32_t pingTimeMs);
    uint32_t sendBuildIdRequest();
    uint32_t sendManifestRequest(const plString& group, uint32_t buildId);
    uint32_t sendFileDownloadRequest(const plString& filename, uint32_t buildId);

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(uint32_t pingTimeMs);
    virtual void onBuildIdReply(uint32_t transId, ENetError result, uint32_t buildId);
    virtual void onBuildIdUpdate(uint32_t buildId);
    virtual void onManifestReply(uint32_t transId, ENetError result,
                    uint32_t readerId, size_t numFiles, const pnFileManifest* files);
    virtual void onFileDownloadReply(uint32_t transId, ENetError result,
                    uint32_t readerId, uint32_t totalSize, size_t bufferSize,
                    const uint8_t* bufferData);

protected:
    pnSocket* fSock;
    uint32_t fBuildType, fBranchId;
    plUuid fProductId;
    bool fThreaded;

private:
    class Dispatch : public pnDispatcher {
    public:
        Dispatch(pnFileClient* self) : fReceiver(self) { }
        virtual ~Dispatch() { }
        virtual bool dispatch(pnSocket* sock);

    private:
        pnFileClient* fReceiver;

    private:
        std::map<uint32_t, pnFileManifest*> fMfsQueue;
        std::map<uint32_t, size_t> fMfsOffset;
    } *fDispatch;

    ENetError performConnect();
    void sendManifestEntryAck(uint32_t transId, uint32_t readerId);
    void sendFileDownloadChunkAck(uint32_t transId, uint32_t readerId);
};

#endif
