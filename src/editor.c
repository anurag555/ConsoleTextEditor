#include <stdio.h>
#include <string.h>
#include "editor.h"

void initEditor(Editor *e) {
    e->line_count = 0;
}

void push(Stack *s, Editor *e) {
    if (s->top >= STACK_SIZE - 1) return;

    s->top++;
    s->data[s->top].line_count = e->line_count;

    for (int i = 0; i < e->line_count; i++) {
        strcpy(s->data[s->top].lines[i], e->lines[i]);
    }
}

void pop(Stack *s, Editor *e) {
    if (s->top < 0) return;

    e->line_count = s->data[s->top].line_count;

    for (int i = 0; i < e->line_count; i++) {
        strcpy(e->lines[i], s->data[s->top].lines[i]);
    }

    s->top--;
}

void insertLine(Editor *e, int pos, char *text) {
    if (pos < 0 || pos > e->line_count) return;

    for (int i = e->line_count; i > pos; i--) {
        strcpy(e->lines[i], e->lines[i - 1]);
    }

    strcpy(e->lines[pos], text);
    e->line_count++;
}

void deleteLine(Editor *e, int pos) {
    if (pos < 0 || pos >= e->line_count) return;

    for (int i = pos; i < e->line_count - 1; i++) {
        strcpy(e->lines[i], e->lines[i + 1]);
    }

    e->line_count--;
}

void editLine(Editor *e, int pos, char *text) {
    if (pos < 0 || pos >= e->line_count) return;

    strcpy(e->lines[pos], text);
}

void display(Editor *e) {
    printf("\n----- TEXT -----\n");
    for (int i = 0; i < e->line_count; i++) {
        printf("%d: %s", i + 1, e->lines[i]);
    }
    printf("----------------\n");
}