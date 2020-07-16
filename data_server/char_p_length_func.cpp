/**
 * Simple function for returning the length of a char* function, null terminated 
 */
#include <cstddef>
size_t char_p_len(char *msg)
{
	size_t len = 0;
	for (; *msg != '\0'; msg = msg + 1) 
		len++;

	return len;
}
