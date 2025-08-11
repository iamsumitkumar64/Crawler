#include <iostream>
#include <fstream>
#include "lib/header.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "Usage: " << argv[0] << " <url> <dir> <depth> <maxCount>\n";
        return 0;
    }

    const char *url = argv[1];
    const char *dirname = argv[2];
    int depth = atoi(argv[3]);
    int maxCount = atoi(argv[4]);

    CrawlClass obj((char *)dirname);
    char *full_code = obj.code_find("keyword.txt");
    if (full_code && size_tmy_strlen(full_code) > 1)
    {
        int choice;
        cout << "\n\nWant old one (0) or New Crawl(1) = ";
        cin >> choice;
        if (choice == 0)
        {
            if (obj.processOldKeywords("keyword.txt", full_code))
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
    obj.dfs_crawl((char *)url, depth, maxCount);
    return 0;
}