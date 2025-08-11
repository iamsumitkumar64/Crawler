#include "header.h"
#include "../../Day_1/lib/header.h"
#include <iostream>
#include <fstream>
using namespace std;

CrawlClass::CrawlClass(char *dirname)
{
    this->folder_name = dirname;
}

char *normalize_url(char *url)
{
    int len = size_tmy_strlen(url);
    while (len > 1 && url[len - 1] == '/')
    {
        url[--len] = '\0';
    }
    for (int i = 0; url[i] != '\0' && url[i] != '/'; i++)
    {
        if (url[i] >= 'A' && url[i] <= 'Z')
        {
            url[i] = url[i] + 32;
        }
    }
    return url;
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

void CrawlClass::extract_url(char *http_url, char *code, int curr_depth, int maxCount)
{
    int i = 0;
    int levelCrawlCount = 0;
    while (code[i] != '\0')
    {
        if (levelCrawlCount >= maxCount)
        {
            return;
        }
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
            if (url[0] == '#' || checksubstr(url, (char *)"#") ||
                checksubstr(url, (char *)"mailto:") ||
                checksubstr(url, (char *)"tel:") ||
                checksubstr(url, (char *)"javascript:"))
            {
                delete[] url;
                continue;
            }
            if (!checksubstr(url, (char *)"http"))
            {
                int base_len = size_tmy_strlen(http_url);
                int url_len = size_tmy_strlen(url);
                char *full_url = new char[base_len + url_len + 2];
                my_strcpy(full_url, http_url);
                if (http_url[base_len - 1] == '/' && url[0] == '/')
                {
                    my_strcat(full_url, url + 1);
                }
                else if (http_url[base_len - 1] != '/' && url[0] != '/')
                {
                    full_url[base_len] = '/';
                    full_url[base_len + 1] = '\0';
                    my_strcat(full_url, url);
                }
                else
                {
                    my_strcat(full_url, url);
                }
                delete[] url;
                url = full_url;
            }
            if (isHtml(url))
            {
                url = normalize_url(url);
                if (hash_obj.HashExists(url, -1))
                {
                    delete[] url;
                    continue;
                }
                if (curr_depth >= 1)
                {
                    bool success = dfs_crawl(url, curr_depth - 1, maxCount);
                    if (success)
                    {
                        levelCrawlCount++;
                    }
                    else
                    {
                        cout << "Crawl failed, not inserted:-> " << url << "\n";
                    }
                }
            }
            delete[] url;
        }
        else
        {
            i++;
        }
    }
}

char *CrawlClass::code_find(char *file_path)
{
    fstream in(file_path);
    if (!in.is_open())
    {
        return nullptr;
    }
    int length = 0, capacity = 1000;
    char c;
    char *full_code = new char[capacity];
    while (in.get(c))
    {
        if (length >= capacity - 1)
        {
            capacity *= 2;
            char *temp = new char[capacity];
            for (int i = 0; i < length; i++)
            {
                temp[i] = full_code[i];
            }
            delete[] full_code;
            full_code = temp;
        }
        full_code[length++] = c;
    }
    full_code[length] = '\0';
    char *temp = trail_spaces(full_code);
    delete[] full_code;
    full_code = temp;
    return full_code;
}

bool CrawlClass::dfs_crawl(char *url, int curr_depth, int maxCount)
{
    if (url == nullptr || folder_name == nullptr || curr_depth < 0)
    {
        return false;
    }
    if (curr_depth == 0)
    {
        return true;
    }
    url = normalize_url(url);
    if (hash_obj.HashExists(url, -1))
    {
        return false;
    }
    hash_obj.Hashinsert(url, -1, 90);
    WgetClass wget_obj;
    char *path = wget_obj.wgetfunc(this->folder_name, url);
    if (path == nullptr)
    {
        return false;
    }
    char *code = code_find(path);
    if (code == nullptr)
    {
        delete[] path;
        return false;
    }
    cout << "[INFO] Depth: " << curr_depth << endl;
    keyword_obj.removeGrammer(path, url);
    if (curr_depth > 0)
    {
        extract_url(url, code, curr_depth, maxCount);
    }
    delete[] code;
    delete[] path;
    return true;
}

bool CrawlClass::processOldKeywords(const char *fileName, const char *full_code)
{
    FILE *fk = fopen(fileName, "r");
    if (!fk)
        return false;
    fclose(fk);

    char word[256];
    cout << "\nEnter Keyword: ";
    cin >> word;

    if (!full_code || my_strcmp(full_code, "") == 0)
    {
        cout << "No keywords present\n";
        return true;
    }

    int startIndex = my_strstr_index(full_code, word);
    if (startIndex == -1)
    {
        cout << "Keyword not found\n";
        return true;
    }

    char urls[2048];
    int i = startIndex;
    int j = 0;
    while (full_code[i] != '\0' &&
           full_code[i] != '\n' &&
           !(full_code[i] == '-' && full_code[i + 1] == '>') &&
           j < (int)sizeof(urls) - 1)
    {
        urls[j++] = full_code[i++];
    }
    urls[j] = '\0';

    cout << "URLs for keyword \"" << word << "\":\n";
    tokenizer(urls);
    return true;
}