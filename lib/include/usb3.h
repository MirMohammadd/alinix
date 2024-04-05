#ifndef _HEISEN_OS_USB3_HPP__
#define _HEISEN_OS_USB3_HPP__

#include "types.h"


#if !defined(__cplusplus)
#define true 1
#define false 0

typedef enum { FALSE=0, TRUE } bool_t;
#endif

#if defined(__cplusplus)

namespace LIBHeisenKernel{
    class USB3{
        public:
            USB3();
            ~USB3();
        
        public :
            void Init();
            void Detect();
         
    };
};

#else 

typedef struct {
    bool initialised;
};

#endif

#endif // _HEISEN_OS_USB3_HPP__