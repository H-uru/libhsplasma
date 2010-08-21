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

DllStruct hsKeyFrame {
    enum {
        kUruUnknown    = 0x1,
        kBezController = 0x2
    };

    enum {
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

    unsigned int getType() const { return fType; }
    unsigned int getFrame() const { return fFrame; }
    float getFrameTime() const { return fFrameTime; }

    void setType(unsigned int type) { fType = type; }
    void setFrame(unsigned int frame);
    void setFrame(float frame);
};

DllStruct hsPoint3Key : public hsKeyFrame {
    hsVector3 fInTan, fOutTan;
    hsVector3 fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsScalarKey : public hsKeyFrame {
    float fInTan, fOutTan;
    float fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsScaleKey : public hsKeyFrame {
    hsVector3 fInTan, fOutTan;

    // Folding hsScaleKey and hsScaleValue together:
    hsVector3 fS;
    hsQuat fQ;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsQuatKey : public hsKeyFrame {
    hsQuat fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsCompressedQuatKey32 : public hsKeyFrame {
public:
    enum { kCompQuatNukeX, kCompQuatNukeY, kCompQuatNukeZ, kCompQuatNukeW };

private:
    static const float kOneOverRootTwo;
    static const float k10BitScaleRange;
    unsigned int fData;

public:
    hsQuat getQuat() const;
    void setQuat(const hsQuat& quat, unsigned char format);

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsCompressedQuatKey64 : public hsKeyFrame {
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

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsG3DSMaxKeyFrame : public hsKeyFrame {
    hsAffineParts fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsMatrix33Key : public hsKeyFrame {
    hsMatrix33 fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

DllStruct hsMatrix44Key : public hsKeyFrame {
    hsMatrix44 fValue;

    virtual void read(hsStream* S, unsigned int type);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
};

#endif
