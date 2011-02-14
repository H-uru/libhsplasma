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

#ifndef _PLLEAFCONTROLLER_H
#define _PLLEAFCONTROLLER_H

#include "plController.h"

class PLASMA_DLL plLeafController : public plController {
    CREATABLE(plLeafController, kLeafController, plController)

protected:
    unsigned int fType, fUruUnknown;
    hsTArray<hsKeyFrame*> fKeys;
    hsTArray<class plEaseController*> fEaseControllers;

public:
    plLeafController();
    virtual ~plLeafController();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    void AllocKeys(unsigned int numKeys, unsigned int type);
    void DeallocKeys();
    void AllocControllers(unsigned int numControllers);
    void DeallocControllers();

    void IReadUruController(hsStream* S);
    void IWriteUruController(hsStream* S);

public:
    plLeafController* ExpandToKeyController() const;
    plLeafController* CompactToLeafController() const;

    bool hasKeys() const { return fKeys.getSize() != 0; }
    bool hasEaseControllers() const { return fEaseControllers.getSize() != 0; }

    unsigned int getType() const { return fType; }
    const hsTArray<hsKeyFrame*>& getKeys() const { return fKeys; }
    const hsTArray<class plEaseController*>& getEaseControllers() const { return fEaseControllers; }

    void setKeys(const hsTArray<hsKeyFrame*>& keys, unsigned int type);
    void setEaseControllers(const hsTArray<class plEaseController*>& controllers);
};

#endif
