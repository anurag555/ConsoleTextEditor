#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"
#include "file.h"

static void drain_stdin_to_newline(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Read at most size-1 chars; if line was longer, consume rest so next read is a fresh line. */
static int read_line_into(char *buf, size_t size) {
    if (size == 0 || !fgets(buf, (int)size, stdin))
        return 0;
    size_t n = strlen(buf);
    if (n == 0)
        return 1;
    if (buf[n - 1] != '\n' && buf[n - 1] != '\r')
        drain_stdin_to_newline();
    buf[strcspn(buf, "\r\n")] = 0;
    return 1;
}

static void trim_inplace(char *s) {
    char *start = s;
    while (*start == ' ' || *start == '\t')
        start++;
    if (start != s)
        memmove(s, start, strlen(start) + 1);
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t'))
        n--;
    s[n] = 0;
}

static int read_line_number(const char *prompt, int *out) {
    char buf[64];
    printf("%s", prompt);
    fflush(stdout);
    if (!read_line_into(buf, sizeof(buf)))
        return 0;
    return sscanf(buf, "%d", out) == 1;
}

int main(int argc, char *argv[]) {
    Editor editor;
    Stack *undoStack = malloc(sizeof(Stack));
    Stack *redoStack = malloc(sizeof(Stack));
    if (!undoStack || !redoStack) {
        fprintf(stderr, "Out of memory.\n");
        free(undoStack);
        free(redoStack);
        return 1;
    }
    undoStack->top = -1;
    redoStack->top = -1;

    initEditor(&editor);

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        free(undoStack);
        free(redoStack);
        return 1;
    }

    char *filename = argv[1];
    loadFile(&editor, filename);

    char cmd[128], text[MAX_LEN];
    int line;

    while (1) {
        display(&editor);

        printf("Commands: insert delete edit undo redo save exit\n> ");
        fflush(stdout);

        if (!read_line_into(cmd, sizeof(cmd)))
            break;
        trim_inplace(cmd);

        if (strcmp(cmd, "insert") == 0) {
            if (!read_line_number("Line number: ", &line)) {
                printf("Invalid line number.\n");
                continue;
            }
            if (line < 1 || line > editor.line_count + 1) {
                printf("Line must be between 1 and %d (insert).\n", editor.line_count + 1);
                continue;
            }
            printf("Text: ");
            fflush(stdout);
            if (!read_line_into(text, sizeof(text))) {
                printf("Input error.\n");
                continue;
            }
            push(undoStack, &editor);
            redoStack->top = -1;
            insertLine(&editor, line - 1, text);
        }

        else if (strcmp(cmd, "delete") == 0) {
            if (editor.line_count == 0) {
                printf("Nothing to delete.\n");
                continue;
            }
            if (!read_line_number("Line number: ", &line)) {
                printf("Invalid line number.\n");
                continue;
            }
            if (line < 1 || line > editor.line_count) {
                printf("Line must be between 1 and %d.\n", editor.line_count);
                continue;
            }
            push(undoStack, &editor);
            redoStack->top = -1;
            deleteLine(&editor, line - 1);
        }

        else if (strcmp(cmd, "edit") == 0) {
            if (editor.line_count == 0) {
                printf("No lines to edit.\n");
                continue;
            }
            if (!read_line_number("Line number: ", &line)) {
                printf("Invalid line number.\n");
                continue;
            }
            if (line < 1 || line > editor.line_count) {
                printf("Line must be between 1 and %d.\n", editor.line_count);
                continue;
            }
            printf("New text: ");
            fflush(stdout);
            if (!read_line_into(text, sizeof(text))) {
                printf("Input error.\n");
                continue;
            }
            push(undoStack, &editor);
            redoStack->top = -1;
            editLine(&editor, line - 1, text);
        }

        else if (strcmp(cmd, "undo") == 0) {
            if (undoStack->top < 0) {
                printf("Nothing to undo.\n");
                continue;
            }
            push(redoStack, &editor);
            pop(undoStack, &editor);
        }

        else if (strcmp(cmd, "redo") == 0) {
            if (redoStack->top < 0) {
                printf("Nothing to redo.\n");
                continue;
            }
            push(undoStack, &editor);
            pop(redoStack, &editor);
        }

        else if (strcmp(cmd, "save") == 0) {
            saveFile(&editor, filename);
        }

        else if (strcmp(cmd, "exit") == 0) {
            break;
        }

        else if (cmd[0] != '\0') {
            printf("Unknown command \"%s\". Type insert, delete, edit, undo, redo, save, or exit.\n", cmd);
        }
    }

    free(undoStack);
    free(redoStack);
    return 0;
}
