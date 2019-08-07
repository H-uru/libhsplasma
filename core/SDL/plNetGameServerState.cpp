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

#include "plNetGameServerState.h"
#include "Util/plZlib.h"
#include "Stream/hsRAMStream.h"

/* plNetServerSessionInfo */
void plNetServerSessionInfo::read(hsStream* S)
{
    fContents = S->readByte();
    if (fContents & kHasServerName) {
        uint16_t len = S->readShort();
        fServerName = S->readStr(len);
    }
    if (fContents & kHasServerType)
        fServerType = S->readByte();
    if (fContents & kHasServerAddr) {
        uint16_t len = S->readShort();
        fServerAddr = S->readStr(len);
    }
    if (fContents & kHasServerPort)
        fServerPort = S->readShort();
    if (fContents & kHasServerGuid)
        fServerGuid.read(S);
}

void plNetServerSessionInfo::write(hsStream* S)
{
    S->writeByte(fContents);
    if (fContents & kHasServerName) {
        S->writeShort(fServerName.size());
        S->writeStr(fServerName);
    }
    if (fContents & kHasServerType)
        S->writeByte(fServerType);
    if (fContents & kHasServerAddr) {
        S->writeShort(fServerAddr.size());
        S->writeStr(fServerAddr);
    }
    if (fContents & kHasServerPort)
        S->writeShort(fServerPort);
    if (fContents & kHasServerGuid)
        fServerGuid.write(S);
}

void plNetServerSessionInfo::setServerName(const ST::string& name)
{
    fContents |= kHasServerName;
    fServerName = name;
}

void plNetServerSessionInfo::setServerAddr(const ST::string& addr)
{
    fContents |= kHasServerAddr;
    fServerAddr = addr;
}

void plNetServerSessionInfo::setServerType(uint8_t type)
{
    fContents |= kHasServerType;
    fServerType = type;
}

void plNetServerSessionInfo::setServerPort(uint16_t port)
{
    fContents |= kHasServerPort;
    fServerPort = port;
}

void plNetServerSessionInfo::setServerGuid(const plUuid& guid)
{
    fContents |= kHasServerGuid;
    fServerGuid = guid;
}

void plNetServerSessionInfo::clearServerName()
{
    fContents &= ~kHasServerName;
}

void plNetServerSessionInfo::clearServerAddr()
{
    fContents &= ~kHasServerAddr;
}

void plNetServerSessionInfo::clearServerType()
{
    fContents &= ~kHasServerType;
}

void plNetServerSessionInfo::clearServerPort()
{
    fContents &= ~kHasServerPort;
}

void plNetServerSessionInfo::clearServerGuid()
{
    fContents &= ~kHasServerGuid;
}


/* plNetGameServerState */
plNetGameServerState::~plNetGameServerState()
{
    for (auto rec = fRecords.begin(); rec != fRecords.end(); ++rec)
        delete *rec;
}

void plNetGameServerState::read(hsStream* S)
{
    fFlags = S->readInt();
    fMajorVer = S->readShort();
    fMinorVer = S->readShort();
    fSession.read(S);

    size_t uncompLen = S->readInt();
    size_t compLen = S->readInt();
    uint8_t* cbuf = new uint8_t[compLen];
    S->read(compLen, cbuf);
    uint8_t* ubuf = new uint8_t[uncompLen];
    plZlib::Uncompress(ubuf, uncompLen, cbuf, compLen);
    delete[] cbuf;

    hsRAMStream data(S->getVer());
    data.stealFrom(ubuf, uncompLen);

    if (data.size() == 0)  // Check if there's actually any data
        return;

    fSDLMgr.read(&data);
    fRecords.resize(data.readInt());
    fObjects.resize(fRecords.size());
    for (size_t i=0; i<fRecords.size(); i++) {
        fRecords[i] = new plStateDataRecord();
        ST::string descName;
        int descVer;
        plStateDataRecord::ReadStreamHeader(&data, descName, descVer, &fObjects[i]);
        fRecords[i]->setDescriptor(fSDLMgr.GetDescriptor(descName, descVer));
        fRecords[i]->read(&data, nullptr);
    }
}

void plNetGameServerState::write(hsStream* S)
{
    S->writeInt(fFlags);
    S->writeShort(fMajorVer);
    S->writeShort(fMinorVer);
    fSession.write(S);

    hsRAMStream data(S->getVer());
    fSDLMgr.write(&data);
    data.writeInt(fRecords.size());
    for (size_t i=0; i<fRecords.size(); i++) {
        plStateDataRecord::WriteStreamHeader(&data, fRecords[i]->getDescriptor()->getName(),
                                             fRecords[i]->getDescriptor()->getVersion(), &fObjects[i]);
        fRecords[i]->write(&data, nullptr);
    }

    size_t uncompLen = data.size();
    uint8_t* ubuf = new uint8_t[uncompLen];
    size_t compLen;
    uint8_t* cbuf;
    data.copyTo(ubuf, uncompLen);
    plZlib::Compress(cbuf, compLen, ubuf, uncompLen);

    S->writeInt(uncompLen);
    S->writeInt(compLen);
    S->write(compLen, cbuf);
    delete[] cbuf;
    delete[] ubuf;
}

void plNetGameServerState::addRecord(plStateDataRecord* rec, const plUoid& obj)
{
    fRecords.push_back(rec);
    fObjects.push_back(obj);
}

void plNetGameServerState::delRecord(size_t idx)
{
    delete fRecords[idx];
    fRecords.erase(fRecords.begin() + idx);
    fObjects.erase(fObjects.begin() + idx);
}

void plNetGameServerState::clearRecords()
{
    for (auto rec = fRecords.begin(); rec != fRecords.end(); ++rec)
        delete *rec;
    fRecords.resize(0);
}
