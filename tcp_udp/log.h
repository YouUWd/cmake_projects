#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>

#define log(fmt, arg...)  { printf(fmt, ##arg); }
#define log_error(fmt, arg...)  { fprintf(stderr, fmt, ##arg); }
#define log_debug(verbose, fmt, arg...)  {      \
    if( (verbose) > 0) {                        \
        printf(fmt, ##arg);                     \
        printf("\n");                     \
    }                                           \
}

#endif
