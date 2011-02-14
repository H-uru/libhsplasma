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

#ifndef _PFGUIDIALOGMOD_H
#define _PFGUIDIALOGMOD_H

#include "pfGUIControlMod.h"

class PLASMA_DLL pfGUIDialogMod : public virtual plSingleModifier {
    CREATABLE(pfGUIDialogMod, kGUIDialogMod, plSingleModifier)

public:
    enum Flags { kModal, kDerivedFlagsStart };

protected:
    unsigned int fTagID, fVersion;
    plKey fRenderMod;
    char fName[128];
    hsTArray<plKey> fControls;
    pfGUIColorScheme fColorScheme;
    plKey fProcReceiver, fSceneNode;

public:
    pfGUIDialogMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getControls() const { return fControls; }
    hsTArray<plKey>& getControls() { return fControls; }
    void addControl(plKey ctrl) { fControls.append(ctrl); }
    void delControl(size_t idx) { fControls.remove(idx); }
    void clearControls() { fControls.clear(); }

    unsigned int getTagID() const { return fTagID; }
    unsigned int getVersion() const { return fVersion; }
    plKey getRenderMod() const { return fRenderMod; }
    plString getName() const { return fName; }
    plKey getProcReceiver() const { return fProcReceiver; }
    plKey getSceneNode() const { return fSceneNode; }

    void setTagID(unsigned int id) { fTagID = id; }
    void setVersion(unsigned int version) { fVersion = version; }
    void setRenderMod(plKey mod) { fRenderMod = mod; }
    void setName(const char* name) { strncpy(fName, name, 128); }
    void setProcReceiver(plKey receiver) { fProcReceiver = receiver; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const pfGUIColorScheme& getColorScheme() const { return fColorScheme; }
    pfGUIColorScheme& getColorScheme() { return fColorScheme; }
};

#endif
