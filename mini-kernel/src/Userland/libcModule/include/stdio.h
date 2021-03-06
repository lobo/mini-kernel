#ifndef _STDIO_H
#define _STDIO_H

#include "stddef.h"
#include <stdarg.h>

#ifndef EOF
#define EOF (-1)
#endif

/* Standard file descriptors. */
#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

typedef struct {
    int fd;
    char lastc;
} FILE;

extern FILE *stdin, *stdout, *stderr;

int putc(int ch, FILE *stream);
int getc(FILE *stream);

int putchar(int ch);
int getchar(void);

int puts(const char *str);

char * gets(char *s, int size);
char * fgets(char *s, int size, FILE *stream);

int printf(const char *fmt, ...);
int fprintf(FILE *f, const char *fmt, ...);
int vfprintf(FILE *f, const char *fmt, va_list ap);

int write(int fd, void *buf, int count);
int read(int fd, void *buf, int count);

#endif
