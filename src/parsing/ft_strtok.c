
#include "../../includes/minishell.h"


//quote[0] = " "
//quote[1] = ' '
char    *ft_strtok(char *str, const char delim)
{
    static char    *stock;
    char        *output;
    bool        found;
    bool        quote[20];

    if (str)
        stock = str;
    output = 0;
    found = false;
    quote[0] = false;
    quote[1] = false;
    while (*stock)
    {
        if (!found && !(*stock == delim))
        {
            found = true;
            output = stock;
        }
        else if ((!quote[0] && !quote[1]) && *stock == '\"')
            quote[0] = true;
        else if ((!quote[0] && !quote[1]) && *stock == '\'')
            quote[1] = true;
        else if (((found && *stock == delim) && (!quote[0] && !quote[1])))
        {
            *stock = 0;
            stock++;
            break ;
        }
        stock++;
    }
    return (output);
}
