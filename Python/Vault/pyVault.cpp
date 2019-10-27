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

#include "pyVaultNode.h"

PY_PLASMA_NEW_MSG(Vault, "plVault is static")

typedef PyObject pyVault;
PY_PLASMA_TYPE(Vault, "plVault", "plVault wrapper")

PY_PLASMA_TYPE_INIT(Vault)
{
    pyVault_Type.tp_new = pyVault_new;
    if (PyType_CheckAndReady(&pyVault_Type) < 0)
        return nullptr;

    /* NodeTypes */
    PY_TYPE_ADD_CONST(Vault, "kNodeInvalid", plVault::kNodeInvalid);
    PY_TYPE_ADD_CONST(Vault, "kNodeVNodeMgrLow", plVault::kNodeVNodeMgrLow);
    PY_TYPE_ADD_CONST(Vault, "kNodePlayer", plVault::kNodePlayer);
    PY_TYPE_ADD_CONST(Vault, "kNodeAge", plVault::kNodeAge);
    PY_TYPE_ADD_CONST(Vault, "kNodeGameServer", plVault::kNodeGameServer);
    PY_TYPE_ADD_CONST(Vault, "kNodeAdmin", plVault::kNodeAdmin);
    PY_TYPE_ADD_CONST(Vault, "kNodeVaultServer", plVault::kNodeVaultServer);
    PY_TYPE_ADD_CONST(Vault, "kNodeCCR", plVault::kNodeCCR);
    PY_TYPE_ADD_CONST(Vault, "kNodeVNodeMgrHigh", plVault::kNodeVNodeMgrHigh);
    PY_TYPE_ADD_CONST(Vault, "kNodeFolder", plVault::kNodeFolder);
    PY_TYPE_ADD_CONST(Vault, "kNodePlayerInfo", plVault::kNodePlayerInfo);
    PY_TYPE_ADD_CONST(Vault, "kNodeSystem", plVault::kNodeSystem);
    PY_TYPE_ADD_CONST(Vault, "kNodeImage", plVault::kNodeImage);
    PY_TYPE_ADD_CONST(Vault, "kNodeTextNote", plVault::kNodeTextNote);
    PY_TYPE_ADD_CONST(Vault, "kNodeSDL", plVault::kNodeSDL);
    PY_TYPE_ADD_CONST(Vault, "kNodeAgeLink", plVault::kNodeAgeLink);
    PY_TYPE_ADD_CONST(Vault, "kNodeChronicle", plVault::kNodeChronicle);
    PY_TYPE_ADD_CONST(Vault, "kNodePlayerInfoList", plVault::kNodePlayerInfoList);
    PY_TYPE_ADD_CONST(Vault, "kNodeUNUSED", plVault::kNodeUNUSED);
    PY_TYPE_ADD_CONST(Vault, "kNodeMarker", plVault::kNodeMarker);
    PY_TYPE_ADD_CONST(Vault, "kNodeAgeInfo", plVault::kNodeAgeInfo);
    PY_TYPE_ADD_CONST(Vault, "kNodeAgeInfoList", plVault::kNodeAgeInfoList);
    PY_TYPE_ADD_CONST(Vault, "kNodeMarkerList", plVault::kNodeMarkerList);
    PY_TYPE_ADD_CONST(Vault, "kNodeNumTypes", plVault::kNodeNumTypes);

    /* Standard Nodes */
    PY_TYPE_ADD_CONST(Vault, "kUserDefinedNode", plVault::kUserDefinedNode);
    PY_TYPE_ADD_CONST(Vault, "kInboxFolder", plVault::kInboxFolder);
    PY_TYPE_ADD_CONST(Vault, "kBuddyListFolder", plVault::kBuddyListFolder);
    PY_TYPE_ADD_CONST(Vault, "kIngoreListFolder", plVault::kIgnoreListFolder);
    PY_TYPE_ADD_CONST(Vault, "kPeopleIKnowAboutFolder", plVault::kPeopleIKnowAboutFolder);
    PY_TYPE_ADD_CONST(Vault, "kVaultMgrGlobalDataFolder", plVault::kVaultMgrGlobalDataFolder);
    PY_TYPE_ADD_CONST(Vault, "kChronicleFolder", plVault::kChronicleFolder);
    PY_TYPE_ADD_CONST(Vault, "kAvatarOutfitFolder", plVault::kAvatarOutfitFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeTypeJournalFolder", plVault::kAgeTypeJournalFolder);
    PY_TYPE_ADD_CONST(Vault, "kSubAgesFolder", plVault::kSubAgesFolder);
    PY_TYPE_ADD_CONST(Vault, "kDeviceInboxFolder", plVault::kDeviceInboxFolder);
    PY_TYPE_ADD_CONST(Vault, "kHoodMembersFolder", plVault::kHoodMembersFolder);
    PY_TYPE_ADD_CONST(Vault, "kAllPlayersFolder", plVault::kAllPlayersFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeMembersFolder", plVault::kAgeMembersFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeJournalsFolder", plVault::kAgeJournalsFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeDevicesFolder", plVault::kAgeDevicesFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeInstanceSDLNode", plVault::kAgeInstanceSDLNode);
    PY_TYPE_ADD_CONST(Vault, "kAgeGlobalSDLNode", plVault::kAgeGlobalSDLNode);
    PY_TYPE_ADD_CONST(Vault, "kCanVisitFolder", plVault::kCanVisitFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeOwnersFolder", plVault::kAgeOwnersFolder);
    PY_TYPE_ADD_CONST(Vault, "kAllAgeGlobalSDLNodesFolder", plVault::kAllAgeGlobalSDLNodesFolder);
    PY_TYPE_ADD_CONST(Vault, "kPlayerInfoNode", plVault::kPlayerInfoNode);
    PY_TYPE_ADD_CONST(Vault, "kPublicAgesFolder", plVault::kPublicAgesFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgesIOwnFolder", plVault::kAgesIOwnFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgesICanVisitFolder", plVault::kAgesICanVisitFolder);
    PY_TYPE_ADD_CONST(Vault, "kAvatarClosetFolder", plVault::kAvatarClosetFolder);
    PY_TYPE_ADD_CONST(Vault, "kAgeInfoNode", plVault::kAgeInfoNode);
    PY_TYPE_ADD_CONST(Vault, "kSystemNode", plVault::kSystemNode);
    PY_TYPE_ADD_CONST(Vault, "kPlayerInviteFolder", plVault::kPlayerInviteFolder);
    PY_TYPE_ADD_CONST(Vault, "kCCRPlayersFolder", plVault::kCCRPlayersFolder);
    PY_TYPE_ADD_CONST(Vault, "kGlobalInboxFolder", plVault::kGlobalInboxFolder);
    PY_TYPE_ADD_CONST(Vault, "kChildAgesFolder", plVault::kChildAgesFolder);
    PY_TYPE_ADD_CONST(Vault, "kGameScoresFolder", plVault::kGameScoresFolder);
    PY_TYPE_ADD_CONST(Vault, "kLastStandardNode", plVault::kLastStandardNode);

    /* Note Types */
    PY_TYPE_ADD_CONST(Vault, "kNoteGeneric", plVault::kNoteGeneric);
    PY_TYPE_ADD_CONST(Vault, "kNoteCCRPetition", plVault::kNoteCCRPetition);
    PY_TYPE_ADD_CONST(Vault, "kNoteDevice", plVault::kNoteDevice);
    PY_TYPE_ADD_CONST(Vault, "kNoteInvite", plVault::kNoteInvite);
    PY_TYPE_ADD_CONST(Vault, "kNoteVisit", plVault::kNoteVisit);
    PY_TYPE_ADD_CONST(Vault, "kNoteUnVisit", plVault::kNoteUnVisit);
    PY_TYPE_ADD_CONST(Vault, "kNumNoteTypes", plVault::kNumNoteTypes);

    /* Image Types */
    PY_TYPE_ADD_CONST(Vault, "kNone", plVault::kNone);
    PY_TYPE_ADD_CONST(Vault, "kJPEG", plVault::kJPEG);
    PY_TYPE_ADD_CONST(Vault, "kPNG", plVault::kPNG);

    /* NodePermissions */
    PY_TYPE_ADD_CONST(Vault, "kOwnerRead", plVault::kOwnerRead);
    PY_TYPE_ADD_CONST(Vault, "kOwnerWrite", plVault::kOwnerWrite);
    PY_TYPE_ADD_CONST(Vault, "kGroupRead", plVault::kGroupRead);
    PY_TYPE_ADD_CONST(Vault, "kGroupWrite", plVault::kGroupWrite);
    PY_TYPE_ADD_CONST(Vault, "kOtherRead", plVault::kOtherRead);
    PY_TYPE_ADD_CONST(Vault, "kOtherWrite", plVault::kOtherWrite);
    PY_TYPE_ADD_CONST(Vault, "kDefaultPermissions", plVault::kDefaultPermissions);

    Py_INCREF(&pyVault_Type);
    return (PyObject*)&pyVault_Type;
}
