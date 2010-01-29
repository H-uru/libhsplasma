#ifndef _PLNETGAMESERVERSTATE_H
#define _PLNETGAMESERVERSTATE_H

#include "plSDLMgr.h"
#include "plStateDataRecord.h"
#include "Sys/plUuid.h"

DllClass plNetServerSessionInfo {
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
    ~plNetServerSessionInfo();

    void read(hsStream* S);
    void write(hsStream* S);

    unsigned char getContents() const;
    plString getServerName() const;
    plString getServerAddr() const;
    unsigned char getServerType() const;
    unsigned short getServerPort() const;
    plUuid getServerGuid() const;

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

DllClass plNetGameServerState {
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

    unsigned int getFlags() const;
    unsigned short getMajorVer() const;
    unsigned short getMinorVer() const;
    plNetServerSessionInfo& getSession();
    plSDLMgr& getSDLMgr();

    void setFlags(unsigned int flags);
    void setVersion(unsigned short major, unsigned short minor);

    void clearRecords();
    size_t numRecords() const;
    plStateDataRecord* getRecord(size_t idx) const;
    plUoid getObject(size_t idx) const;
    void addRecord(plStateDataRecord* rec, const plUoid& obj);
    void delRecord(size_t idx);
};

#endif
