#ifndef DFS
#define DFS
#include "../../../My Libraries/String_Lib/header.h"
#include "../../../My Libraries/Generic_C++_Hash_Map/generic_libs/header.h"

class CrawlClass
{
private:
    Hash_map<char *, int> hash_obj = Hash_map<char *, int>(5);
    char *folder_name;

public:
    CrawlClass(char *dirname);

    bool dfs_crawl(char *url, int &curr_depth, int maxCount);
    void url_find(char *file_path, int curr_depth, int maxCount);
    char *code_find(char *file_path);
    void extract_url(char *code, int curr_depth, int maxCount);
    bool isHtml(char *url);
};

#include "source.cpp"
#endif