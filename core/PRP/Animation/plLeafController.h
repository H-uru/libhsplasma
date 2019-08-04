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

class PLASMA_DLL plLeafController : public plController
{
    CREATABLE(plLeafController, kLeafController, plController)

protected:
    unsigned int fType, fUruUnknown;
    std::vector<hsKeyFrame*> fKeys;
    std::vector<class plEaseController*> fEaseControllers;

public:
    plLeafController() : fType(), fUruUnknown() { }
    ~plLeafController();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

    void AllocKeys(unsigned int numKeys, unsigned int type);
    void DeallocKeys();
    void AllocControllers(unsigned int numControllers);
    void DeallocControllers();

    void IReadUruController(hsStream* S);
    void IWriteUruController(hsStream* S);

public:
    plLeafController* ExpandToKeyController() const;
    plLeafController* CompactToLeafController() const;
    plController* EncapsulateKeyController() const;

    bool hasKeys() const { return !fKeys.empty(); }
    bool hasEaseControllers() const { return !fEaseControllers.empty(); }

    unsigned int getType() const { return fType; }
    const std::vector<hsKeyFrame*>& getKeys() const { return fKeys; }
    const std::vector<class plEaseController*>& getEaseControllers() const { return fEaseControllers; }

    void setKeys(const std::vector<hsKeyFrame*>& keys, unsigned int type);
    void setEaseControllers(const std::vector<class plEaseController*>& controllers);
};

#endif
