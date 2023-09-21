#include <string.h>
#include <stdio.h>
#include "../../includes/parsing.h"


void teststrtok(void)
{
    char *line = "ls -la | wc -l > outfile >> bobfile";
    char *new = ft_strtok(line, '>');

    printf("test : %s\n", new);
}