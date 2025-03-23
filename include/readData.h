//
// Created by lucas on 23/03/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef READDATA_H
#define READDATA_H

const int MAX_LINE_LENGTH = 100;

void read_line(FILE *file, int line_index, const char *mask, ...);

void interative_mode(void);

void file_mode(void);

#endif //READDATA_H
