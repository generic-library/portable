/*
 * Public domain
 * sys/time.h compatibility shim
 */

#ifdef _MSC_VER
#if _MSC_VER >= 1900
#include <../ucrt/time.h>
#else
#include <../include/time.h>
#endif
#else
#include_next <time.h>
#endif

#ifdef _WIN32
struct tm *__gmtime_r(const time_t * t, struct tm * tm);
#define gmtime_r(tp, tm) __gmtime_r(tp, tm)
#endif

#ifndef HAVE_TIMEGM
time_t timegm(struct tm *tm);
#endif

#ifndef timespecsub
#define timespecsub(tsp, usp, vsp)                                      \
        do {                                                            \
                (vsp)->tv_sec = (tsp)->tv_sec - (usp)->tv_sec;          \
                (vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec;       \
                if ((vsp)->tv_nsec < 0) {                               \
                        (vsp)->tv_sec--;                                \
                        (vsp)->tv_nsec += 1000000000L;                  \
                }                                                       \
        } while (0)
#endif
