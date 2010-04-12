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

DllClass plRotController : public plController {
    CREATABLE(plRotController, kRotController, plController)

public:
    enum { kSimple = 1, kUnused, kCompound };

public:
    virtual int getType() const = 0;
};


DllClass plSimpleRotController : public plRotController {
    CREATABLE(plSimpleRotController, kSimpleRotController, plRotController)

protected:
    plQuatController* fRot;

public:
    plSimpleRotController();
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


DllClass plCompoundRotController : public plRotController {
    CREATABLE(plCompoundRotController, kCompoundRotController, plRotController)

protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    plCompoundRotController();
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

    void setX(plScalarController* controller);
    void setY(plScalarController* controller);
    void setZ(plScalarController* controller);
};

#endif
