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

class PLASMA_DLL plNetServerSessionInfo {
public:
    enum {
        kHasServerName = 0x01,
        kHasServerType = 0x02,
        kHasServerAddr = 0x04,
        kHasServerPort = 0x08,
        kHasServerGuid = 0x10,
    };

private:
    unsigned char fContents;
    unsigned char fServerType;
    unsigned short fServerPort;
    plString fServerName, fServerAddr;
    plUuid fServerGuid;

public:
    plNetServerSessionInfo();

    void read(hsStream* S);
    void write(hsStream* S);

public:
    unsigned char getContents() const { return fContents; }
    plString getServerName() const { return fServerName; }
    plString getServerAddr() const { return fServerAddr; }
    unsigned char getServerType() const { return fServerType; }
    unsigned short getServerPort() const { return fServerPort; }
    plUuid getServerGuid() const { return fServerGuid; }

    void setServerName(const plString& name);
    void setServerAddr(const plString& addr);
    void setServerType(unsigned char type);
    void setServerPort(unsigned short port);
    void setServerGuid(const plUuid& guid);

    void clearServerName();
    void clearServerAddr();
    void clearServerType();
    void clearServerPort();
    void clearServerGuid();
};


class PLASMA_DLL plNetGameServerState {
public:
    enum Flags {
        kCompressed = 0x1,
        kCompressFailed = 0x2,
        kUnCompressFailed = 0x4,
    };

private:
    unsigned int fFlags;
    unsigned short fMajorVer, fMinorVer;
    plNetServerSessionInfo fSession;
    plSDLMgr fSDLMgr;
    hsTArray<plStateDataRecord*> fRecords;
    hsTArray<plUoid> fObjects;

public:
    plNetGameServerState();
    ~plNetGameServerState();

    void read(hsStream* S);
    void write(hsStream* S);

public:
    unsigned int getFlags() const { return fFlags; }
    unsigned short getMajorVer() const { return fMajorVer; }
    unsigned short getMinorVer() const { return fMinorVer; }
    const plNetServerSessionInfo& getSession() const { return fSession; }
    plNetServerSessionInfo& getSession() { return fSession; }
    const plSDLMgr& getSDLMgr() const { return fSDLMgr; }
    plSDLMgr& getSDLMgr() { return fSDLMgr; }

    void setFlags(unsigned int flags) { fFlags = flags; }

    void setVersion(unsigned short major, unsigned short minor)
    { fMajorVer = major; fMinorVer = minor; }

    size_t numRecords() const { return fRecords.getSize(); }
    plStateDataRecord* getRecord(size_t idx) const { return fRecords[idx]; }
    plUoid getObject(size_t idx) const { return fObjects[idx]; }
    void addRecord(plStateDataRecord* rec, const plUoid& obj);
    void delRecord(size_t idx);
    void clearRecords();
};

#endif
