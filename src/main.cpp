#include <iostream>
#include "../include/ComputerClub.h"
#include "../include/Parser.h"
#include "../include/Table.h"
#include "../include/Event.h"
#include "../include/Time.h"

int main(int argc, char *argv[]) {
    std::string filename = argv[1];

    ComputerClub club;
    Parser::ParseFile(filename, club);
}