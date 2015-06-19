/** this file is only made to fix compilation issues */

#include "libft.h"

void	__ms_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	vsnprintf(str, size, format, ap);
}
