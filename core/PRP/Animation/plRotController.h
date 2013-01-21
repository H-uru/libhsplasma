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

#ifndef _PLROTCONTROLLER_H
#define _PLROTCONTROLLER_H

#include "plKeyControllers.hpp"

class PLASMA_DLL plRotController : public plController {
    CREATABLE(plRotController, kRotController, plController)

public:
    enum { kSimple = 1, kUnused, kCompound };

public:
    virtual int getType() const = 0;
};


class PLASMA_DLL plSimpleRotController : public plRotController {
    CREATABLE(plSimpleRotController, kSimpleRotController, plRotController)

protected:
    plQuatController* fRot;

public:
    plSimpleRotController() : fRot(NULL) { }
    virtual ~plSimpleRotController();

    virtual int getType() const { return kSimple; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plQuatController* getRot() const { return fRot; }
    void setRot(plQuatController* rot);
};


class PLASMA_DLL plCompoundRotController : public plRotController {
    CREATABLE(plCompoundRotController, kCompoundRotController, plRotController)

protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    enum { kX, kY, kZ, kNumControllers };

    plCompoundRotController()
        : fXController(NULL), fYController(NULL), fZController(NULL) { }
    virtual ~plCompoundRotController();

    virtual int getType() const { return kCompound; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plScalarController* getX() const { return fXController; }
    plScalarController* getY() const { return fYController; }
    plScalarController* getZ() const { return fZController; }
    plScalarController* getController(unsigned int index) const {
        switch (index)
        {
        case kX:
            return fXController;
        case kY:
            return fYController;
        case kZ:
            return fZController;
        default:
            return NULL;
        }
    }

    void setController(unsigned int index, plScalarController* controller);
    void setX(plScalarController* controller);
    void setY(plScalarController* controller);
    void setZ(plScalarController* controller);
};

#endif
