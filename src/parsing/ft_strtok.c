
#include "../../includes/minishell.h"

char *ft_strtok(char *str)
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
        if (!found && *stock != '|')
        {
            found = true;
            output = stock;
        }
        if (*stock == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (*stock == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        if (found && *stock == '|' && !in_double_quote && !in_single_quote)
        {
            *stock = '\0';
            stock++;
            break;
        }
        stock++;
    }
    return output;
}

char *ft_strtok_redirect(char *str)
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
        if (!found && *stock != '>' && *stock != '<')
        {
            found = true;
            output = stock;
        }
        
        if (*stock == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (*stock == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;

        if (found && !in_double_quote && !in_single_quote &&
            ((*stock == '>' && *(stock + 1) != '>') ||
             (*stock == '<' && *(stock + 1) != '<') ||
             (ft_strncmp(stock, ">>", 2) == 0) ||
             (ft_strncmp(stock, "<<", 2) == 0)))
        {
            *stock = '\0';
            if ((*(stock + 1) == '>' && *stock == '>') ||
                (*(stock + 1) == '<' && *stock == '<'))
                stock += 2;
            else
                stock++;
            break;
        }
        stock++;
    }
    return output;
}
