#pragma once

#include <vector>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <fstream>
#include <map>
#include "ComputerClub.h"
#include "MyTime.h"

class Parser {
private:
    static int ParseInt(const std::string& line);
    static std::vector<std::string> SplitString(const std::string& line);
    static void ParseConfig(std::ifstream& file, ComputerClub& compClub);
    static void ParseEvents(std::ifstream& file, ComputerClub& compClub);
public:
    static void ParseFile(std::string& filename, ComputerClub& compClub);
};