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

#ifndef _PLCONTROLLER_H
#define _PLCONTROLLER_H

#include "PRP/plCreatable.h"
#include "ResManager/plResManager.h"
#include "hsKeys.h"

class PLASMA_DLL plController : public plCreatable
{
    CREATABLE(plController, kController, plCreatable)

public:
    static void WriteController(hsStream* S, plResManager* mgr, plController* controller);
};


class PLASMA_DLL plCompoundController : public plController
{
    CREATABLE(plCompoundController, kCompoundController, plController)

protected:
    plController* fXController;
    plController* fYController;
    plController* fZController;

public:
    enum { kPosController, kRotController, kScaleController, kNumControllers };

    plCompoundController()
        : fXController(), fYController(), fZController() { }
    ~plCompoundController();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    class plTMController* convertToTMController();

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plController* getXController() const { return fXController; }
    plController* getYController() const { return fYController; }
    plController* getZController() const { return fZController; }

    plController* getController(unsigned int index) const
    {
        switch (index)
        {
        case kPosController:
            return fXController;
        case kRotController:
            return fYController;
        case kScaleController:
            return fZController;
        default:
            return nullptr;
        }
    }

    void setController(unsigned int index, plController* controller);
    void setXController(plController* controller);
    void setYController(plController* controller);
    void setZController(plController* controller);
};

#endif
