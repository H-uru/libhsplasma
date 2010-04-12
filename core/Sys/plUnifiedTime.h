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

#ifndef _PLUNIFIEDTIME_H
#define _PLUNIFIEDTIME_H

#include <time.h>
#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

// FIX: Windows doesn't have the <sys/time.h> stuff, so let's add it
#ifdef WIN32
extern "C" {
    int gettimeofday(struct timeval* tv, void* tz);
}
#endif

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plUnifiedTime {
public:
    enum Mode { kGMT, kLocal };

protected:
    static int fLocalTimeZoneOffset;

    time_t fSecs;
    unsigned int fMicros;
    Mode fMode;

public:
    plUnifiedTime();
    plUnifiedTime(const plUnifiedTime& other);
    plUnifiedTime(const timeval& tv);
    plUnifiedTime(double time);
    plUnifiedTime(time_t time);
    plUnifiedTime(int year, int month, int day, int hour, int min, int sec,
                  unsigned int usec, bool dst);
    plUnifiedTime(tm* time);
    plUnifiedTime(Mode mode, const char* buf, const char* fmt);

    static plUnifiedTime GetCurrentTime();
    static plUnifiedTime FromString(const char* buf, const char* fmt);

    plUnifiedTime& operator=(const plUnifiedTime& other);
    plUnifiedTime& operator=(const timeval& time);
    plUnifiedTime& operator=(tm* time);
    plUnifiedTime& operator=(time_t secs);
    plUnifiedTime& operator+=(const plUnifiedTime& other);
    plUnifiedTime& operator-=(const plUnifiedTime& other);
    bool operator==(const plUnifiedTime& other);
    bool operator!=(const plUnifiedTime& other);
    bool operator<(const plUnifiedTime& other);
    bool operator>(const plUnifiedTime& other);
    bool operator<=(const plUnifiedTime& other);
    bool operator>=(const plUnifiedTime& other);

    operator timeval();
    operator tm*();

    unsigned int getSecs() const { return fSecs; }
    unsigned int getMicros() const { return fMicros; }
    double getSecsDouble() const;

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getDayOfWeek() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    void getTime(int& year, int& month, int& day, int& hour, int& minute, int& second) const;
    tm* getTm() const;

    void setSecs(unsigned int secs) { fSecs = secs; }
    void setMicros(unsigned int micros) { fMicros = micros; }
    void setMode(Mode mode) { fMode = mode; }
    void setSecsDouble(double secs);

    void setGMTime(int year, int month, int day, int hour, int minute, int second,
                   unsigned int usec, bool dst);
    void setTime(int year, int month, int day, int hour, int minute, int second,
                 unsigned int usec, bool dst);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    plString format(const char* fmt);
    void fromString(const char* buf, const char* fmt);

    bool atEpoch() const { return (fSecs == 0 && fMicros == 0); }
    void toEpoch() { fSecs = 0; fMicros = 0; }
    void toGMT();
    void toLocal();
    void toCurrentTime();

protected:
    static int IGetLocalTimeZoneOffset();
    tm* IGetTime(const time_t* secs) const;
};

plUnifiedTime operator+(const plUnifiedTime& left, const plUnifiedTime& right);
plUnifiedTime operator-(const plUnifiedTime& left, const plUnifiedTime& right);

#endif
