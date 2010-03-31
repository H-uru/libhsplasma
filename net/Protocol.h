#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "PlasmaDefs.h"
#include "Sys/plUuid.h"

enum ENetError {
    kNetPending = -1,
    kNetSuccess = 0, kNetErrInternalError, kNetErrTimeout, kNetErrBadServerData,
    kNetErrAgeNotFound, kNetErrConnectFailed, kNetErrDisconnected,
    kNetErrFileNotFound, kNetErrOldBuildId, kNetErrRemoteShutdown,
    kNetErrTimeoutOdbc, kNetErrAccountAlreadyExists, kNetErrPlayerAlreadyExists,
    kNetErrAccountNotFound, kNetErrPlayerNotFound, kNetErrInvalidParameter,
    kNetErrNameLookupFailed, kNetErrLoggedInElsewhere, kNetErrVaultNodeNotFound,
    kNetErrMaxPlayersOnAcct, kNetErrAuthenticationFailed,
    kNetErrStateObjectNotFound, kNetErrLoginDenied, kNetErrCircularReference,
    kNetErrAccountNotActivated, kNetErrKeyAlreadyUsed, kNetErrKeyNotFound,
    kNetErrActivationCodeNotFound, kNetErrPlayerNameInvalid,
    kNetErrNotSupported, kNetErrServiceForbidden, kNetErrAuthTokenTooOld,
    kNetErrMustUseGameTapClient, kNetErrTooManyFailedLogins,
    kNetErrGameTapConnectionFailed, kNetErrGTTooManyAuthOptions,
    kNetErrGTMissingParameter, kNetErrGTServerError, kNetErrAccountBanned,
    kNetErrKickedByCCR, kNetErrScoreWrongType, kNetErrScoreNotEnoughPoints,
    kNetErrScoreAlreadyExists, kNetErrScoreNoDataFound,
    kNetErrInviteNoMatchingPlayer, kNetErrInviteTooManyHoods, kNetErrNeedToPay,
    kNetErrServerBusy, kNumNetErrors,
};
DllExport const char* GetNetErrorString(int errcode);

enum ENetProtocol {
    kNetProtocolNil, kNetProtocolDebug, kNetProtocolCli2Unused_00,
    kNetProtocolCli2Csr, kNetProtocolCli2Auth, kNetProtocolCli2Game,
    kNetProtocolCli2File, kNetProtocolCli2Unused_01,
};

enum EConnType {
    kConnTypeNil, kConnTypeDebug,
    kConnTypeCliToAuth = 10, kConnTypeCliToGame, kConnTypeSrvToAgent,
    kConnTypeSrvToMcp, kConnTypeSrvToVault, kConnTypeSrvToDb,
    kConnTypeCliToFile, kConnTypeSrvToState, kConnTypeSrvToLog,
    kConnTypeSrvToScore, kConnTypeCliToCsr, kConnTypeSimpleNet,
    kConnTypeCliToGateKeeper,
};

enum NetCliConnectMsg {
    kNetCliCli2SrvConnect, kNetCliSrv2CliEncrypt, kNetCliSrv2CliError,
};

/* Wide strings used in the Network protocol */
typedef unsigned short NCchar_t;

DllExport size_t NCstrlen(const NCchar_t* str);
DllExport NCchar_t* NCstrdup(const NCchar_t* str);
DllExport plString NCstrToString(const NCchar_t* str);
DllExport NCchar_t* StringToNCstr(const plString& str);
DllExport void NCstrlower(NCchar_t* str);

#endif
