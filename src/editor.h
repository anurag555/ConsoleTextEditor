#ifndef EDITOR_H
#define EDITOR_H

#define MAX_LINES 1000
#define MAX_LEN 256
#define STACK_SIZE 100

typedef struct {
    char lines[MAX_LINES][MAX_LEN];
    int line_count;
} Editor;

typedef struct {
    char lines[MAX_LINES][MAX_LEN];
    int line_count;
} State;

typedef struct {
    State data[STACK_SIZE];
    int top;
} Stack;

void initEditor(Editor *e);
void insertLine(Editor *e, int pos, char *text);
void deleteLine(Editor *e, int pos);
void editLine(Editor *e, int pos, char *text);
void display(Editor *e);

void push(Stack *s, Editor *e);
void pop(Stack *s, Editor *e);

#endif