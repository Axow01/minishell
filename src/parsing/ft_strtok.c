
#include "../../includes/minishell.h"

char    *ft_strtok(char *str, const char delim)
{
    static char    *stock;
    char        *output;
    bool        found;

    if (str)
        stock = str;
    output = 0;
    found = false;
    while (*stock)
    {
        if (!found && !(*stock == delim))
        {
            found = true;
            output = stock;
        }
        else if (found && *stock == delim)
        {
            *stock = 0;
            stock++;
            break ;
        }
        stock++;
    }
    return (output);
}
