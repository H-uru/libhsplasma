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

#ifndef _PLTMCONTROLLER_H
#define _PLTMCONTROLLER_H

#include "plPosController.h"
#include "plRotController.h"
#include "plScaleController.h"

DllClass plTMController : public plController {
    CREATABLE(plTMController, kTMController, plController)

protected:
    plPosController* fPosController;
    plRotController* fRotController;
    plScaleController* fScaleController;

public:
    plTMController();
    virtual ~plTMController();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    plCompoundController* convertToCompoundController();

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plPosController* getPosController() const { return fPosController; }
    plRotController* getRotController() const { return fRotController; }
    plScaleController* getScaleController() const { return fScaleController; }

    void setPosController(plPosController* controller);
    void setRotController(plRotController* controller);
    void setScaleController(plScaleController* controller);
};

#endif
