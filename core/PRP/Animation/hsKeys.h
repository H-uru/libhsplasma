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

#ifndef _HSKEYS_H
#define _HSKEYS_H

#include "Math/hsMatrix33.h"
#include "Math/hsMatrix44.h"
#include "Math/hsAffineParts.h"

struct PLASMA_DLL hsKeyFrame
{
    enum
    {
        kUruUnknown    = 0x1,
        kBezController = 0x2
    };

    enum
    {
        kUnknownKeyFrame, kPoint3KeyFrame, kBezPoint3KeyFrame, kScalarKeyFrame,
        kBezScalarKeyFrame, kScaleKeyFrame, kBezScaleKeyFrame, kQuatKeyFrame,
        kCompressedQuatKeyFrame32, kCompressedQuatKeyFrame64, k3dsMaxKeyFrame,
        kMatrix33KeyFrame, kMatrix44KeyFrame
    };
    static const char* TypeNames[];

protected:
    unsigned int fFlags, fFrame, fType;
    float fFrameTime;

public:
    hsKeyFrame() { }
    virtual ~hsKeyFrame() { }

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc) = 0;
    virtual void prcParse(const pfPrcTag* tag) = 0;

    virtual hsKeyFrame& operator=(const hsKeyFrame& rhs);

    unsigned int getType() const { return fType; }
    unsigned int getFrame() const { return fFrame; }
    float getFrameTime() const { return fFrameTime; }

    void setType(unsigned int type) { fType = type; }
    void setFrame(unsigned int frame);
    void setFrameTime(float frame);
};

struct PLASMA_DLL hsPoint3Key : public hsKeyFrame
{
    hsVector3 fInTan, fOutTan;
    hsVector3 fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsPoint3Key& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsScalarKey : public hsKeyFrame
{
    float fInTan, fOutTan;
    float fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsScalarKey& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsScaleKey : public hsKeyFrame
{
    hsVector3 fInTan, fOutTan;

    // Folding hsScaleKey and hsScaleValue together:
    hsVector3 fS;
    hsQuat fQ;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsScaleKey& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsQuatKey : public hsKeyFrame
{
    hsQuat fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsQuatKey& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsCompressedQuatKey32 : public hsKeyFrame
{
public:
    enum { kCompQuatNukeX, kCompQuatNukeY, kCompQuatNukeZ, kCompQuatNukeW };

private:
    static const float kOneOverRootTwo;
    static const float k10BitScaleRange;
    unsigned int fData;

public:
    hsQuat getQuat() const;
    void setQuat(const hsQuat& quat, unsigned char format);

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsCompressedQuatKey32& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsCompressedQuatKey64 : public hsKeyFrame
{
public:
    enum { kCompQuatNukeX, kCompQuatNukeY, kCompQuatNukeZ, kCompQuatNukeW };

private:
    static const float kOneOverRootTwo;
    static const float k20BitScaleRange;
    static const float k21BitScaleRange;
    unsigned int fData[2];

public:
    hsQuat getQuat() const;
    void setQuat(const hsQuat& quat, unsigned char format);

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsCompressedQuatKey64& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsG3DSMaxKeyFrame : public hsKeyFrame
{
    hsAffineParts fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsG3DSMaxKeyFrame& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsMatrix33Key : public hsKeyFrame
{
    hsMatrix33 fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsMatrix33Key& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

struct PLASMA_DLL hsMatrix44Key : public hsKeyFrame
{
    hsMatrix44 fValue;

    void read(hsStream* S, unsigned int type) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;
    void prcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void prcParse(const pfPrcTag* tag) HS_OVERRIDE;

    hsMatrix44Key& operator=(const hsKeyFrame& rhs) HS_OVERRIDE;
};

#endif
