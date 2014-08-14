/*!
 * @file lsd_assert.hpp
 *
 * @author David Losteiner
 * @date 2014.08.13.
 *
 * Assertion macros are defined here.
 *
 */

#include <iostream>
#include <cstdlib>     /* exit, EXIT_FAILURE */


#ifndef NDEBUG
#   define LSD_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "LSD Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            exit(EXIT_FAILURE); \
        } \
    } while (false)
#else
#   define LSD_ASSERT(condition, message) do { } while (false)
#endif
