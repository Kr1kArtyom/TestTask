#include "../include/Time.h"

Time::Time() : hours(0), minutes(0) {}
Time::Time(int h, int m) {
    if (h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::invalid_argument("Invalid time: hours and minutes must be within valid range");
    }
    hours = h;
    minutes = m;
};

Time ParseTime(std::string str) {
    std::istringstream ss(str);
    int h, m;
    char colon;
    if (!(ss >> h >> colon >> m) || colon != ':' || h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::invalid_argument("Invalid time format: " + str);
    }
    return { h, m };
}

std::string ToString(Time time) {
    if (time.hours < 0 || time.hours > 23 || time.minutes < 0 || time.minutes > 59) {
        throw std::invalid_argument("Invalid time: " + std::to_string(time.hours) + ":" + std::to_string(time.minutes));
    }
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << time.hours << ":"
        << std::setfill('0') << std::setw(2) << time.minutes;
    return ss.str();
}

bool operator==(const Time& firTime, const Time& secTime) {
    return firTime.hours == secTime.hours && firTime.minutes == secTime.minutes;
}

bool operator!=(const Time& firTime, const Time& secTime) {
    return !(firTime == secTime);
}

bool operator<(const Time& firTime, const Time& secTime) {
    if (firTime.hours == secTime.hours) {
        return firTime.minutes < secTime.minutes;
    }
    return firTime.hours < secTime.hours;
}

bool operator<=(const Time& firTime, const Time& secTime) {
    return !(secTime < firTime);
}

bool operator>(const Time& firTime, const Time& secTime) {
    return secTime < firTime;
}

bool operator>=(const Time& firTime, const Time& secTime) {
    return !(firTime < secTime);
}

Time operator+(const Time& firTime, const Time& secTime) {
    int totalMinutes = firTime.hours * 60 + firTime.minutes + secTime.hours * 60 + secTime.minutes;
    return { totalMinutes / 60, totalMinutes % 60 };
}

Time operator-(const Time& firTime, const Time& secTime) {
    int totalMinutes = firTime.hours * 60 + firTime.minutes - (secTime.hours * 60 + secTime.minutes);
    if (totalMinutes < 0) {
        totalMinutes += 1440;
    }
    return { totalMinutes / 60, totalMinutes % 60 };
}

Time& operator+=(Time& firTime, const Time& secTime) {
    firTime.minutes += secTime.minutes;
    firTime.hours += firTime.minutes / 60;
    firTime.minutes %= 60;
    firTime.hours += secTime.hours;
    firTime.hours %= 24;
    return firTime;
}