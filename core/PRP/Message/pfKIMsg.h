#ifndef _PFKIMSG_H
#define _PFKIMSG_H

#include "plMessage.h"

DllClass pfKIMsg : public plMessage {
public:
    enum {
        kHACKChatMsg, kEnterChatMode, kSetChatFadeDelay, kSetTextChatAdminMode,
        kDisableKIandBB, kEnableKIandBB, kYesNoDialog, kAddPlayerDevice,
        kRemovePlayerDevice, kUpgradeKILevel, kDowngradeKILevel, kRateIt,
        kSetPrivateChatChannel, kUnsetPrivateChatChannel, kStartBookAlert,
        kMiniBigKIToggle, kKIPutAway, kChatAreaPageUp, kChatAreaPageDown,
        kChatAreaGoToBegin, kChatAreaGoToEnd, KITakePicture,
        kKICreateJournalNote, kKIToggleFade, kKIToggleFadeEnable,
        kKIChatStatusMsg, kKILocalChatStatusMsg, kKIUpSizeFont,
        kKIDownSizeFont, kKIOpenYeehsaBook, kKIOpenKI, kKIShowCCRHelp,
        kKICreateMarker, kKICreateMarkerFolder, kKILocalChatErrorMsg,
        kKIPhasedAllOn, kKIPhasedAllOff, kKIOKDialog, kDisableYeeshaBook,
        kEnableYeeshaBook, kQuitDialog, kTempDisableKIandBB, kTempEnableKIandBB,
        kDisableEntireYeeshaBook, kEnableEntireYeeshaBook, kKIOKDialogNoQuit,
        kGZUpdated, kGZInRange, kGZOutRange, kUpgradeKIMarkerLevel,
        kKIShowMiniKI, kGZFlashUpdate, kStartJournalAlert, kAddJournalBook,
        kRemoveJournalBook, kKIOpenJournalBook, kNoCommand
    };

    enum Flags {
        kPrivateMsg = 0x1,
        kAdminMsg = 0x2,
        kDead = 0x4,
        kUNUSED1 = 0x8,
        kStatusMsg = 0x10,
        kNeighborMsg = 0x20,
        kChannelMask = 0xFFFFFF00
    };

    enum KILevels {
        kNanoKI, kMicroKI, kNormalKI
    };

protected:
    unsigned char fCommand;
    unsigned int fFlags, fPlayerID;
    plString fUser;
    plWString fString;
    float fDelay;
    int fValue;

public:
    pfKIMsg();
    virtual ~pfKIMsg();

    DECLARE_CREATABLE(pfKIMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
