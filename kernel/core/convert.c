#include <alinix/convert.h>


StringToInt(char* string)
{
    int result = 0;
    unsigned int digit;
    int sign;

    while (IsSpace(*string)) {
        string += 1;
    }

    /*
    * Check for a sign.
    */

    if (*string == '-') {
        sign = 1;
        string += 1;
    } else {
        sign = 0;
        if (*string == '+') {
            string += 1;
        }
    }

    for ( ; ; string += 1) {
        digit = *string - '0';
        if (digit > 9) {
            break;
        }
        result = (10*result) + digit;
    }

    if (sign) {
        return -result;
    }
    return result;
}

int Isspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}