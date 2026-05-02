#include <stdio.h>
#include "editor.h"

void loadFile(Editor *e, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        insertLine(e, e->line_count, buffer);
    }

    fclose(fp);
}

void saveFile(Editor *e, char *filename) {
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < e->line_count; i++) {
        fputs(e->lines[i], fp);
    }

    fclose(fp);
    printf("File saved successfully!\n");
}