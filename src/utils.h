#ifndef __UTILS_H__
#define __UTILS_H__

/*
 *  utils.h
 */

/*
 *  General C utilities
 */

/*
 *  Constants taken from platformio.ini
 *  or defined elsewhere
 */

/*
    DEBUG: if  0, debug is disabled, else enabled
*/

#if DEBUG
#define debprint(x) x
#else
#define debprint(x)
#endif  //  DEBUG

#endif  // __UTILS_H__
