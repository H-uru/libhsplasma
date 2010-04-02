#include "plNetGameServerState.h"
#include "Util/plZlib.h"
#include "Stream/hsRAMStream.h"

/* plNetServerSessionInfo */
plNetServerSessionInfo::plNetServerSessionInfo()
                      : fServerType(0), fServerPort(0) { }

void plNetServerSessionInfo::read(hsStream* S) {
    fContents = S->readByte();
    if (fContents & kHasServerName) {
        unsigned short len = S->readShort();
        fServerName = S->readStr(len);
    }
    if (fContents & kHasServerType)
        fServerType = S->readByte();
    if (fContents & kHasServerAddr) {
        unsigned short len = S->readShort();
        fServerAddr = S->readStr(len);
    }
    if (fContents & kHasServerPort)
        fServerPort = S->readShort();
    if (fContents & kHasServerGuid)
        fServerGuid.read(S);
}

void plNetServerSessionInfo::write(hsStream* S) {
    S->writeByte(fContents);
    if (fContents & kHasServerName) {
        S->writeShort(fServerName.len());
        S->writeStr(fServerName);
    }
    if (fContents & kHasServerType)
        S->writeByte(fServerType);
    if (fContents & kHasServerAddr) {
        S->writeShort(fServerAddr.len());
        S->writeStr(fServerAddr);
    }
    if (fContents & kHasServerPort)
        S->writeShort(fServerPort);
    if (fContents & kHasServerGuid)
        fServerGuid.write(S);
}

void plNetServerSessionInfo::setServerName(const plString& name) {
    fContents |= kHasServerName;
    fServerName = name;
}

void plNetServerSessionInfo::setServerAddr(const plString& addr) {
    fContents |= kHasServerAddr;
    fServerAddr = addr;
}

void plNetServerSessionInfo::setServerType(unsigned char type) {
    fContents |= kHasServerType;
    fServerType = type;
}

void plNetServerSessionInfo::setServerPort(unsigned short port) {
    fContents |= kHasServerPort;
    fServerPort = port;
}

void plNetServerSessionInfo::setServerGuid(const plUuid& guid) {
    fContents |= kHasServerGuid;
    fServerGuid = guid;
}

void plNetServerSessionInfo::clearServerName() {
    fContents &= ~kHasServerName;
}

void plNetServerSessionInfo::clearServerAddr() {
    fContents &= ~kHasServerAddr;
}

void plNetServerSessionInfo::clearServerType() {
    fContents &= ~kHasServerType;
}

void plNetServerSessionInfo::clearServerPort() {
    fContents &= ~kHasServerPort;
}

void plNetServerSessionInfo::clearServerGuid() {
    fContents &= ~kHasServerGuid;
}


/* plNetGameServerState */
plNetGameServerState::plNetGameServerState()
                    : fFlags(kCompressed), fMajorVer(1), fMinorVer(1) { }

plNetGameServerState::~plNetGameServerState() {
    for (size_t i=0; i<fRecords.getSize(); i++)
        delete fRecords[i];
}

void plNetGameServerState::read(hsStream* S) {
    fFlags = S->readInt();
    fMajorVer = S->readShort();
    fMinorVer = S->readShort();
    fSession.read(S);

    unsigned int uncompLen = S->readInt();
    unsigned int compLen = S->readInt();
    unsigned char* cbuf = new unsigned char[compLen];
    S->read(compLen, cbuf);
    unsigned char* ubuf = new unsigned char[uncompLen];
    plZlib::Uncompress(ubuf, uncompLen, cbuf, compLen);

    hsRAMStream data(S->getVer());
    data.copyFrom(ubuf, uncompLen);
    delete[] cbuf;
    delete[] ubuf;

    if (data.size() == 0)  // Check if there's actually any data
        return;

    fSDLMgr.read(&data);
    fRecords.setSize(data.readInt());
    fObjects.setSize(fRecords.getSize());
    for (size_t i=0; i<fRecords.getSize(); i++) {
        fRecords[i] = new plStateDataRecord();
        plString descName;
        int descVer;
        plStateDataRecord::ReadStreamHeader(&data, descName, descVer, &fObjects[i]);
        fRecords[i]->setDescriptor(fSDLMgr.GetDescriptor(descName, descVer));
        fRecords[i]->read(&data, NULL);
    }
}

void plNetGameServerState::write(hsStream* S) {
    S->writeInt(fFlags);
    S->writeShort(fMajorVer);
    S->writeShort(fMinorVer);
    fSession.write(S);

    hsRAMStream data(S->getVer());
    fSDLMgr.write(&data);
    data.writeInt(fRecords.getSize());
    for (size_t i=0; i<fRecords.getSize(); i++) {
        plStateDataRecord::WriteStreamHeader(&data, fRecords[i]->getDescriptor()->getName(),
                                             fRecords[i]->getDescriptor()->getVersion(), &fObjects[i]);
        fRecords[i]->write(&data, NULL);
    }

    unsigned int uncompLen = data.size();
    unsigned char* ubuf = new unsigned char[uncompLen];
    unsigned int compLen;
    unsigned char* cbuf;
    data.copyTo(ubuf, uncompLen);
    plZlib::Compress(cbuf, compLen, ubuf, uncompLen);

    S->writeInt(uncompLen);
    S->writeInt(compLen);
    S->write(compLen, cbuf);
    delete[] cbuf;
    delete[] ubuf;
}

void plNetGameServerState::addRecord(plStateDataRecord* rec, const plUoid& obj) {
    fRecords.append(rec);
    fObjects.append(obj);
}

void plNetGameServerState::delRecord(size_t idx) {
    delete fRecords[idx];
    fRecords.remove(idx);
    fObjects.remove(idx);
}

void plNetGameServerState::clearRecords() {
    for (size_t i=0; i<fRecords.getSize(); i++)
        delete fRecords[i];
    fRecords.setSize(0);
}
