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

#ifndef _PLSCALARCHANNEL_H
#define _PLSCALARCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Scalar Channels */
class PLASMA_DLL plScalarChannel : public plAGChannel
{
    CREATABLE(plScalarChannel, kScalarChannel, plAGChannel)

protected:
    float fResult;

public:
    float getResult() const { return fResult; }
    void setResult(float result) { fResult = result; }
};


class PLASMA_DLL plScalarBlend : public plScalarChannel
{
    CREATABLE(plScalarBlend, kScalarBlend, plScalarChannel)
};


class PLASMA_DLL plScalarConstant : public plScalarChannel
{
    CREATABLE(plScalarConstant, kScalarConstant, plScalarChannel)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plScalarControllerCacheChannel : public plScalarChannel
{
    CREATABLE(plScalarControllerCacheChannel, kScalarControllerCacheChannel,
              plScalarChannel)
};


class PLASMA_DLL plScalarControllerChannel : public plScalarChannel
{
    CREATABLE(plScalarControllerChannel, kScalarControllerChannel,
              plScalarChannel)

protected:
    plController* fController;

public:
    plScalarControllerChannel() : fController() { }
    ~plScalarControllerChannel();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plController* getController() const { return fController; }
    void setController(plController* controller);
};


class PLASMA_DLL plScalarTimeScale : public plScalarChannel
{
    CREATABLE(plScalarTimeScale, kScalarTimeScale, plScalarChannel)
};

class PLASMA_DLL plScalarSDLChannel : public plScalarChannel
{
    CREATABLE(plScalarSDLChannel, kScalarSDLChannel, plScalarChannel)
};

class PLASMA_DLL plATCChannel : public plScalarChannel
{
    CREATABLE(plATCChannel, kATCChannel, plScalarChannel)
};


/* Scalar Channel Applicators */
class PLASMA_DLL plScalarChannelApplicator : public plAGApplicator
{
    CREATABLE(plScalarChannelApplicator, kScalarChannelApplicator,
              plAGApplicator)
};

#endif
