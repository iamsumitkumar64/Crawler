#ifndef KEYWORDS
#define KEYWORDS

#include <fstream>
#include "../../../My Libraries/String_Lib/header.h"

class Keywords
{
public:
    char *code_find(char *file_path);
    void removeGrammer(char *file_path, char *url);
    void extract_text_from_body(char *html);
    char *find_most_frequent_keyword(char *text);
    void updateKeywordFile(char *keyword, char *url);
};

#include "source.cpp"
#endif