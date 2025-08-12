#include "header.h"

SEO::SEO(char *dirname)
{
    Crawl_obj = new CrawlClass(dirname);
    this->dirname = dirname;
}

SEO::~SEO()
{
    delete Crawl_obj;
}

void SEO::Do_Crawl(char *url,
                   int depth, int maxCount)
{
    if (!url && !depth && !maxCount)
    {
        cout << "Url-Depth-Maxcount missing";
        return;
    }
    Crawl_obj->dfs_crawl(url, depth, maxCount);
}

char *SEO::Search_Keyword(char *keyword)
{
    char *full_code = Crawl_obj->code_find("keyword.txt");
    char *urls = Crawl_obj->processOldKeywords("keyword.txt", full_code);
    cout << urls;
    return urls;
    delete[] full_code;
    delete[] urls;
}

void SEO::Delete_Old_Data()
{
    if (!dirname)
    {
        cout << "Directory name not set\n";
        return;
    }
    char cmd1[50] = "rm -rf ";
    my_strcat(cmd1, dirname);

    char cmd2[50] = "rm -f keyword.txt";
    int result1 = system(cmd1);
    int result2 = system(cmd2);

    if (result1 == 0)
    {
        cout << "Deleted directory: " << dirname << "\n";
    }
    else
    {
        cout << "Failed to delete directory: " << dirname << "\n";
    }
    if (result2 == 0)
    {
        cout << "Deleted keyword.txt\n";
    }
    else
    {
        cout << "Failed to delete keyword.txt\n";
    }
}