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

    unsigned int getSecs();
    unsigned int getMicros();
    double getSecsDouble();

    int getYear();
    int getMonth();
    int getDay();
    int getDayOfWeek();
    int getHour();
    int getMinute();
    int getSecond();
    void getTime(int& year, int& month, int& day, int& hour, int& minute, int& second);
    tm* getTm();

    void setSecs(unsigned int secs);
    void setMicros(unsigned int micros);
    void setMode(Mode mode);
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
    
    bool atEpoch();
    void toEpoch();
    void toGMT();
    void toLocal();
    void toCurrentTime();

protected:
    static int IGetLocalTimeZoneOffset();
    tm* IGetTime(time_t* secs);
};

plUnifiedTime operator+(const plUnifiedTime& left, const plUnifiedTime& right);
plUnifiedTime operator-(const plUnifiedTime& left, const plUnifiedTime& right);

#endif
