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

#include <math.h>
#include "plUnifiedTime.h"

#ifdef _MSC_VER
int gettimeofday(struct timeval* tv, void* tz)
{
    FILETIME ft;

    if (!tv)
        return -1;
    GetSystemTimeAsFileTime(&ft);

    unsigned __int64 tim = ft.dwHighDateTime;
    tim <<= 32;
    tim |= ft.dwLowDateTime;

    tim /= 10;  // Windows stores time as 100 nsec
    tim -= 11644473600000000ULL;    // Windows epoch -> UNIX epoch
    tv->tv_sec  = (long)(tim / 1000000L);
    tv->tv_usec = (long)(tim % 1000000L);

    return 0;
}
#endif

int plUnifiedTime::fLocalTimeZoneOffset = 0;

plUnifiedTime::plUnifiedTime(const timeval& tv)
{
    fMode = kLocal;
    fSecs = tv.tv_sec;
    fMicros = tv.tv_usec;
}

plUnifiedTime::plUnifiedTime(double time)
{
    setSecsDouble(time);
}

plUnifiedTime::plUnifiedTime(time_t time)
{
    fSecs = time;
    fMicros = 0;
    fMode = kLocal;
}

plUnifiedTime::plUnifiedTime(int year, int month, int day, int hour, int min,
                             int sec, unsigned int usec, bool dst)
{
    fMode = kLocal;
    setTime(year, month, day, hour, min, sec, usec, dst);
}

plUnifiedTime::plUnifiedTime(tm* time)
{
    fMode = kLocal;
    fSecs = mktime(time);
}

plUnifiedTime::plUnifiedTime(Mode mode, const char* buf, const char* fmt)
{
    fMode = mode;
    fromString(buf, fmt);
}

plUnifiedTime plUnifiedTime::CurrentTime()
{
    plUnifiedTime time;
    timeval tv;
    gettimeofday(&tv, nullptr);
    time.fMode = kLocal;
    time.fSecs = tv.tv_sec;
    time.fMicros = tv.tv_usec;
    return time;
}

plUnifiedTime plUnifiedTime::FromString(const char* buf, const char* fmt)
{
#ifdef _WIN32
    throw hsNotImplementedException(__FILE__, __LINE__, "strptime");
#else
    tm* result = nullptr;
    strptime(buf, fmt, result);
    return plUnifiedTime(result);
#endif
}

plUnifiedTime& plUnifiedTime::operator=(const timeval& time)
{
    fSecs = time.tv_sec;
    fMicros = time.tv_usec;
    fMode = kLocal;
    return *this;
}

plUnifiedTime& plUnifiedTime::operator=(tm* time)
{
    fSecs = mktime(time);
    fMode = kLocal;
    return *this;
}

plUnifiedTime& plUnifiedTime::operator=(time_t secs)
{
    fSecs = secs;
    fMicros = 0;
    fMode = kLocal;
    return *this;
}

plUnifiedTime& plUnifiedTime::operator+=(const plUnifiedTime& other)
{
    fMicros += other.fMicros;
    if (fMicros > 1000000) {
        fSecs++;
        fMicros -= 1000000;
    }
    fSecs += other.fSecs;
    return *this;
}

plUnifiedTime& plUnifiedTime::operator-=(const plUnifiedTime& other)
{
    if (fMicros <= other.fMicros) {
        fSecs--;
        fMicros += 1000000;
    }
    fMicros -= other.fMicros;
    fSecs -= other.fSecs;
    return *this;
}

bool plUnifiedTime::operator==(const plUnifiedTime& other)
{
    return (fSecs == other.fSecs && fMicros == other.fMicros);
}

bool plUnifiedTime::operator!=(const plUnifiedTime& other)
{
    return (fSecs != other.fSecs || fMicros != other.fMicros);
}

bool plUnifiedTime::operator<(const plUnifiedTime& other)
{
    if (fSecs < other.fSecs)
        return true;
    if (fSecs > other.fSecs)
        return false;
    return (fMicros < other.fMicros);
}

bool plUnifiedTime::operator>(const plUnifiedTime& other)
{
    if (fSecs > other.fSecs)
        return true;
    if (fSecs < other.fSecs)
        return false;
    return (fMicros > other.fMicros);
}

bool plUnifiedTime::operator<=(const plUnifiedTime& other)
{
    if (fSecs < other.fSecs)
        return true;
    if (fSecs == other.fSecs)
        return (fMicros <= other.fMicros);
    return false;
}

bool plUnifiedTime::operator>=(const plUnifiedTime& other)
{
    if (fSecs > other.fSecs)
        return true;
    if (fSecs == other.fSecs)
        return (fMicros >= other.fMicros);
    return false;
}

plUnifiedTime::operator timeval()
{
    timeval tval;
    tval.tv_sec = fSecs;
    tval.tv_usec = fMicros;
    return tval;
}

double plUnifiedTime::getSecsDouble() const
{
    return (double)fSecs + ((double)fMicros / 1000000.0);
}

void plUnifiedTime::getTime(int& year, int& month, int& day, int& hour,
                            int& minute, int& second) const
{
    tm* time = IGetTime(&fSecs);
    year = time->tm_year + 1900;
    month = time->tm_mon + 1;
    day = time->tm_mday;
    hour = time->tm_hour;
    minute = time->tm_min;
    second = time->tm_sec;
}

void plUnifiedTime::setSecsDouble(double secs)
{
    double ipart, fpart;
    fpart = modf(secs, &ipart);
    fSecs = (unsigned int)ipart;
    fMicros = (unsigned int)(fpart * 1000000.0);
}

void plUnifiedTime::setGMTime(int year, int month, int day, int hour, int minute,
                              int second, unsigned int usec, bool dst)
{
    setTime(year, month, day, hour, minute, second, usec, dst);
    toGMT();
}

void plUnifiedTime::setTime(int year, int month, int day, int hour, int minute,
                            int second, unsigned int usec, bool dst)
{
    tm time;
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;
    time.tm_isdst = dst;
    fSecs = mktime(&time);
    fMicros = usec;
    fMode = kLocal;
}

void plUnifiedTime::read(hsStream* S)
{
    fSecs = S->readInt();
    fMicros = S->readInt();
}

void plUnifiedTime::write(hsStream* S)
{
    S->writeInt(fSecs);
    S->writeInt(fMicros);
}

void plUnifiedTime::prcWrite(pfPrcHelper* prc)
{
    int year, month, day, hour, minute, second;
    getTime(year, month, day, hour, minute, second);

    if (atEpoch()) {
        prc->startTag("plUnifiedTime");
        prc->writeParam("AtEpoch", true);
        prc->endTag(true);
    } else {
        prc->startTag("plUnifiedTime");
        prc->writeParam("year", year);
        prc->writeParam("month", month);
        prc->writeParam("day", day);
        prc->writeParam("hour", hour);
        prc->writeParam("minute", minute);
        prc->writeParam("second", second);
        prc->writeParam("microsecond", fMicros);
        prc->writeParam("Mode", (fMode == kGMT) ? "GMT" : "Local");
        prc->endTag(true);
    }
}

void plUnifiedTime::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plUnifiedTime")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (tag->getParam("AtEpoch", "False").to_bool()) {
        fSecs = 0;
        fMicros = 0;
    } else {
        int year, month, day, hour, minute, second;
        year = tag->getParam("year", "0").to_int();
        month = tag->getParam("month", "0").to_int();
        day = tag->getParam("day", "0").to_int();
        hour = tag->getParam("hour", "0").to_int();
        minute = tag->getParam("minute", "0").to_int();
        second = tag->getParam("second", "0").to_int();
        fMicros = tag->getParam("microsecond", "0").to_int();
        ST::string mode = tag->getParam("Mode", "GMT");
        if (mode.compare_i("local") == 0)
            setTime(year, month, day, hour, minute, second, fMicros, false);
        else
            setGMTime(year, month, day, hour, minute, second, fMicros, false);
    }
}

ST::string plUnifiedTime::format(const char* fmt)
{
    char buf[256];
    strftime(buf, 256, fmt, IGetTime(&fSecs));
    return buf;
}

void plUnifiedTime::toGMT()
{
    if (fMode != kGMT) {
        fSecs -= IGetLocalTimeZoneOffset();
        fMode = kGMT;
    }
}

void plUnifiedTime::toLocal()
{
    if (fMode != kLocal) {
        fSecs += IGetLocalTimeZoneOffset();
        fMode = kLocal;
    }
}

int plUnifiedTime::IGetLocalTimeZoneOffset()
{
    static bool haveOffset = false;
    if (!haveOffset) {
        time_t secs = time(nullptr);
        fLocalTimeZoneOffset = (unsigned int)difftime(mktime(gmtime(&secs)), secs);
    }
    return fLocalTimeZoneOffset;
}

tm* plUnifiedTime::IGetTime(const time_t* secs) const
{
    tm* time = (fMode == kGMT) ? gmtime(secs) : localtime(secs);
    time->tm_isdst = -1;
    return time;
}

plUnifiedTime operator+(const plUnifiedTime& left, const plUnifiedTime& right)
{
    plUnifiedTime result = left;
    result += right;
    return result;
}

plUnifiedTime operator-(const plUnifiedTime& left, const plUnifiedTime& right)
{
    plUnifiedTime result = left;
    result -= right;
    return result;
}
