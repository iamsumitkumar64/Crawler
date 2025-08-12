#include <iostream>
#include <fstream>
#include "lib/header.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "Usage: " << argv[0] << " <url> <dir_name> <depth> <maxCount>\n";
        return 0;
    }

    char *url = argv[1];
    char *dirname = argv[2];
    int depth = atoi(argv[3]);
    int maxCount = atoi(argv[4]);

    CrawlClass Crawl_obj((char *)dirname);
    char *full_code = Crawl_obj.code_find("keyword.txt");
    if (full_code && size_tmy_strlen(full_code) > 1)
    {
        int choice;
        cout << "\n\nWant old Crawl (0) or New Crawl(any INTEGER) = ";
        cin >> choice;
        if (choice == 0)
        {
            if (Crawl_obj.processOldKeywords("keyword.txt", full_code))
            {
                delete[] full_code;
                return 0;
            }
        }
    }
    delete[] full_code;
    FILE *fp = fopen("logfile.txt", "w");
    if (fp)
    {
        fclose(fp);
    }
    Crawl_obj.dfs_crawl(url, depth, maxCount);
    return 0;
}