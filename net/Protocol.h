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

#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "PlasmaDefs.h"
#include "Sys/plUuid.h"

enum ENetError
{
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
PLASMANET_DLL const char* GetNetErrorString(int errcode);

enum ENetProtocol
{
    kNetProtocolNil, kNetProtocolDebug, kNetProtocolCli2Unused_00,
    kNetProtocolCli2Csr, kNetProtocolCli2Auth, kNetProtocolCli2Game,
    kNetProtocolCli2File, kNetProtocolCli2Unused_01,
};

enum EConnType
{
    kConnTypeNil, kConnTypeDebug,
    kConnTypeCliToAuth = 10, kConnTypeCliToGame, kConnTypeSrvToAgent,
    kConnTypeSrvToMcp, kConnTypeSrvToVault, kConnTypeSrvToDb,
    kConnTypeCliToFile, kConnTypeSrvToState, kConnTypeSrvToLog,
    kConnTypeSrvToScore, kConnTypeCliToCsr, kConnTypeSimpleNet,
    kConnTypeCliToGateKeeper,
};

enum NetCliConnectMsg
{
    kNetCliCli2SrvConnect, kNetCliSrv2CliEncrypt, kNetCliSrv2CliError,
};

#endif
