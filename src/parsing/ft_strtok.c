
#include "../../includes/minishell.h"

char *ft_strtok(char *str, const char delim)
{
    static char *stock = NULL;
    char *output = NULL;
    bool found = false;
    bool in_double_quote = false;
    bool in_single_quote = false;

    if (str) 
        stock = str;
    while (stock && *stock)
    {
        if (!found && *stock != delim)
        {
            found = true;
            output = stock;
        }
        if (*stock == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (*stock == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        if (found && *stock == delim && !in_double_quote && !in_single_quote)
        {
            *stock = '\0';
            stock++;
            break;
        }
        stock++;
    }
    return output;
}

char *ft_strtok_2(char *str, const char delim)
{
    static char *stock = NULL;
    char *output = NULL;
    bool found = false;
    bool in_double_quote = false;
    bool in_single_quote = false;

    if (str) 
        stock = str;
    while (stock && *stock)
    {
        if (!found && *stock != delim)
        {
            found = true;
            output = stock;
        }
        if (*stock == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (*stock == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        if (found && *stock == delim && !in_double_quote && !in_single_quote)
        {
            get_redirec()->redirec[get_redirec()->index] = ft_stringf("%c", *stock);
            *stock = '\0';
            stock++;
            break;
        }
        stock++;
    }
    return output;
}
