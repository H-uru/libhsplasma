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
#include "hsKeys.h"

class PLASMA_DLL plController : public plCreatable {
    CREATABLE(plController, kController, plCreatable)

public:
    static void WriteController(hsStream* S, plResManager* mgr, plController* controller);
};


class PLASMA_DLL plCompoundController : public plController {
    CREATABLE(plCompoundController, kCompoundController, plController)

protected:
    plController* fXController;
    plController* fYController;
    plController* fZController;

public:
    plCompoundController();
    virtual ~plCompoundController();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    class plTMController* convertToTMController();

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getXController() const { return fXController; }
    plController* getYController() const { return fYController; }
    plController* getZController() const { return fZController; }

    void setXController(plController* controller);
    void setYController(plController* controller);
    void setZController(plController* controller);
};

#endif
