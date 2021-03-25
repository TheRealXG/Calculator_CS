#include "memcpy.h"
/* memcpy definition taken from:
 * https://github.com/gcc-mirror/gcc/blob/master/libgcc/memcpy.c
 */

/* Public domain.  */
void *
memcpy (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}
