#ifndef DEBUG_H
#define DEBUG_H

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif
