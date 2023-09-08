#include <string.h>
#include <stdio.h>


void teststrtok(void)
{
    char *line = "ls -la | wc -l > outfile >> bobfile";
    printf("test : %s\n", strtok(line, ">"));
}