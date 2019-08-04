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

#ifndef _PFKIMSG_H
#define _PFKIMSG_H

#include "plMessage.h"

class PLASMA_DLL pfKIMsg : public plMessage
{
    CREATABLE(pfKIMsg, kKIMsg, plMessage)

public:
    enum
    {
        kHACKChatMsg, kEnterChatMode, kSetChatFadeDelay, kSetTextChatAdminMode,
        kDisableKIandBB, kEnableKIandBB, kYesNoDialog, kAddPlayerDevice,
        kRemovePlayerDevice, kUpgradeKILevel, kDowngradeKILevel, kRateIt,
        kSetPrivateChatChannel, kUnsetPrivateChatChannel, kStartBookAlert,
        kMiniBigKIToggle, kKIPutAway, kChatAreaPageUp, kChatAreaPageDown,
        kChatAreaGoToBegin, kChatAreaGoToEnd, kKITakePicture,
        kKICreateJournalNote, kKIToggleFade, kKIToggleFadeEnable,
        kKIChatStatusMsg, kKILocalChatStatusMsg, kKIUpSizeFont,
        kKIDownSizeFont, kKIOpenYeehsaBook, kKIOpenKI, kKIShowCCRHelp,
        kKICreateMarker, kKICreateMarkerFolder, kKILocalChatErrorMsg,
        kKIPhasedAllOn, kKIPhasedAllOff, kKIOKDialog, kDisableYeeshaBook,
        kEnableYeeshaBook, kQuitDialog, kTempDisableKIandBB, kTempEnableKIandBB,
        kDisableEntireYeeshaBook, kEnableEntireYeeshaBook, kKIOKDialogNoQuit,
        kGZUpdated, kGZInRange, kGZOutRange, kUpgradeKIMarkerLevel,
        kKIShowMiniKI, kGZFlashUpdate, kStartJournalAlert, kAddJournalBook,
        kRemoveJournalBook, kKIOpenJournalBook, kMGStartCGZGame, kMGStopCGZGame,
        kKICreateMarkerNode, kStartKIAlert, kUpdatePelletScore, kFriendInviteSent,
        kRegisterImager, kNoCommand
    };

    enum Flags
    {
        kPrivateMsg = 0x1,
        kAdminMsg = 0x2,
        kDead = 0x4,
        kUNUSED1 = 0x8,
        kStatusMsg = 0x10,
        kNeighborMsg = 0x20,
        kChannelMask = 0xFF00
    };

    enum KILevels
    {
        kNanoKI, kMicroKI, kNormalKI
    };

protected:
    unsigned char fCommand;
    unsigned int fFlags, fPlayerID;
    ST::string fUser, fString;
    float fDelay;
    int fValue;

public:
    pfKIMsg() : fCommand(kNoCommand), fFlags(), fPlayerID(), fDelay(), fValue()
    {
        fBCastFlags |= kBCastByExactType;
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getCommand() const { return fCommand; }
    unsigned int getFlags() const { return fFlags; }
    unsigned int getPlayerID() const { return fPlayerID; }
    ST::string getUser() const { return fUser; }
    ST::string getString() const { return fString; }
    float getDelay() const { return fDelay; }
    int getValue() const { return fValue; }

    void setCommand(unsigned char command) { fCommand = command; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setPlayerID(unsigned int playerID) { fPlayerID = playerID; }
    void setUser(const ST::string& user) { fUser = user; }
    void setString(const ST::string& str) { fString = str; }
    void setDelay(float delay) { fDelay = delay; }
    void setValue(int value) { fValue = value; }
};

#endif
