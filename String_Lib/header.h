#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include "source.cpp"

int size_tmy_strlen(const char *s);
int my_strcmp(const char *a, const char *b);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
char *my_strchr(const char *s, int c);
char *my_strstr(const char *haystack, const char *needle);
int checksubstr(const char *str, const char *sub);
int my_strstr_index(const char *haystack, const char *needle);
void reverse_inplace(char *s);
int is_palindrome(const char *s);
int count_words(const char *s);
void tokenizer(const char *str);
char *trail_spaces(char *a);
int find_occur(const char *s, const char *word);
char *replace_key_value(char *str, const char *obj);

#endif