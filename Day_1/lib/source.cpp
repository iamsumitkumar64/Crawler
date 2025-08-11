#include "header.h"
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "../../../My Libraries/String_Lib/header.h"
using namespace std;

char *WgetClass::wgetfunc(const char *dirname, const char *url)
{
    char mkdir_cmd[150] = "mkdir -p ";
    my_strcat(mkdir_cmd, dirname);
    system(mkdir_cmd);

    char *file_path = new char[200];
    file_path[0] = '\0';

    int len = size_tmy_strlen(dirname);
    my_strcpy(file_path, dirname);
    if (dirname[len - 1] != '/')
    {
        my_strcat(file_path, "/");
    }

    my_strcat(file_path, unique_name());
    my_strcat(file_path, ".html");

    char command[600] = "wget -O ";
    my_strcat(command, file_path);
    my_strcat(command, " ");
    my_strcat(command, url);

    int result = system(command);
    if (result == 0)
    {
        char *abs_path = realpath(file_path, nullptr);

        if (abs_path != nullptr)
        {
            system("touch logfile.txt");
            ofstream logfile("logfile.txt", ios::app);

            char logs[500] = " ";
            my_strcpy(logs, "Url-> ");
            my_strcat(logs, url);
            my_strcat(logs, " File_Name-> ");
            my_strcat(logs, abs_path);
            logfile << logs << endl;

            cout << "\tSuccess\n";
            delete[] file_path;
            return abs_path;
        }
    }
    cout << "\tFailed\n";
    delete[] file_path;
    return nullptr;
}

char *WgetClass::unique_name()
{
    char *uniqueName = new char[30];
    long long timestamp = time(0);
    // add clock ticks and process ID to avoid duplicates in same second
    timestamp = timestamp * 100000 + (clock() % 100000) + getpid();
    longIntoString(timestamp, uniqueName);
    return uniqueName;
}

void WgetClass::longIntoString(long long num, char *str)
{
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    int i = 0;
    if (num < 0)
    {
        str[i++] = '-';
        num = -num;
    }
    long long revNum = 0;
    int digit_count = 0;
    while (num > 0)
    {
        revNum = revNum * 10 + (num % 10);
        num /= 10;
        digit_count++;
    }
    for (int j = 0; j < digit_count; j++)
    {
        str[i++] = (revNum % 10) + '0';
        revNum /= 10;
    }
    str[i] = '\0';
}