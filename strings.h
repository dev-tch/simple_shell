#ifndef STRINGS_H
#define STRINGS_H
char *_strdup(const char *str);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int is_space(char c);
int is_empty(char  *str);
char *_strchr(char *s, char c);
char *split(char *str, char *separators);
#endif
