#include "../include/Table.h"

Table::Table() : id(0), isOccupied(false), revenue(0), workTime(0, 0) {}

Table::Table(int _id) : id(_id), isOccupied(false), revenue(0), workTime(0, 0) {}

void Table::PrintParams() const {
    std::string time = ToString(workTime);
    std::cout << id << " "
        << revenue << " "
        << time << std::endl;
}

void Table::Run(Time startTimeSession) {
    isOccupied = true;
    startTime = startTimeSession;
}

void Table::End(Time endTimeSession, int pricePerHour) {
    isOccupied = false;
    Time timeSession = endTimeSession - startTime;
    workTime += timeSession;
    revenue += CalculateRevenue(timeSession, pricePerHour);
}

int Table::CalculateRevenue(Time timeSession, int pricePerHour) {
    return (timeSession.hours + (bool)(timeSession.minutes % 60)) * pricePerHour;
}

bool Table::IsOccupied() const {
    return isOccupied;
}