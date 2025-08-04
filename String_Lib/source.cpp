#include "header.h"
#include <iostream>
using namespace std;

int size_tmy_strlen(const char *s)
{
    size_t i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

int my_strcmp(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return a[i] - b[i];
        }
        i++;
    }
    return a[i] - b[i];
}
int checksubstr(const char *str, const char *sub)
{
    int i = 0;
    while (str[i] != '\0')
    {
        int j = 0;
        int ascii_str = (int)str[i + j] > 91 ? 122 - (int)str[i + j] : 90 - (int)str[i + j];
        int ascii_sub = (int)sub[j] > 91 ? 122 - (int)sub[j] : 90 - (int)sub[j];
        while (sub[j] != '\0' && ascii_str == ascii_sub)
        {
            j++;
            ascii_str = (int)str[i + j] > 91 ? 122 - (int)str[i + j] : 90 - (int)str[i + j];
            ascii_sub = (int)sub[j] > 91 ? 122 - (int)sub[j] : 90 - (int)sub[j];
        }
        if (sub[j] == '\0')
        {
            return 1;
        }
        i++;
    }
    return 0;
}
char *my_strcpy(char *dest, const char *src)
{
    int i = 0;
    while ((dest[i] = src[i]) != '\0')
    {
        i++;
    }
    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    int size = size_tmy_strlen(dest);
    int i = 0;
    while (src[i] != '\0')
    {
        dest[size + i] = src[i];
        i++;
    }
    dest[size + i] = '\0';
    return dest;
}

char *my_strchr(const char *s, int c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return (char *)(s + i);
        }
        i++;
    }
    return nullptr;
}

char *my_strstr(const char *haystack, const char *needle)
{
    if (!*needle)
        return (char *)haystack;
    int i = 0;
    while (haystack[i] != '\0')
    {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j])
        {
            j++;
        }
        if (needle[j] == '\0')
        {
            return (char *)(haystack + i);
        }
        i++;
    }
    return nullptr;
}
int my_strstr_index(const char *haystack, const char *needle)
{
    int i = 0;
    while (haystack[i] != '\0')
    {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j])
        {
            j++;
        }
        if (needle[j] == '\0')
        {
            while (haystack[i] != ':')
            {
                i++;
            }
            return i + 1;
        }
        i++;
    }
    return -1;
}
void reverse_inplace(char *s)
{
    int size = size_tmy_strlen(s);
    int i = 0;
    while (i < size / 2)
    {
        char temp = s[i];
        s[i] = s[size - i - 1];
        s[size - i - 1] = temp;
        i++;
    }
}

int is_palindrome(const char *s)
{
    int size = size_tmy_strlen(s);
    char *dup = new char[size + 1];
    my_strcpy(dup, s);
    reverse_inplace(dup);
    int result = my_strcmp(dup, s);
    delete[] dup;
    return result;
}

int count_words(const char *s)
{
    int i = 0, count = 0;
    while (s[i] != '\0')
    {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
        {
            count++;
        }
        i++;
    }
    return count;
}

void tokenizer(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        char token[100] = "";
        int j = 0;
        while (str[i] != ',' && str[i] != '\0')
        {
            token[j++] = str[i++];
        }
        token[j] = '\0';
        cout << token << "\n";
        if (str[i] == ',')
        {
            i++;
        }
    }
}

char *trail_spaces(char *a)
{
    int i = 0, j = 0;
    int len = size_tmy_strlen(a);
    char *b = new char[len + 1];
    while (a[i] != '\0')
    {
        if ((a[i] == ' ' && a[i + 1] == ' ') || a[i] == '\n' || a[i] == '\t')
        {
            i++;
            continue;
        }
        b[j++] = a[i++];
    }
    if (b[j - 1] == ' ')
    {
        b[j - 1] = '\0';
    }
    else
    {
        b[j] = '\0';
    }
    return b;
}

int find_occur(const char *s, const char *word)
{
    int i = 0, count = 0;
    char a[400];
    while (s[i] != '\0')
    {
        while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
        {
            i++;
        }
        int j = 0;
        while (s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && s[i] != '\0')
        {
            a[j++] = s[i++];
        }
        a[j] = '\0';
        if (j > 0 && my_strcmp(a, word) == 0)
        {
            count++;
        }
        i++;
    }
    return count;
}

char *replace_key_value(char *str, const char *obj)
{
    int i = 0, j = 0;
    int len = 0;
    len += size_tmy_strlen(str);
    len += size_tmy_strlen(obj);
    char *new_str = new char[len + 1];
    while (str[i] != '\0')
    {
        char *block = new char[len];
        if (str[i] == '{' && str[i + 1] == '{')
        {
            i += 2;
            int k = 0;
            while (str[k + i] != '}' && str[k + i - 1] != '}')
            {
                block[k] = str[k + i];
                k++;
            }
            block[k] = '\0';
            k = 0;
            while (block[k] != '\0')
            {
                if (block[k] == str[k + i])
                {
                    str[k + i] = '}';
                    k++;
                }
            }
            int index = my_strstr_index(obj, block);

            while (obj[index] != '}')
            {
                new_str[j++] = obj[index++];
            }
        }
        else if (str[i] == '}' && str[i + 1] == '}')
        {
            i += 2;
        }
        else
        {
            new_str[j++] = str[i++];
        }
    }
    new_str[i + 1] = '\0';
    return new_str;
}