#ifndef WGET_HANDLER_H
#define WGET_HANDLER_H
#include <iostream>

class WgetClass
{
private:
    char *unique_name();
    void longIntoString(long long num, char *str);

public:
    char *wgetfunc(const char *dirname, const char *url);
};
#include "source.cpp"
#endif