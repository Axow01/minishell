#include "minishell.h"

char *heredoc_parsing(char *line, char *delimiter)
{
    size_t i;
    
    while (line[i])
    {

        i++;
    }
    
    mms_free(line);
}
bool heredoc(char *delimiter)
{
    char *line;
    char *new;

    while (true)
    {

        line = readline(">");
        if (!line)
            return (false);
        mms_add_ptr(line);
        new = heredoc_parsing(line, delimiter);
        if (!new)
            return (false);
    }
    return (true);
}