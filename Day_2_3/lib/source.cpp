#include "header.h"
#include "../../Day_1/lib/header.h"
#include <iostream>
#include <fstream>
using namespace std;

CrawlClass::CrawlClass(char *dirname)
{
    this->folder_name = dirname;
}

bool CrawlClass::isHtml(char *url)
{
    if (checksubstr(url, (char *)".css") || checksubstr(url, (char *)".js") ||
        checksubstr(url, (char *)".png") || checksubstr(url, (char *)".jpg") ||
        checksubstr(url, (char *)".jpeg") || checksubstr(url, (char *)".svg") ||
        checksubstr(url, (char *)".ico") || checksubstr(url, (char *)".pdf") ||
        checksubstr(url, (char *)"fonts.") || checksubstr(url, (char *)"/css") ||
        checksubstr(url, (char *)".woff") || checksubstr(url, (char *)".ttf") ||
        !checksubstr(url, (char *)"."))
    {
        return false;
    }
    return true;
}

void CrawlClass::extract_url(char *code, int curr_depth, int maxCount)
{
    int i = 0;
    while (code[i] != '\0')
    {
        char temp[9];
        int n = 0;
        while (n < 8 && code[i + n] != '\0')
        {
            temp[n] = code[i + n];
            n++;
        }
        temp[n] = '\0';
        int index = my_strstr_index(temp, "<a href=");
        if (index != -1)
        {
            i += 8;
            while (code[i] == '"' || code[i] == '\'')
            {
                i++;
            }
            int start = i;
            while (code[i] != '\0' && code[i] != '"' && code[i] != '\'' && code[i] != '>' && code[i] != ' ')
            {
                i++;
            }
            int len = i - start;
            if (len <= 0)
            {
                continue;
            }
            char *url = new char[len + 1];
            for (int j = 0; j < len; j++)
            {
                url[j] = code[start + j];
            }
            url[len] = '\0';
            int ulen = size_tmy_strlen(url);
            if (isHtml(url))
            {
                if (!hash_obj.HashExists(url, -1) && hash_obj.Hashcount() < maxCount)
                {
                    bool success = dfs_crawl(url, curr_depth, maxCount);
                    if (success)
                    {
                        hash_obj.Hashinsert(url, -1, 90);
                    }
                    else
                    {
                        cout << "Crawl failed, not into hash:-> " << url << "\n";
                    }
                    delete[] url;
                }
                else
                {
                    cout << "Already visited or duplicate URL:-> " << url << "\n";
                }
            }
            else
            {
                cout << "Rejected URL:-> " << url << "\n";
                delete[] url;
            }
        }
        else
        {
            i++;
        }
    }
    cout << "\n\n\nAccepted URL:-> " << "\n";
    hash_obj.HashdisplayAll();
    if (hash_obj.Hashcount() >= maxCount)
    {
        return;
    }
    cout << "\n\n\n";
}

char *CrawlClass::code_find(char *file_path)
{
    fstream in(file_path);
    int length = 0, capacity = 1000;
    char c;
    char *new_url = new char[capacity];
    while (in.get(c))
    {
        if (length >= capacity - 1)
        {
            capacity *= 2;
            char *temp = new char[capacity];
            for (int i = 0; i < length; i++)
            {
                temp[i] = new_url[i];
            }
            delete[] new_url;
            new_url = temp;
        }
        new_url[length++] = c;
    }
    new_url[length] = '\0';
    char *temp = trail_spaces(new_url);
    delete[] new_url;
    new_url = temp;
    return new_url;
}

void CrawlClass::url_find(char *file_path, int curr_depth, int maxCount)
{
    char *full_code = code_find(file_path);
    extract_url(full_code, curr_depth, maxCount);
    delete[] full_code;
}

bool CrawlClass::dfs_crawl(char *url, int &curr_depth, int maxCount)
{
    if (curr_depth <= 0 || url == nullptr || this->folder_name == nullptr)
    {
        return false;
    }
    WgetClass wget_obj;
    char *path = wget_obj.wgetfunc(this->folder_name, url);
    if (path == nullptr)
    {
        return false;
    }
    int next_depth = curr_depth - 1;
    url_find(path, next_depth, maxCount);
    return true;
}