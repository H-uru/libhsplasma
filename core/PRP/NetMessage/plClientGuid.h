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

#ifndef _PLCLIENTGUID_H
#define _PLCLIENTGUID_H

#include "PRP/plCreatable.h"
#include "Sys/plUuid.h"

class PLASMA_DLL plClientGuid : public plCreatable
{
    CREATABLE(plClientGuid, kClientGuid, plCreatable)

public:
    enum Flags
    {
        kAcctUuid = 0x1,
        kPlayerID = 0x2,
        kTempPlayerID = 0x4,
        kCCRLevel = 0x8,
        kProtectedLogin = 0x10,
        kBuildType = 0x20,
        kPlayerName = 0x40,
        kSrcAddr = 0x80,
        kSrcPort = 0x100,
        kReserved = 0x200,
        kClientKey = 0x400,
    };

private:
    unsigned short fFlags;
    plUuid fAcctUuid;
    unsigned int fPlayerID;
    ST::string fPlayerName;
    unsigned char fCCRLevel, fProtectedLogin, fBuildType;
    unsigned int fSrcAddr;
    unsigned short fSrcPort;
    unsigned short fReserved;
    ST::string fClientKey;

public:
    plClientGuid() : fFlags() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned short getFlags() const { return fFlags; }
    plUuid getAcctUuid() const { return fAcctUuid; }
    unsigned int getPlayerID() const { return fPlayerID; }
    ST::string getPlayerName() const { return fPlayerName; }
    unsigned char getCCRLevel() const { return fCCRLevel; }
    unsigned char getProtectedLogin() const { return fProtectedLogin; }
    unsigned char getBuildType() const { return fBuildType; }
    unsigned int getSrcAddr() const { return fSrcAddr; }
    unsigned short getSrcPort() const { return fSrcPort; }
    unsigned short getReserved() const { return fReserved; }
    ST::string getClientKey() const { return fClientKey; }

    void setFlags(unsigned short flags) { fFlags = flags; }
    void setAcctUuid(const plUuid& acctUuid) { fAcctUuid = acctUuid; }
    void setPlayerID(unsigned int playerID) { fPlayerID = playerID; }
    void setPlayerName(const ST::string& playerName) { fPlayerName = playerName; }
    void setCCRLevel(unsigned char level) { fCCRLevel = level; }
    void setProtectedLogin(unsigned char protectedLogin) { fProtectedLogin = protectedLogin; }
    void setBuildType(unsigned char buildType) { fBuildType = buildType; }
    void setSrcAddr(unsigned int srcAddr) { fSrcAddr = srcAddr; }
    void setSrcPort(unsigned short srcPort) { fSrcPort = srcPort; }
    void setReserved(unsigned short reserved) { fReserved = reserved; }
    void setClientKey(const ST::string& clientKey) { fClientKey = clientKey; }
};

#endif
