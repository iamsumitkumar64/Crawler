#include <iostream>
#include "lib/header.h"
using namespace std;

int main()
{
    char dirname[30];
    int depth, maxCount;
    char url[100];
    cout << "\n\nEnter URL :->";
    cin >> url;
    cout << "Enter Folder Name :->";
    cin >> dirname;
    cout << "Enter depth :->";
    cin >> depth;
    cout << "Enter Max-Count at Every depth :->";
    cin >> maxCount;
    CrawlClass obj(dirname);
    obj.dfs_crawl(url, depth, maxCount);
    return 0;
}