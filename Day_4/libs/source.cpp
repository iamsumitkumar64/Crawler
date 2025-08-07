#include "header.h"
#include <iostream>

void Keywords::extract_file_paths()
{
    fstream in("../Day_2_3/logfile.txt", ios::in);
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
    int i = 0;
    while (full_code[i] != '\0')
    {
        char temp[13];
        int n = 0;
        while (n < 12 && full_code[i + n] != '\0')
        {
            temp[n] = full_code[i + n];
            n++;
        }
        temp[n] = '\0';
        int index = my_strstr_index(temp, "File_Name->");
        if (index != -1)
        {
            i += 12;
            while (full_code[i] == ' ' || full_code[i] == '\n')
            {
                i++;
            }
            int start = i;
            while (full_code[i] != '\0' && full_code[i] != '"' && full_code[i] != '\'' && full_code[i] != '>' && full_code[i] != ' ')
            {
                i++;
            }
            int len = i - start;
            char *file_path = new char[len + 1];
            for (int j = 0; j < len; j++)
            {
                file_path[j] = full_code[start + j];
            }
            file_path[len] = '\0';
            cout << "File Name-" << file_path << endl;
            // removeGrammer(file_path);
        }
        else
        {
            i++;
        }
    }
    delete[] full_code;
}

void Keywords::removeGrammer(char *file_path)
{
    char *full_code = code_find(file_path);
    if (full_code != nullptr)
    {
        cout << full_code << endl;
        delete[] full_code;
    }
}

char *Keywords::code_find(char *file_path)
{
    fstream in(file_path);
    if (!in)
    {
        cerr << "[ERROR] Cannot open file: " << file_path << endl;
        delete[] file_path;
        return nullptr;
    }
    int length = 0, capacity = 1000;
    char c;
    char *full_code = new char[capacity]();
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
    char *trimmed = trail_spaces(full_code);
    delete[] full_code;
    delete[] file_path;
    return trimmed;
}