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

#ifndef _PLMATRIXCHANNEL_H
#define _PLMATRIXCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Matrix Channels */
class HSPLASMA_EXPORT plMatrixChannel : public plAGChannel
{
    CREATABLE(plMatrixChannel, kMatrixChannel, plAGChannel)

protected:
    hsAffineParts fAP;

public:
    hsAffineParts getAffine() const { return fAP; }
    void setAffine(const hsAffineParts& ap) { fAP = ap; }
};


class HSPLASMA_EXPORT plMatrixBlend : public plMatrixChannel
{
    CREATABLE(plMatrixBlend, kMatrixBlend, plMatrixChannel)
};


class HSPLASMA_EXPORT plMatrixConstant : public plMatrixChannel
{
    CREATABLE(plMatrixConstant, kMatrixConstant, plMatrixChannel)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class HSPLASMA_EXPORT plMatrixControllerCacheChannel : public plMatrixChannel
{
    CREATABLE(plMatrixControllerCacheChannel, kMatrixControllerCacheChannel,
              plMatrixChannel)
};


class HSPLASMA_EXPORT plMatrixControllerChannel : public plMatrixChannel
{
    CREATABLE(plMatrixControllerChannel, kMatrixControllerChannel,
              plMatrixChannel)

protected:
    plController* fController;

public:
    plMatrixControllerChannel() : fController() { }
    ~plMatrixControllerChannel();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plController* getController() const { return fController; }
    void setController(plController* controller);
};


class HSPLASMA_EXPORT plMatrixTimeScale : public plMatrixChannel
{
    CREATABLE(plMatrixTimeScale, kMatrixTimeScale, plMatrixChannel)
};

class HSPLASMA_EXPORT plQuatPointCombine : public plMatrixChannel
{
    CREATABLE(plQuatPointCombine, kQuatPointCombine, plMatrixChannel)
};


/* Matrix Channel Applicators */
class HSPLASMA_EXPORT plMatrixChannelApplicator : public plAGApplicator
{
    CREATABLE(plMatrixChannelApplicator, kMatrixChannelApplicator,
              plAGApplicator)
};

class HSPLASMA_EXPORT plMatrixDelayedCorrectionApplicator : public plMatrixChannelApplicator
{
    CREATABLE(plMatrixDelayedCorrectionApplicator,
              kMatrixDelayedCorrectionApplicator,
              plMatrixChannelApplicator)
};

class HSPLASMA_EXPORT plMatrixDifferenceApp : public plMatrixChannelApplicator
{
    CREATABLE(plMatrixDifferenceApp, kMatrixDifferenceApp,
              plMatrixChannelApplicator)
};

class HSPLASMA_EXPORT plRelativeMatrixChannelApplicator : public plAGApplicator
{
    CREATABLE(plRelativeMatrixChannelApplicator,
              kRelativeMatrixChannelApplicator,
              plAGApplicator)
};

#endif
