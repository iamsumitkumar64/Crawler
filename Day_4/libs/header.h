#ifndef KEYWORDS
#define KEYWORDS

#include <fstream>
#include "../../../My Libraries/Generic_C++_LL/libs_head_files/LL_Head.h"
#include "../../../My Libraries/String_Lib/header.h"

class Keywords
{
private:
public:
    void extract_file_paths();
    char *code_find(char *file_path);
    void removeGrammer(char *file_path);
};

#include "source.cpp"
#endif