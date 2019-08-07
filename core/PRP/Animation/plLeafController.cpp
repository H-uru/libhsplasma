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

#include "plLeafController.h"
#include "plKeyControllers.hpp"
#include "plPosController.h"
#include "plRotController.h"
#include "plScaleController.h"
#include "Debug/plDebug.h"

/* plLeafController */
plLeafController::~plLeafController()
{
    DeallocKeys();
    DeallocControllers();
}

void plLeafController::read(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isUniversal()) {
        if (ClassIndex() == kLeafController) {
            fType = S->readByte();
            unsigned int numKeys = S->readInt();
            AllocKeys(numKeys, fType);

            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->read(S, fType);
        } else {
            unsigned int numControllers = S->readInt();
            AllocControllers(numControllers);

            for (size_t i=0; i<fEaseControllers.size(); i++)
                fEaseControllers[i]->read(S, mgr);
            IReadUruController(S);
        }
    } else if (S->getVer().isUruSP()) {
        fUruUnknown = S->readInt();
        if (fUruUnknown != 0)
            plDebug::Debug("Found an UruUnknown of {}", fUruUnknown);
        unsigned int numControllers = S->readInt();
        AllocControllers(numControllers);

        for (size_t i=0; i<fEaseControllers.size(); i++)
            fEaseControllers[i]->read(S, mgr);

        S->readInt();
        IReadUruController(S);
    } else {
        fType = S->readByte();
        if ((S->getVer().isNewPlasma()) && fType >= hsKeyFrame::kCompressedQuatKeyFrame64)
            fType++;    // Myst V doesn't have hsCompressedQuatKeyFrame64
        unsigned int numKeys = S->readInt();
        AllocKeys(numKeys, fType);

        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->read(S, fType);
    }
}

void plLeafController::write(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isUniversal()) {
        if (ClassIndex() == kLeafController) {
            S->writeByte(fType);
            S->writeInt(fKeys.size());

            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->write(S);
        } else {
            S->writeInt(fEaseControllers.size());

            for (size_t i=0; i<fEaseControllers.size(); i++)
                fEaseControllers[i]->write(S, mgr);
            IWriteUruController(S);
        }
    } else if (S->getVer().isUruSP()) {
        S->writeInt(fUruUnknown);
        S->writeInt(fEaseControllers.size());

        for (size_t i=0; i<fEaseControllers.size(); i++)
            fEaseControllers[i]->write(S, mgr);

        S->writeInt(0);
        IWriteUruController(S);
    } else {
        if ((S->getVer().isNewPlasma()) && fType >= hsKeyFrame::kCompressedQuatKeyFrame64)
            S->writeByte(fType - 1);
        else
            S->writeByte(fType);
        S->writeInt(fKeys.size());

        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->write(S);
    }
}

void plLeafController::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Parameters");
    prc->writeParam("Type", hsKeyFrame::TypeNames[fType]);
    if (fUruUnknown != 0)
        prc->writeParam("UruUnknown", fUruUnknown);
    prc->endTag(true);

    if (hasEaseControllers()) {
        prc->writeSimpleTag("EaseControllers");
        for (size_t i=0; i<fEaseControllers.size(); i++)
            fEaseControllers[i]->prcWrite(prc);
        prc->closeTag();
    }

    if (hasKeys()) {
        prc->writeSimpleTag("Keys");
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->prcWrite(prc);
        prc->closeTag();
    }
}

void plLeafController::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Parameters") {
        ST::string typeStr = tag->getParam("Type", "");
        fType = hsKeyFrame::kUnknownKeyFrame;
        for (size_t i=0; i<=hsKeyFrame::kMatrix44KeyFrame; i++) {
            if (typeStr == hsKeyFrame::TypeNames[i])
                fType = i;
        }
        fUruUnknown = tag->getParam("UruUnknown", "0").to_uint();
    } else if (tag->getName() == "Keys") {
        AllocKeys(tag->countChildren(), fType);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fKeys.size(); i++) {
            fKeys[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "EaseControllers") {
        AllocControllers(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEaseControllers.size(); i++) {
            fEaseControllers[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plLeafController::AllocKeys(unsigned int numKeys, unsigned int type)
{
    DeallocKeys();
    fType = type;
    fKeys.resize(numKeys);

    switch (fType) {
    case hsKeyFrame::kPoint3KeyFrame:
    case hsKeyFrame::kBezPoint3KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsPoint3Key();
        break;
    case hsKeyFrame::kScalarKeyFrame:
    case hsKeyFrame::kBezScalarKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsScalarKey();
        break;
    case hsKeyFrame::kScaleKeyFrame:
    case hsKeyFrame::kBezScaleKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsScaleKey();
        break;
    case hsKeyFrame::kQuatKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsQuatKey();
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame32:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsCompressedQuatKey32();
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame64:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsCompressedQuatKey64();
        break;
    case hsKeyFrame::k3dsMaxKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsG3DSMaxKeyFrame();
        break;
    case hsKeyFrame::kMatrix33KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsMatrix33Key();
        break;
    case hsKeyFrame::kMatrix44KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsMatrix44Key();
        break;
    default:
        break;
    }
}

void plLeafController::DeallocKeys()
{
    for (auto key = fKeys.begin(); key != fKeys.end(); ++key)
        delete *key;
    fKeys.clear();
}

void plLeafController::AllocControllers(unsigned int numControllers)
{
    DeallocControllers();
    fEaseControllers.resize(numControllers);
    for (size_t i=0; i<numControllers; i++)
        fEaseControllers[i] = new plEaseController();
}

void plLeafController::DeallocControllers()
{
    for (auto ci = fEaseControllers.begin(); ci != fEaseControllers.end(); ++ci)
        delete *ci;
    fEaseControllers.clear();
}

void plLeafController::IReadUruController(hsStream* S)
{
    switch (ClassIndex()) {
    case kEaseController:
        if (S->readInt() != 0) {
            AllocKeys(S->readInt(), hsKeyFrame::kScalarKeyFrame);
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->read(S, fType);
        } else {
            AllocKeys(0, 0);
        }
        break;
    case kMatrix33Controller:
        AllocKeys(S->readInt(), hsKeyFrame::kMatrix33KeyFrame);
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->read(S, fType);
        break;
    case kMatrix44Controller:
        AllocKeys(S->readInt(), hsKeyFrame::kMatrix44KeyFrame);
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->read(S, fType);
        break;
    case kPoint3Controller:
        if (S->readInt() != 0) {
            AllocKeys(S->readInt(), hsKeyFrame::kPoint3KeyFrame);
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->read(S, fType);
        } else {
            AllocKeys(0, 0);
        }
        break;
    case kQuatController:
        AllocKeys(S->readInt(), hsKeyFrame::kQuatKeyFrame);
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->read(S, fType);
        break;
    case kScalarController:
        if (S->readInt() != 0) {
            AllocKeys(S->readInt(), hsKeyFrame::kScalarKeyFrame);
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->read(S, fType);
        } else {
            AllocKeys(0, 0);
        }
        break;
    case kScaleValueController:
        AllocKeys(S->readInt(), hsKeyFrame::kScaleKeyFrame);
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->read(S, fType);
        break;
    default:
        ST::string err = ST::format("Unexpected class type [{_04X}]", ClassIndex());
        throw hsBadParamException(__FILE__, __LINE__, err);
    }

    if (!fKeys.empty())
        fType = fKeys[0]->getType();
}

void plLeafController::IWriteUruController(hsStream* S)
{
    switch (ClassIndex()) {
    case kEaseController:
        if (fKeys.empty()) {
            S->writeInt(0);
        } else {
            S->writeInt(1);
            S->writeInt(fKeys.size());
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->write(S);
        }
        break;
    case kMatrix33Controller:
        S->writeInt(fKeys.size());
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->write(S);
        break;
    case kMatrix44Controller:
        S->writeInt(fKeys.size());
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->write(S);
        break;
    case kPoint3Controller:
        if (fKeys.empty()) {
            S->writeInt(0);
        } else {
            S->writeInt(1);
            S->writeInt(fKeys.size());
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->write(S);
        }
        break;
    case kQuatController:
        S->writeInt(fKeys.size());
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->write(S);
        break;
    case kScalarController:
        if (fKeys.empty()) {
            S->writeInt(0);
        } else {
            S->writeInt(1);
            S->writeInt(fKeys.size());
            for (size_t i=0; i<fKeys.size(); i++)
                fKeys[i]->write(S);
        }
        break;
    case kScaleValueController:
        S->writeInt(fKeys.size());
        for (size_t i=0; i<fKeys.size(); i++)
            fKeys[i]->write(S);
        break;
    default:
        ST::string err = ST::format("Unexpected class type [{_04X}]", ClassIndex());
        throw hsBadParamException(__FILE__, __LINE__, err);
    }
}

plLeafController* plLeafController::ExpandToKeyController() const
{
    plLeafController* ctrl = nullptr;
    switch (fType) {
    case hsKeyFrame::kPoint3KeyFrame:
    case hsKeyFrame::kBezPoint3KeyFrame:
        ctrl = new plPoint3Controller();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsPoint3Key*)ctrl->fKeys[i] = *(hsPoint3Key*)fKeys[i];
        }
        break;
    case hsKeyFrame::kScalarKeyFrame:
    case hsKeyFrame::kBezScalarKeyFrame:
        ctrl = new plScalarController();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsScalarKey*)ctrl->fKeys[i] = *(hsScalarKey*)fKeys[i];
        }
        break;
    case hsKeyFrame::kScaleKeyFrame:
    case hsKeyFrame::kBezScaleKeyFrame:
        ctrl = new plScaleValueController();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsScaleKey*)ctrl->fKeys[i] = *(hsScaleKey*)fKeys[i];
        }
        break;
    case hsKeyFrame::kQuatKeyFrame:
        ctrl = new plQuatController();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsQuatKey*)ctrl->fKeys[i] = *(hsQuatKey*)fKeys[i];
        }
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame32:
        ctrl = new plQuatController();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++) {
                ((hsQuatKey*)ctrl->fKeys[i])->setType(hsKeyFrame::kQuatKeyFrame);
                ((hsQuatKey*)ctrl->fKeys[i])->setFrame(((hsCompressedQuatKey32*)fKeys[i])->getFrameTime());
                ((hsQuatKey*)ctrl->fKeys[i])->fValue = ((hsCompressedQuatKey32*)fKeys[i])->getQuat();
            }
        }
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame64:
        ctrl = new plQuatController();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++) {
                ((hsQuatKey*)ctrl->fKeys[i])->setType(hsKeyFrame::kQuatKeyFrame);
                ((hsQuatKey*)ctrl->fKeys[i])->setFrame(((hsCompressedQuatKey64*)fKeys[i])->getFrameTime());
                ((hsQuatKey*)ctrl->fKeys[i])->fValue = ((hsCompressedQuatKey64*)fKeys[i])->getQuat();
            }
        }
        break;
    case hsKeyFrame::k3dsMaxKeyFrame:
        ctrl = nullptr;
        break;
    case hsKeyFrame::kMatrix33KeyFrame:
        ctrl = new plMatrix33Controller();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsMatrix33Key*)ctrl->fKeys[i] = *(hsMatrix33Key*)fKeys[i];
        }
        break;
    case hsKeyFrame::kMatrix44KeyFrame:
        ctrl = new plMatrix44Controller();
        if (hasKeys()) {
            ctrl->AllocKeys(fKeys.size(), fType);
            for (size_t i=0; i<fKeys.size(); i++)
                *(hsMatrix44Key*)ctrl->fKeys[i] = *(hsMatrix44Key*)fKeys[i];
        }
        break;
    default:
        break;
    }
    if (ctrl)
        ctrl->fType = fType;
    return ctrl;
}

plLeafController* plLeafController::CompactToLeafController() const
{
    plLeafController* ctrl = new plLeafController();
    ctrl->fType = fType;
    ctrl->fUruUnknown = fUruUnknown;
    if (hasKeys()) {
        ctrl->AllocKeys(fKeys.size(), fType);
        for (size_t i=0; i<fKeys.size(); i++)
            *ctrl->fKeys[i] = *fKeys[i];
    }
    if (hasEaseControllers())
        plDebug::Warning("Warning: Throwing away {} Ease Controllers", fEaseControllers.size());
    return ctrl;
}

plController* plLeafController::EncapsulateKeyController() const
{
    plLeafController* expanded = ExpandToKeyController();
    switch (expanded->ClassIndex()) {
    case kPoint3Controller: {
        plSimplePosController* pos = new plSimplePosController();
        pos->setPosition(plPoint3Controller::Convert(expanded));
        return pos;
    }
    case kScaleValueController: {
        plSimpleScaleController* scale = new plSimpleScaleController();
        scale->setValue(plScaleValueController::Convert(expanded));
        return scale;
    }
    case kQuatController: {
        plSimpleRotController* rot = new plSimpleRotController();
        rot->setRot(plQuatController::Convert(expanded));
        return rot;
    }
    default:
        return expanded;
    }
}

void plLeafController::setKeys(const std::vector<hsKeyFrame*>& keys, unsigned int type)
{
    DeallocKeys();
    AllocKeys(keys.size(), type);
    for (size_t i=0; i<keys.size(); i++)
        *fKeys[i] = *keys[i];
}

void plLeafController::setEaseControllers(const std::vector<class plEaseController*>& controllers)
{
    DeallocControllers();
    AllocControllers(controllers.size());
    for (size_t i=0; i<controllers.size(); i++)
        *fEaseControllers[i] = *controllers[i];
}
