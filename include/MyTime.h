#pragma once

#include <iostream>
#include <iomanip>
#include <regex>
#include <sstream>

struct Time {
    int hours;
    int minutes;
    Time();
    Time(int h, int m);
};

Time ParseTime(std::string str);
std::string ToString(Time time);

bool operator==(const Time& firTime, const Time& secTime);
bool operator!=(const Time& firTime, const Time& secTime);
bool operator<(const Time& firTime, const Time& secTime);
bool operator<=(const Time& firTime, const Time& secTime);
bool operator>(const Time& firTime, const Time& secTime);
bool operator>=(const Time& firTime, const Time& secTime);
Time operator+(const Time& firTime, const Time& secTime);
Time operator-(const Time& firTime, const Time& secTime);
Time& operator+=(Time& firTime, const Time& secTime);