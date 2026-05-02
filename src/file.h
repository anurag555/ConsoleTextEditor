#ifndef FILE_H
#define FILE_H

#include "editor.h"

void loadFile(Editor *e, char *filename);
void saveFile(Editor *e, char *filename);

#endif