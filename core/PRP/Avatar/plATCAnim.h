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

#ifndef _PLATCANIM_H
#define _PLATCANIM_H

#include "plAGAnim.h"
#include <map>

class PLASMA_DLL plATCAnim : public virtual plAGAnim {
    CREATABLE(plATCAnim, kATCAnim, plAGAnim)

public:
    typedef std::map<plString, float> marker_t;
    typedef std::map<plString, std::pair<float, float> > loop_t;

protected:
    float fInitial, fLoopStart, fLoopEnd;
    bool fAutoStart, fLoop;
    unsigned char fEaseInType, fEaseOutType;
    float fEaseInLength, fEaseInMin, fEaseInMax;
    float fEaseOutLength, fEaseOutMin, fEaseOutMax;
    marker_t fMarkers;
    loop_t fLoops;
    hsTArray<float> fStopPoints;

public:
    plATCAnim();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const marker_t& getMarkers() const { return fMarkers; }
    marker_t& getMarkers() { return fMarkers; }
    const loop_t& getLoops() const { return fLoops; }
    loop_t& getLoops() { return fLoops; }

    float getInitial() const { return fInitial; }
    float getLoopStart() const { return fLoopStart; }
    float getLoopEnd() const { return fLoopEnd; }
    bool getAutoStart() const { return fAutoStart; }
    bool getDoLoop() const { return fLoop; }
    unsigned char getEaseInType() const { return fEaseInType; }
    unsigned char getEaseOutType() const { return fEaseOutType; }
    float getEaseInLength() const { return fEaseInLength; }
    float getEaseInMin() const { return fEaseInMin; }
    float getEaseInMax() const { return fEaseInMax; }
    float getEaseOutLength() const { return fEaseOutLength; }
    float getEaseOutMin() const { return fEaseOutMin; }
    float getEaseOutMax() const { return fEaseOutMax; }

    float getMarker(const plString& key) const;
    std::pair<float, float> getLoop(const plString& key) const;
    const hsTArray<float>& getStops() const { return fStopPoints; }

    void setInitial(float init) { fInitial = init; }
    void setLoopStart(float start) { fLoopStart = start; }
    void setLoopEnd(float end) { fLoopEnd = end; }
    void setAutoStart(bool autoStart) { fAutoStart = autoStart; }
    void setDoLoop(bool loop) { fLoop = loop; }
    void setEaseInType(unsigned char type) { fEaseInType = type; }
    void setEaseOutType(unsigned char type) { fEaseOutType = type; }

    void setEaseInParams(float length, float min, float max)
    { fEaseInLength = length; fEaseInMin = min; fEaseInMax = max; }

    void setEaseOutParams(float length, float min, float max)
    { fEaseOutLength = length; fEaseOutMin = min; fEaseOutMax = max; }

    void setMarker(const plString& key, float value) { fMarkers[key] = value; }

    void setLoop(const plString& key, float start, float end)
    { fLoops[key] = std::pair<float, float>(start, end); }

    void setStops(const hsTArray<float>& stops) { fStopPoints = stops; }
};


class PLASMA_DLL plEmoteAnim : public virtual plATCAnim {
    CREATABLE(plEmoteAnim, kEmoteAnim, plATCAnim)

protected:
    plAGAnim::BodyUsage fBodyUsage;
    float fFadeIn, fFadeOut;

public:
    plEmoteAnim();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAGAnim::BodyUsage getBodyUsage() const { return fBodyUsage; }
    float getFadeIn() const { return fFadeIn; }
    float getFadeOut() const { return fFadeOut; }

    void setBodyUsage(plAGAnim::BodyUsage usage) { fBodyUsage = usage; }
    void setFadeIn(float fade) { fFadeIn = fade; }
    void setFadeOut(float fade) { fFadeOut = fade; }
};

class PLASMA_DLL plAGAnimBink : public plATCAnim {
    CREATABLE(plAGAnimBink, kAGAnimBink, plATCAnim)

protected:
    plString fBinkFilename, fSgtFilename, fSubtitleId;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getBinkFilename() const { return fBinkFilename; }
    plString getSgtFilename() const { return fSgtFilename; }
    plString getSubtitleId() const { return fSubtitleId; }

    void setBinkFilename(const plString& filename) { fBinkFilename = filename; }
    void setSgtFilename(const plString& filename) { fSgtFilename = filename; }
    void setSubtitleId(const plString& id) { fSubtitleId = id; }
};

#endif
