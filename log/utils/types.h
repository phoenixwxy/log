#ifndef __PHOENIX_HEADER_TYPES_H
#define __PHOENIX_HEADER_TYPES_H


#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef int             BOOL;
typedef char            CHAR;
typedef uint8_t         BYTE;
typedef unsigned char   UCHAR;
typedef short           SHORT;
typedef unsigned short  USHORT;
typedef int             INT;
typedef unsigned int    UINT;
typedef float           FLOAT;

typedef uint8_t         UINT8;
typedef int8_t          INT8;
typedef uint16_t        UINT16;
typedef int16_t         INT16;
typedef uint32_t        UINT32;
typedef int32_t         INT32;
typedef uint64_t        UINT64;
typedef int64_t         INT64;

typedef max_align_t     MAXALIGN_T;
typedef size_t          SIZE_T;
typedef void            VOID;

typedef unsigned char           Word8u;
typedef short unsigned int      Word16u;
typedef short signed int        Word16;
typedef unsigned int            Word32u;
typedef signed int              Word32;
typedef long long signed int    Word64;
typedef long long unsigned int  Word64u;

#if !defined (TRUE)
#define TRUE                1
#endif // !defined (TRUE)

#if !defined (FALSE)
#define FALSE               0
#endif // !defined (FALSE)

#ifdef __cplusplus
}
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Result Codes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The result code type to be returned from functions. Must match ordering and size PResultStrings.
typedef INT32 PResult;

static const PResult PResultSuccess           = 0;    ///< Operation was successful
static const PResult PResultEFailed           = 1;    ///< Operation encountered unspecified error
static const PResult PResultEUnsupported      = 2;    ///< Operation is not supported
static const PResult PResultEInvalidState     = 3;    ///< Invalid state
static const PResult PResultEInvalidArg       = 4;    ///< Invalid argument
static const PResult PResultEInvalidPointer   = 5;    ///< Invalid memory pointer
static const PResult PResultENoSuch           = 6;    ///< No such item exists or is valid
static const PResult PResultEOutOfBounds      = 7;    ///< Out of bounds
static const PResult PResultENoMemory         = 8;    ///< Out of memory
static const PResult PResultETimeout          = 9;    ///< Operation timed out
static const PResult PResultENoMore           = 10;   ///< No more items available
static const PResult PResultENeedMore         = 11;   ///< Operation requires more
static const PResult PResultEExists           = 12;   ///< Item exists
static const PResult PResultEPrivLevel        = 13;   ///< Privileges are insufficient for requested operation
static const PResult PResultEResource         = 14;   ///< Resources are insufficient for requested operation
static const PResult PResultEUnableToLoad     = 15;   ///< Unable to load library/object
static const PResult PResultEInProgress       = 16;   ///< Operation is already in progress
static const PResult PResultETryAgain         = 17;   ///< Could not complete request; try again
static const PResult PResultEBusy             = 18;   ///< Device or resource busy
static const PResult PResultEReentered        = 19;   ///< Non re-entrant API re-entered
static const PResult PResultEReadOnly         = 20;   ///< Cannot change read-only object or parameter
static const PResult PResultEOverflow         = 21;   ///< Value too large for defined data type
static const PResult PResultEOutOfDomain      = 22;   ///< Math argument or result out of domain
static const PResult PResultEInterrupted      = 23;   ///< Waitable call is interrupted
static const PResult PResultEWouldBlock       = 24;   ///< Operation would block
static const PResult PResultETooManyUsers     = 25;   ///< Too many users
static const PResult PResultENotImplemented   = 26;   ///< Function or method is not implemented
static const PResult PResultEDisabled         = 27;   ///< Feature disabled (by an override for example)
static const PResult PResultECancelledRequest = 28;   ///< Flush in progress

// Increment the count below if adding additional result codes.
static const PResult PResultCount             = 29;   ///< The number of result codes. Not to be used.

// PResult max size to be used, for module specific errors in PResultExt
static const PResult PResultMax = 255;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OS Agnostic Primitive Data Type Abstractions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned int    BIT;
typedef double          DOUBLE;

typedef intptr_t        INTPTR_T;
typedef uintptr_t       UINTPTR_T;
typedef ptrdiff_t       PTRDIFF_T;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timing Types
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Time structure
struct PTime
{
    UINT32  seconds;                    ///< Time in whole seconds
    UINT32  nanoSeconds;                ///< Fractional nanoseconds
};

/// @brief Date time structure
struct PDateTime
{
    UINT32  seconds;                    ///< Seconds after the minute 0-61*
    UINT32  microseconds;               ///< Microseconds 0-999999
    UINT32  minutes;                    ///< Time in minutes 0-59
    UINT32  hours;                      ///< Time in hours 0-23
    UINT32  dayOfMonth;                 ///< Day of month 1-31
    UINT32  month;                      ///< Months since January 0-11, where 0 is January
    UINT32  year;                       ///< Year since 1900
    UINT32  weekday;                    ///< Day of week 0-6
    UINT32  yearday;                    ///< Day of year 0-365
    UINT32  dayLightSavingTimeFlag;     ///< Day light saving time flag
};

#endif