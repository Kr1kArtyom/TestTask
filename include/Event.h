#pragma once

#include <chrono>
#include <string>
#include "MyTime.h"

struct Event {
    static const int withoutTable = 0;

    Time time;
    int id;
    std::string client;
    int tableId;
    std::string message;
};
