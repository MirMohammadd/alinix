/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file string.h

 */
#ifndef STRING_H
#define STRING_H

#include "../types.h"

void strcpy(char *str, char *format);
void strncpy(char *str, char *format, size_t len);
int strcmp(char *str1, char *str2);
int strncmp(char *str1, char *str2, size_t len);
void memset(void *start, uint32_t val, size_t len);
void memcpy(void *dest, void *src, int size);
void itoa(int val, char *str, int base);
int atoi(char *str);
int strlen(char *str);
char char_at(char *str, int pos);
void to_uppercase(char *str, char *format);
void to_lowercase(char *str, char *format);
char toupper(char c);
char tolower(char c);
int vsprintf(char *str, char *format, va_list args);
char *strchr(char *str, int c);
char *strcat(char *dest, char *src);

#endif