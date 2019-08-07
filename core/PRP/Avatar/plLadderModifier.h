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

#ifndef _PLLADDERMODIFIER_H
#define _PLLADDERMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

 /**
 * \brief Defines a movement-driven Ladder modifier.
 *
 * When the avatar enters a physical with this modifier attached, it
 * places the Avatar into a climbing state, which then plays through
 * the climbing animation (and loops if required by its type) in the
 * direction specified.
 */

class PLASMA_DLL plAvLadderMod : public plSingleModifier
{
    CREATABLE(plAvLadderMod, kAvLadderMod, plSingleModifier)

public:
    enum TypeField
    {
        /**
        * Ladder is of arbitrary length
        * \sa setLoops()
        */
        kBig,

        /** Ladder is four-feet tall */
        kFourFeet,

        /** Ladder is two-feet tall */
        kTwoFeet,
        kNumTypeFields
    };

protected:
    bool fGoingUp, fEnabled;
    int fType, fLoops;
    hsVector3 fLadderView;

public:
    plAvLadderMod() : fGoingUp(), fEnabled(true), fType(kBig), fLoops() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns whether this ladder's direction is upward */
    bool getGoingUp() const { return fGoingUp; };

    /** Returns the number of animation loops played for this ladder */
    int getLoops() const { return fLoops; };

    /**
    * Returns the type for this ladder
    * \sa TypeField
    */
    int getType() const { return fType; };

    /** Returns whether this ladder is enabled by default */
    bool isEnabled() const { return fEnabled; };

    /** Returns the normal vector of the ladder for checking avatar facing */
    hsVector3 getLadderView() const { return fLadderView; };

    /** Sets whether this ladder's direction is upward */
    void setGoingUp(bool goingUp) { fGoingUp = goingUp; };

    /** Sets the number of animation loops played for this ladder */
    void setLoops(const int loops) { fLoops = loops; };

    /**
    * Sets the type for this ladder
    * \sa TypeField
    */
    void setType(const int type) { fType = type; };

    /** Sets whether this ladder is enabled by default */
    void setEnabled(bool enabled) { fEnabled = enabled; };

    /** Sets the normal vector of the ladder for checking avatar facing */
    void setLadderView(const hsVector3& ladderView) { fLadderView = ladderView; };
};

/**
* \brief Defines a clickable Ladder modifier.
*
* This ladder modifier is intended to be entirely driven by interactions
* with clickables. The user clicks to enter, ascend or descend, and exit
* the ladder.
*/

class PLASMA_DLL plLadderModifier : public plSingleModifier
{
    CREATABLE(plLadderModifier, kLadderModifier, plSingleModifier)

protected:
    plKey fTopLogic, fBottomLogic, fMainLogic;
    plKey fExitTop, fExitBottom, fTopPos, fBottomPos;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns the clickable plLogicModifier for this ladder's top end */
    plKey getTopLogic() const { return fTopLogic; }

    /** Returns the clickable plLogicModifier for this ladder's bottom end */
    plKey getBottomLogic() const { return fBottomLogic; }

    /** Returns the clickable plLogicModifier for this ladder's middle */
    plKey getMainLogic() const { return fMainLogic; }

    /** Returns the plSceneNode for this ladder's top exit point */
    plKey getExitTop() const { return fExitTop; }

    /** Returns the plSceneNode for this ladder's bottom exit point */
    plKey getExitBottom() const { return fExitBottom; }

    /** Returns the plSceneNode for this ladder's top entry seekpoint */
    plKey getTopPos() const { return fTopPos; }

    /** Returns the plSceneNode for this ladder's bottom entry seekpoint */
    plKey getBottomPos() const { return fBottomPos; }

    /** Sets the clickable plLogicModifier for this ladder's top end */
    void setTopLogic(plKey topLogic) { fTopLogic = std::move(topLogic); }

    /** Sets the clickable plLogicModifier for this ladder's bottom end */
    void setBottomLogic(plKey bottomLogic) { fBottomLogic = std::move(bottomLogic); }

    /** Sets the clickable plLogicModifier for this ladder's middle */
    void setMainLogic(plKey mainLogic) { fMainLogic = std::move(mainLogic); }

    /** Sets the plSceneNode for this ladder's top exit point */
    void setExitTop(plKey exitTop) { fExitTop = std::move(exitTop); }

    /** Sets the plSceneNode for this ladder's bottom exit point */
    void setExitBottom(plKey exitBottom) { fExitBottom = std::move(exitBottom); }

    /** Sets the plSceneNode for this ladder's top entry seekpoint */
    void setTopPos(plKey topPos) { fTopPos = std::move(topPos); }

    /** Sets the plSceneNode for this ladder's bottom entry seekpoint */
    void setBottomPos(plKey bottomPos) { fBottomPos = std::move(bottomPos); }
};

#endif
