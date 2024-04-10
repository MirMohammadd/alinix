#ifndef CACTUSOS__COMMON__CONVERT_H
#define CACTUSOS__COMMON__CONVERT_H

#include <common/types.h>
#include <common/memoryoperations.h>



namespace HeisenOs
{
    namespace common
    {
        /**
         * @brief A set of static functions that will convert the data types from one representation to another.
        */
        class Convert
        {
        public:
        // -------------------------------------------------------------
            // A set of static functions that will convert the data types from one representation to another.
            static char* IntToString(int i);
            static char* IntToString32(uint32_t i);

            static char* IntToHexString(common::uint8_t w);
            static char* IntToHexString(common::uint16_t w);
            static char* IntToHexString(common::uint32_t w);

            static int StringToInt(char* string);
            static uint32_t HexToInt(char* string);
        // -------------------------------------------------------------
        };
    }
}

#endif