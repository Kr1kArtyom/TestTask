#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
#include <regex>
#include <fstream>
#include <map>
#include <iomanip>
#include "Event.h"
#include "Table.h"

class ComputerClub {
private:
    int numTables, numFreeTables;
    std::map<int, Table> tables;
    std::deque<std::string> queue;
    std::map<std::string, int> clients;
    Time startTime, endTime, lastEventTime;
    int pricePerHour;

    bool CheckSeqEvents(Time timeEvent);
    bool ValidateClient(std::string client);
    bool ValidateTable(int eventId, int tableId);
    bool ValidateEvent(Event event);
    bool CheckTime(Event event);
    bool CheckClientAvailability(Event event);
    bool IsTableOccupied(int tableId);
    bool IsClientInQueue(std::string client);
    void RemoveClientFromQueue(std::string client);
    void UpdateLastEvent(Event event);

public:
    enum Events {
        CLIENTARRIVED = 1,
        CLIENTSIT = 2,
        CLIENTWAIT = 3,
        CLIENTLEFT = 4,
        OUTCLIENTLEFT = 11,
        OUTCLIENTSIT = 12,
        ERROREVENT = 13
    };

    ComputerClub();
    ComputerClub(int _numTables, Time _startTime, Time _endTime, int _pricePerHour);

    void OpenShift();
    void CloseShift();
    void HandleEvent(Event event);
    void HandleClientArrival(Event event);
    void HandleClientSit(Event event);
    void HadleClientWait(Event event);
    void HandleClientLeft(Event event);
    void GenerateOutClientSitEvent(Event event, int numTable);
    void HandleOutClientSit(Event event);
    void GenerateOutClientLeftEvent(Event event);
    void HandleOutClientLeft(Event event);
    void GenerateErrorEvent(Event event, std::string errorMessage);
    std::string EventToString(Event event);
    void HandleErrorEvent(Event event);
};


