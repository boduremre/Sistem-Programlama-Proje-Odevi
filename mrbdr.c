#include "mrbdr.h"

void remove_str_character(char *s, char delimeter)
{
    const char *d = s;
    do
    {
        while (*d == delimeter)
        {
            ++d;
        }
    } while (*s++ = *d++);
}

// https://stackoverflow.com/questions/23170096/how-to-count-single-or-double-quotes
int getNumPipe(const char *cmd, char match)
{
    int num = 0;
    while (*cmd != '\0')
    {
        if (*cmd == match)
            num++;
        cmd++;
    }
    return num;
}