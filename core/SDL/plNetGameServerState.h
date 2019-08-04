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

#ifndef _PLNETGAMESERVERSTATE_H
#define _PLNETGAMESERVERSTATE_H

#include "plSDLMgr.h"
#include "plStateDataRecord.h"
#include "Sys/plUuid.h"

class PLASMA_DLL plNetServerSessionInfo
{
public:
    enum
    {
        kHasServerName = 0x01,
        kHasServerType = 0x02,
        kHasServerAddr = 0x04,
        kHasServerPort = 0x08,
        kHasServerGuid = 0x10,
    };

private:
    uint8_t fContents;
    uint8_t fServerType;
    uint16_t fServerPort;
    ST::string fServerName, fServerAddr;
    plUuid fServerGuid;

public:
    plNetServerSessionInfo() : fContents(), fServerType(), fServerPort() { }

    void read(hsStream* S);
    void write(hsStream* S);

public:
    uint8_t getContents() const { return fContents; }
    ST::string getServerName() const { return fServerName; }
    ST::string getServerAddr() const { return fServerAddr; }
    uint8_t getServerType() const { return fServerType; }
    uint16_t getServerPort() const { return fServerPort; }
    plUuid getServerGuid() const { return fServerGuid; }

    void setServerName(const ST::string& name);
    void setServerAddr(const ST::string& addr);
    void setServerType(uint8_t type);
    void setServerPort(uint16_t port);
    void setServerGuid(const plUuid& guid);

    void clearServerName();
    void clearServerAddr();
    void clearServerType();
    void clearServerPort();
    void clearServerGuid();
};


class PLASMA_DLL plNetGameServerState
{
public:
    enum Flags
    {
        kCompressed = 0x1,
        kCompressFailed = 0x2,
        kUnCompressFailed = 0x4,
    };

private:
    uint32_t fFlags;
    uint16_t fMajorVer, fMinorVer;
    plNetServerSessionInfo fSession;
    plSDLMgr fSDLMgr;
    std::vector<plStateDataRecord*> fRecords;
    std::vector<plUoid> fObjects;

public:
    plNetGameServerState() : fFlags(kCompressed), fMajorVer(1), fMinorVer(1) { }
    ~plNetGameServerState();

    void read(hsStream* S);
    void write(hsStream* S);

public:
    uint32_t getFlags() const { return fFlags; }
    uint16_t getMajorVer() const { return fMajorVer; }
    uint16_t getMinorVer() const { return fMinorVer; }
    const plNetServerSessionInfo& getSession() const { return fSession; }
    plNetServerSessionInfo& getSession() { return fSession; }
    const plSDLMgr& getSDLMgr() const { return fSDLMgr; }
    plSDLMgr& getSDLMgr() { return fSDLMgr; }

    void setFlags(uint32_t flags) { fFlags = flags; }

    void setVersion(uint16_t major, uint16_t minor)
    {
        fMajorVer = major;
        fMinorVer = minor;
    }

    size_t numRecords() const { return fRecords.size(); }
    plStateDataRecord* getRecord(size_t idx) const { return fRecords[idx]; }
    plUoid getObject(size_t idx) const { return fObjects[idx]; }
    void addRecord(plStateDataRecord* rec, const plUoid& obj);
    void delRecord(size_t idx);
    void clearRecords();
};

#endif
