#include <iostream>
#include <fstream>
#include "Day_5/lib/header.h"
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

    SEO seo_obj(dirname);
    int choice;
    while (true)
    {
        cout << "\n===== SEO Tool Menu =====\n";
        cout << "1. Crawl Website (New or Old)\n";
        cout << "2. Delete Old Crawl Data\n";
        cout << "3. Search Keyword\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            ifstream keyword_file("keyword.txt");
            if (keyword_file.good())
            {
                keyword_file.close();
                int crawl_choice;
                cout << "\nFound 'keyword.txt'.\nUse old crawl (0) or new crawl (any other integer)? ";
                cin >> crawl_choice;
                if (crawl_choice == 0)
                {
                    cout << "\nRunning old crawl using keywords...\n";
                    char *result = seo_obj.Search_Keyword((char *)"keyword.txt");
                    if (!result)
                    {
                        cout << "Returning to menu...\n";
                    }
                }
                else
                {
                    cout << "\nRunning new crawl...\n";
                    seo_obj.Do_Crawl(url, depth, maxCount);
                }
            }
            else
            {
                cout << "\nRunning new crawl...\n";
                seo_obj.Do_Crawl(url, depth, maxCount);
            }
            break;
        }
        case 2:
            cout << "\nDeleting old crawl data...\n";
            seo_obj.Delete_Old_Data();
            break;
        case 3:
        {
            ifstream keyword_file("keyword.txt");
            if (!keyword_file.good())
            {
                cout << "\n'keyword.txt' does not exist. Cannot search.\n";
                break;
            }
            keyword_file.close();
            cout << "\nSearching using existing keywords...\n";
            seo_obj.Search_Keyword((char *)"keyword.txt");
            break;
        }
        case 4:
            cout << "\nExiting program.\n";
            return 0;
        default:
            cout << "\nInvalid choice. Please enter 1, 2, 3, or 4.\n";
        }
    }

    return 0;
}