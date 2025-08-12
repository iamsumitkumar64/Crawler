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

void SEO::ReinitializeCrawlObj()
{
    delete Crawl_obj;
    Crawl_obj = new CrawlClass(dirname);
}

void SEO::Do_Crawl(char *url,
                   int depth, int maxCount)
{
    if (!url && !depth && !maxCount)
    {
        cout << "Url-Depth-Maxcount missing";
        return;
    }
    ReinitializeCrawlObj();
    Crawl_obj->dfs_crawl(url, depth, maxCount);
}
char *SEO::Search_Keyword(char *keyword)
{
    char keyword_file_name[20] = "keyword.txt";
    char *full_code = Crawl_obj->code_find(keyword_file_name);
    if (!full_code)
    {
        cout << "Could not load keyword file.\n";
        return nullptr;
    }
    char *all_urls = Crawl_obj->processOldKeywords(keyword_file_name, full_code);
    if (!all_urls)
    {
        cout << "Keyword not found or no URLs associated.\n";
        delete[] full_code;
        return nullptr;
    }
    cout << all_urls << endl;
    delete[] full_code;
    delete[] all_urls;
    return all_urls;
}

void SEO::delete_directory()
{
    if (!dirname)
    {
        cout << "Directory name not set\n";
        return;
    }
    char cmd1[50] = "rm -rf ";
    my_strcat(cmd1, dirname);
    int result = system(cmd1);
    if (result == 0)
    {
        cout << "Deleted directory: " << dirname << "\n";
    }
    else
    {
        cout << "Failed to delete directory: " << dirname << "\n";
    }
}

void SEO::delete_file()
{
    int result1 = system("rm -f keyword.txt");
    int result2 = system("rm -f logfile.txt");
    if (result1 == 0)
    {
        cout << "Deleted keyword.txt\n";
    }
    else
    {
        cout << "Failed to delete keyword.txt\n";
    }
    if (result2 == 0)
    {
        cout << "Deleted logfile.txt\n";
    }
    else
    {
        cout << "Failed to delete logfile.txt\n";
    }
}

void SEO::Delete_Old_Data()
{
    delete_directory();
    delete_file();
    ReinitializeCrawlObj();
}