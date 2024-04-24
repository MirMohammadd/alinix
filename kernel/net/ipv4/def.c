#include <alinix/types.h>
#include <net/def.h>

uint16_t
lwip_htons(uint16_t n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

uint32_t
lwip_ntohl(uint32_t n)
{
  return lwip_htonl(n);
}
