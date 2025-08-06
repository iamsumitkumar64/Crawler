#include <iostream>
#include "./lib/header.h"
using namespace std;

int main(int argc, char *argv[])
{
    // 1st run compile+link-> g++ Crawler.cpp -o ./exe
    // 2nd run exe-> ./{exe_name} {link} {folder_name}
    cout << "\n";
    if (argc < 3)
    {
        cout << "\nLess Argument Given\n";
        return 0;
    }
    const char *url = argv[1];
    const char *dirname = argv[2];

    // char url[50];
    // char dirname[50];
    // cout << "\nEnter url :";
    // cin >> url;
    // cout << "\nEnter dirname :";
    // cin >> dirname;

    WgetClass obj;
    char *file_path = obj.wgetfunc(dirname, url);
    cout << file_path;
    cout << "\n";
    return 0;
}