#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file.mis>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }

    my_stack_t stack = {0};
    stack_init(&stack);

    const char *delim = " ;,\t\n";

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, f) != EOF)
    {
        char *comment = strchr(line, ';');
        if (comment != NULL)
            *comment = '\0';
        if (line[0] == ';' || line[0] == '\n')
            continue;
        char *tok = strtok(line, delim);
        while (tok != NULL)
        {

            parse_token(&stack, tok);
            // fprintf(stdout, "%s\n", tok);
            tok = strtok(NULL, delim);
        }
    }
    free(line);

    stack_clear(&stack);

    fclose(f);
    return 0;
}