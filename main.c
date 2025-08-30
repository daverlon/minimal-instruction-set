#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

static int ACC;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.mis>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }

    char *line = NULL;
    size_t *size = NULL;
    while (getline(&line, size, f) != EOF) {
        fprintf(stdout, "Line: %s\n", line);
        free(line);
    }
    

    fclose(f);
    return 0;
}