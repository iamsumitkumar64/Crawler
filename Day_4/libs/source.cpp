#include "header.h"
#include <iostream>

using namespace std;

char *Keywords::code_find(char *file_path)
{
    fstream in(file_path);
    if (!in)
    {
        cerr << "[ERROR] Cannot open file: " << file_path << endl;
        return nullptr;
    }
    int length = 0, capacity = 1000;
    char c;
    char *full_code = new char[capacity]();
    while (in.get(c))
    {
        if (length >= capacity - 1)
        {
            capacity *= 2;
            char *temp = new char[capacity];
            for (int i = 0; i < length; i++)
            {
                temp[i] = full_code[i];
            }
            delete[] full_code;
            full_code = temp;
        }
        full_code[length++] = c;
    }
    full_code[length] = '\0';
    char *trimmed = trail_spaces(full_code);
    // delete[] full_code;
    // delete[] file_path;
    return trimmed;
}
void Keywords::removeGrammer(char *file_path, char *url)
{
    char *full_code = code_find(file_path);
    if (full_code != nullptr)
    {
        extract_text_from_body(full_code);
        char *keyword = find_most_frequent_keyword(full_code);
        char *url_copy = nullptr;
        if (url)
        {
            int url_len = size_tmy_strlen(url);
            url_copy = new char[url_len + 1];
            my_strcpy(url_copy, url);
        }
        bool keyword_allocated = true;
        if (!keyword)
        {
            my_strcpy(keyword, "[no keyword found]");
            keyword_allocated = false;
        }
        updateKeywordFile(keyword, url_copy);
        // delete[] full_code;
        if (keyword_allocated)
        {
            delete[] keyword;
        }
        if (url_copy)
        {
            delete[] url_copy;
        }
    }
}

void Keywords::extract_text_from_body(char *html)
{
    char *body_start = nullptr, *body_end = nullptr;
    for (int i = 0; html[i]; i++)
    {
        if (!body_start && html[i] == '<' && html[i + 1] == 'b' && html[i + 2] == 'o' && html[i + 3] == 'd' && html[i + 4] == 'y')
        {
            while (html[i] && html[i++] != '>')
            {
                if (!body_start && html[i])
                {
                    body_start = &html[i];
                }
            }
        }
        if (html[i] == '<' && html[i + 1] == '/' && html[i + 2] == 'b' && html[i + 3] == 'o' && html[i + 4] == 'd' && html[i + 5] == 'y')
        {
            body_end = &html[i];
            break;
        }
    }
    if (!body_start || !body_end)
    {
        return;
    }
    int j = 0;
    bool in_tag = false;
    for (char *p = body_start; p < body_end; p++)
    {
        if (*p == '<')
        {
            in_tag = true;
        }
        else if (*p == '>')
        {
            in_tag = false;
        }
        else if (!in_tag)
        {
            html[j++] = *p;
        }
    }
    html[j] = '\0';
}
char *Keywords::find_most_frequent_keyword(char *text)
{
    const char *stopwords[] = {
        "nbsp",
        "a",
        "an",
        "and",
        "are",
        "as",
        "at",
        "be",
        "by",
        "for",
        "from",
        "has",
        "he",
        "in",
        "is",
        "it",
        "its",
        "of",
        "on",
        "that",
        "the",
        "to",
        "was",
        "will",
        "with",
        "would",
        "you",
        "your",
        "have",
        "had",
        "this",
        "these",
        "they",
        "them",
        "their",
        "there",
        "then",
        "than",
        "or",
        "but",
        "not",
        "can",
        "could",
        "should",
        "would",
        "may",
        "might",
        "must",
        "shall",
        "will",
        "do",
        "does",
        "did",
        "done",
        "been",
        "being",
        "about",
        "after",
        "all",
        "also",
        "any",
        "because",
        "before",
        "both",
        "but",
        "each",
        "even",
        "first",
        "her",
        "here",
        "him",
        "his",
        "how",
        "if",
        "into",
        "just",
        "like",
        "make",
        "many",
        "me",
        "more",
        "most",
        "my",
        "new",
        "no",
        "now",
        "only",
        "other",
        "our",
        "out",
        "over",
        "said",
        "same",
        "see",
        "she",
        "so",
        "some",
        "such",
        "take",
        "time",
        "two",
        "up",
        "use",
        "very",
        "way",
        "we",
        "well",
        "were",
        "what",
        "when",
        "where",
        "which",
        "who",
        "why",
        "work",
        "page",
        "home",
        "contact",
        "about",
        "services",
        "products",
        "news",
        "blog",
        "login",
        "register",
        "search",
        "help",
        "support",
        "privacy",
        "terms",
        "policy",
        "www",
        "quot",
        "http",
        "https",
        "com",
        "org",
        "net",
        "edu",
        "gov",
        "io",
        "co",
        "uk",
        "us",
        "info",
        "site",
        "online",
        "web",
        "page",
        "html",
        "www",
        "www.",
        "http://",
        "https://",
    };
    int stop_count = sizeof(stopwords) / sizeof(stopwords[0]);
    int max_count = 0;
    char *most_freq_word = nullptr;
    int i = 0, wlen = 0;
    char word[30];

    while (text[i] != '\0')
    {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            if (wlen < 29)
            {
                word[wlen++] = (c | 32);
            }
            i++;
        }
        else
        {
            if (wlen > 0)
            {
                word[wlen] = '\0';
                wlen = 0;
                if (size_tmy_strlen(word) < 3)
                {
                    i++;
                    continue;
                }
                bool skip = false;
                for (int s = 0; s < stop_count; s++)
                {
                    if (my_strcmp(word, stopwords[s]) == 0)
                    {
                        skip = true;
                        break;
                    }
                }
                if (skip)
                {
                    i++;
                    continue;
                }
                int count = 0;
                int idx = 0;
                while (text[idx] != '\0')
                {
                    while (text[idx] != '\0' && !((text[idx] >= 'a' && text[idx] <= 'z') || (text[idx] >= 'A' && text[idx] <= 'Z')))
                    {
                        idx++;
                    }
                    int k = 0;
                    char temp_word[30];
                    while (((text[idx] >= 'a' && text[idx] <= 'z') || (text[idx] >= 'A' && text[idx] <= 'Z')) && k < 29)
                    {
                        temp_word[k++] = (text[idx++] | 32);
                    }
                    temp_word[k] = '\0';
                    if (k > 0 && my_strcmp(temp_word, word) == 0)
                    {
                        count++;
                    }
                }
                if (count > max_count)
                {
                    max_count = count;
                    if (most_freq_word)
                    {
                        delete[] most_freq_word;
                    }
                    most_freq_word = new char[size_tmy_strlen(word) + 1];
                    my_strcpy(most_freq_word, word);
                }
            }
            i++;
        }
    }
    return most_freq_word;
}

void Keywords::updateKeywordFile(char *keyword, char *url)
{
    if (!keyword || !url)
    {
        return;
    }
    FILE *fp = fopen("keyword.txt", "r");
    const int MAX_LINE = 9000;
    char **lines = new char *[1000];
    int line_count = 0;
    bool keyword_found = false;
    if (fp)
    {
        char buffer[MAX_LINE];
        while (fgets(buffer, sizeof(buffer), fp))
        {
            buffer[size_tmy_strlen(buffer) - (buffer[size_tmy_strlen(buffer) - 1] == '\n')] = '\0';
            lines[line_count] = new char[MAX_LINE];
            my_strcpy(lines[line_count], buffer);
            line_count++;
        }
        fclose(fp);
    }
    for (int i = 0; i < line_count; i++)
    {
        char *arrow = my_strstr(lines[i], "->");
        if (arrow)
        {
            int len = arrow - lines[i];
            if (my_strncmp(lines[i], keyword, len) == 0 && size_tmy_strlen(keyword) == (size_t)len)
            {
                my_strcat(lines[i], ",");
                my_strcat(lines[i], url);
                keyword_found = true;
                break;
            }
        }
    }
    if (!keyword_found)
    {
        lines[line_count] = new char[MAX_LINE];
        my_strcpy(lines[line_count], keyword);
        my_strcat(lines[line_count], "->");
        my_strcat(lines[line_count], url);
        line_count++;
    }
    fp = fopen("keyword.txt", "w");
    for (int i = 0; i < line_count; i++)
    {
        size_t len = size_tmy_strlen(lines[i]);
        if (len == 0 || lines[i][len - 1] != '\n')
        {
            fprintf(fp, "%s\n", lines[i]);
        }
        else
        {
            fprintf(fp, "%s", lines[i]);
        }
        delete[] lines[i];
    }
    fclose(fp);
    delete[] lines;
}