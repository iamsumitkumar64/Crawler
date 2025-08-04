#include "header.h"
#include <ctime>
#include <fstream>
#include "../../String_Lib/header.h"
using namespace std;

void WgetClass::wgetfunc(const char *dirname, const char *url)
{
    char mkdir_cmd[150] = "mkdir -p ";
    my_strcat(mkdir_cmd, dirname);
    system(mkdir_cmd);

    system("touch logfile.txt");
    ofstream logfile("logfile.txt", ios::app);
    char logs[400] = " ";
    my_strcpy(logs, " Url-> ");
    my_strcat(logs, url);
    my_strcat(logs, " Folder-> ");
    my_strcat(logs, dirname);
    logfile << logs << endl;

    char file_path[200] = "";
    my_strcat(file_path, dirname);
    my_strcat(file_path, "/");
    cout << "hi one";
    my_strcat(file_path, unique_name());
    cout << "hi two";
    my_strcat(file_path, ".html");
    char command[600] = "wget -O ";
    my_strcat(command, file_path);
    my_strcat(command, " ");
    my_strcat(command, url);

    int result = system(command);
    if (result == 0)
    {
        cout << "\tSuccess\n";
    }
    else
    {
        cout << "\tFailed\n";
    }
}

char *WgetClass::unique_name()
{
    char *uniqueName = new char[30];
    time_t timenow = time(0);
    longIntoString(timenow, uniqueName);
    return uniqueName;
}

void WgetClass::longIntoString(long long num, char *str)
{
    str[0] = '/';
    if (num == 0)
    {
        str[1] = '0';
        str[2] = '\0';
    }
    else
    {
        int i = 1, rem = 0;
        if (num < 0)
        {
            num = -num;
            str[i] = '-';
            i++;
        }
        long long revNum = 0;
        while (num > 0)
        {
            rem = num % 10;
            revNum = revNum * 10 + rem;
            num /= 10;
        }
        while (revNum > 0)
        {
            str[i] = (revNum % 10) + '0';
            revNum /= 10;
            i++;
        }
        str[i] = '\0';
    }
    // char extension[] = {'.', 'h', 't', 'm', 'l', '\0'};
    // my_strcat(str, extension);
}