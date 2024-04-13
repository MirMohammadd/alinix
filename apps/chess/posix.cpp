#include <cerrno>
#include <cstdio> // REMOVE ME?
#include <cstdlib>
#include <cstring>
#include <ctime>

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__)
#include <windows.h>

#else

#  include <sys/resource.h>
#  include <sys/time.h>
#  include <sys/types.h>
#  include <unistd.h>
#endif

#include "posix.h"
#include "util.h"
// #include "components.h"