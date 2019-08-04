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

class PLASMA_DLL plATCAnim : public plAGAnim
{
    CREATABLE(plATCAnim, kATCAnim, plAGAnim)

public:
    typedef std::map<ST::string, float> marker_t;
    typedef std::map<ST::string, std::pair<float, float>> loop_t;

protected:
    float fInitial, fLoopStart, fLoopEnd;
    bool fAutoStart, fLoop;
    unsigned char fEaseInType, fEaseOutType;
    float fEaseInLength, fEaseInMin, fEaseInMax;
    float fEaseOutLength, fEaseOutMin, fEaseOutMax;
    marker_t fMarkers;
    loop_t fLoops;
    std::vector<float> fStopPoints;

public:
    plATCAnim()
        : fInitial(), fLoopStart(), fLoopEnd(), fAutoStart(), fLoop(),
          fEaseInType(), fEaseOutType() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

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

    float getMarker(const ST::string& key) const;
    std::pair<float, float> getLoop(const ST::string& key) const;
    const std::vector<float>& getStops() const { return fStopPoints; }

    void setInitial(float init) { fInitial = init; }
    void setLoopStart(float start) { fLoopStart = start; }
    void setLoopEnd(float end) { fLoopEnd = end; }
    void setAutoStart(bool autoStart) { fAutoStart = autoStart; }
    void setDoLoop(bool loop) { fLoop = loop; }
    void setEaseInType(unsigned char type) { fEaseInType = type; }
    void setEaseOutType(unsigned char type) { fEaseOutType = type; }
    void setEaseInLength(float length) { fEaseInLength = length; }
    void setEaseInMin(float min) { fEaseInMin = min; }
    void setEaseInMax(float max) { fEaseInMax = max; }
    void setEaseOutLength(float length) { fEaseOutLength = length; }
    void setEaseOutMin(float min) { fEaseOutMin = min; }
    void setEaseOutMax(float max) { fEaseOutMax = max; }

    void setEaseInParams(float length, float min, float max)
    {
        fEaseInLength = length;
        fEaseInMin = min;
        fEaseInMax = max;
    }

    void setEaseOutParams(float length, float min, float max)
    {
        fEaseOutLength = length;
        fEaseOutMin = min;
        fEaseOutMax = max;
    }

    void setMarker(const ST::string& key, float value) { fMarkers[key] = value; }

    void setLoop(const ST::string& key, float start, float end)
    {
        fLoops[key] = std::make_pair(start, end);
    }

    void setStops(const std::vector<float>& stops) { fStopPoints = stops; }
};


class PLASMA_DLL plEmoteAnim : public plATCAnim
{
    CREATABLE(plEmoteAnim, kEmoteAnim, plATCAnim)

protected:
    plAGAnim::BodyUsage fBodyUsage;
    float fFadeIn, fFadeOut;

public:
    plEmoteAnim() : fBodyUsage(plAGAnim::kBodyUnknown) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plAGAnim::BodyUsage getBodyUsage() const { return fBodyUsage; }
    float getFadeIn() const { return fFadeIn; }
    float getFadeOut() const { return fFadeOut; }

    void setBodyUsage(plAGAnim::BodyUsage usage) { fBodyUsage = usage; }
    void setFadeIn(float fade) { fFadeIn = fade; }
    void setFadeOut(float fade) { fFadeOut = fade; }
};

class PLASMA_DLL plAGAnimBink : public plATCAnim
{
    CREATABLE(plAGAnimBink, kAGAnimBink, plATCAnim)

protected:
    ST::string fBinkFilename, fSgtFilename, fSubtitleId;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getBinkFilename() const { return fBinkFilename; }
    ST::string getSgtFilename() const { return fSgtFilename; }
    ST::string getSubtitleId() const { return fSubtitleId; }

    void setBinkFilename(const ST::string& filename) { fBinkFilename = filename; }
    void setSgtFilename(const ST::string& filename) { fSgtFilename = filename; }
    void setSubtitleId(const ST::string& id) { fSubtitleId = id; }
};

#endif
