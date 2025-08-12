#ifndef SEO_H
#define SEO_H
#include "../../Day_2_3/lib/header.h"
#include "../../../My Libraries/String_Lib/header.h"

class SEO
{
private:
    CrawlClass *Crawl_obj;
    char *dirname;

public:
    SEO(char *dirname);
    ~SEO();
    void Do_Crawl(char *url,
                  int depth, int maxCount); // used for crawling
    char *Search_Keyword(char *keyword);    // used for getting keyword urls
    void Delete_Old_Data();                 // used for removing old data
};

#include "source.cpp"
#endif