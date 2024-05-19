#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include "MyTime.h"

class Table {
private:
    int id;
    bool isOccupied;
    int revenue;
    Time workTime;
    Time startTime;
    int CalculateRevenue(Time timeSession, int pricePerHour);

public:
    Table();
    Table(int _id);

    void PrintParams() const;
    void Run(Time startTimeSession);
    void End(Time endTimeSession, int pricePerHour);
    bool IsOccupied() const;
};

