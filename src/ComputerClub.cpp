#include "../include/ComputerClub.h"

bool ComputerClub::CheckSeqEvents(Time timeEvent) {
    return timeEvent >= lastEventTime;
}

bool ComputerClub::ValidateClient(std::string client) {
    std::regex pattern("^[0-9a-z_-]*$");
    return std::regex_match(client, pattern);
}

bool ComputerClub::ValidateTable(int eventId, int tableId) {
    return eventId == Events::CLIENTSIT ? tableId >= 1 && tableId <= numTables : tableId == 0;
}

bool ComputerClub::ValidateEvent(Event event) {
    return ValidateClient(event.client) && ValidateTable(event.id, event.tableId) && CheckSeqEvents(event.time);
}

bool ComputerClub::CheckTime(Event event) {
    return event.time >= startTime && event.time <= endTime;
}

bool ComputerClub::CheckClientAvailability(Event event) {
    return clients.find(event.client) != clients.end();
}

bool ComputerClub::IsTableOccupied(int tableId) {
    return tables[tableId].IsOccupied();
}

bool ComputerClub::IsClientInQueue(std::string client) {
    return std::find(queue.begin(), queue.end(), client) != queue.end();
}

void ComputerClub::RemoveClientFromQueue(std::string client) {
    auto clientIt = std::find(queue.begin(), queue.end(), client);
    queue.erase(clientIt);
}

void ComputerClub::UpdateLastEvent(Event event) {
    lastEventTime = event.time;
}

ComputerClub::ComputerClub() {}

ComputerClub::ComputerClub(int _numTables, Time _startTime, Time _endTime, int _pricePerHour)
    : numTables(_numTables), numFreeTables(_numTables), startTime(_startTime), endTime(_endTime), lastEventTime(Time()), pricePerHour(_pricePerHour) {
    for (int id = 1; id <= numTables; id++) {
        tables[id] = Table(id);
    }
}

void ComputerClub::OpenShift() {
    std::cout << ToString(startTime) << std::endl;
}

void ComputerClub::CloseShift() {
    std::vector<std::string> clientsKeys;
    for (const auto& client : clients) {
        clientsKeys.push_back(client.first);
    }

    for (const auto& client : clientsKeys) {
        GenerateOutClientLeftEvent(Event{
            endTime,
            Events::OUTCLIENTLEFT,
            client,
            });
    }

    clientsKeys.clear();

    std::cout << ToString(endTime) << std::endl;

    for (const auto& table : tables) {
        table.second.PrintParams();
    }
}

void ComputerClub::HandleEvent(Event event) {
    if (!ValidateEvent(event)) {
        throw std::invalid_argument("HandleEvent throw an exception: Input data format error");
        return;
    }
    
    std::cout << EventToString(event) << std::endl;

    switch (event.id) {
    case Events::CLIENTARRIVED:
        HandleClientArrival(event);
        break;
    case Events::CLIENTSIT:
        HandleClientSit(event);
        break;
    case Events::CLIENTWAIT:
        HadleClientWait(event);
        break;
    case Events::CLIENTLEFT:
        HandleClientLeft(event);
        break;
    }

    UpdateLastEvent(event);
}

void ComputerClub::HandleClientArrival(Event event) {
    if (CheckClientAvailability(event)) {
        GenerateErrorEvent(event, "YouShallNotPass");
        return;
    }

    if (!CheckTime(event)) {
        GenerateErrorEvent(event, "NotOpenYet");
        return;
    }

    clients[event.client] = Event::withoutTable;
}

void ComputerClub::HandleClientSit(Event event) {
    if (!CheckClientAvailability(event)) {
        GenerateErrorEvent(event, "ClientUnknown");
        return;
    }

    if (IsTableOccupied(event.tableId)) {
        GenerateErrorEvent(event, "PlaceIsBusy");
        return;
    }

    clients[event.client] = event.tableId;
    tables[event.tableId].Run(event.time);
    numFreeTables--;
}

void ComputerClub::HadleClientWait(Event event) {
    if (!CheckClientAvailability(event)) {
        GenerateErrorEvent(event, "ClientUnknown");
        return;
    }

    if (IsClientInQueue(event.client)) {
        GenerateErrorEvent(event, "ClientIsAlreadyWaiting");
        return;
    }

    if (clients[event.client] != Event::withoutTable) {
        GenerateErrorEvent(event, "ClientIsAlreadySitting");
        return;
    }

    if (numFreeTables != 0) {
        GenerateErrorEvent(event, "ICanWaitNoLonger!");
        return;
    }

    if (queue.size() >= numTables) {
        GenerateOutClientLeftEvent(event);
        return;
    }

    queue.push_back(event.client);
}

void ComputerClub::HandleClientLeft(Event event) {
    if (!CheckClientAvailability(event)) {
        GenerateErrorEvent(event, "ClientUnknown");
        return;
    }

    int numTable = clients[event.client];
    if (numTable != Event::withoutTable) {
        tables[numTable].End(event.time, pricePerHour);
        numFreeTables++;
        GenerateOutClientSitEvent(event, numTable);
    }
    else if (IsClientInQueue(event.client)) {
        RemoveClientFromQueue(event.client);
    }

    clients.erase(event.client);
}

void ComputerClub::GenerateOutClientSitEvent(Event event, int numTable) {
    if (queue.empty()) return;

    std::string clientFromQueue = queue.front();
    queue.pop_front();

    Event newEvent = {
        event.time,
        Events::OUTCLIENTSIT,
        clientFromQueue,
        numTable
    };

    HandleOutClientSit(newEvent);
}

void ComputerClub::HandleOutClientSit(Event event) {
    clients[event.client] = event.tableId;
    tables[event.tableId].Run(event.time);
    numFreeTables--;
    std::cout << EventToString(event) << std::endl;
}

void ComputerClub::GenerateOutClientLeftEvent(Event event) {
    Event newEvent = {
        event.time,
        Events::OUTCLIENTLEFT,
        event.client,
        Event::withoutTable
    };

    HandleOutClientLeft(newEvent);
}

void ComputerClub::HandleOutClientLeft(Event event) {
    int numTable = clients[event.client];
    if (numTable != Event::withoutTable) {
        tables[numTable].End(event.time, pricePerHour);
        numFreeTables++;
    }
    else if (IsClientInQueue(event.client)) {
        RemoveClientFromQueue(event.client);
    }
    clients.erase(event.client);
    std::cout << EventToString(event) << std::endl;
}

void ComputerClub::GenerateErrorEvent(Event event, std::string errorMessage) {
    Event errorEvent = {
        event.time,
        Events::ERROREVENT,
        event.client,
        Event::withoutTable,
        errorMessage
    };

    HandleErrorEvent(errorEvent);
}

std::string ComputerClub::EventToString(Event event) {
    std::ostringstream oss;
    oss << ToString(event.time) << " " << event.id;

    switch (event.id) {
    case Events::CLIENTSIT:
    case Events::OUTCLIENTSIT:
        oss << " " << event.client << " " << event.tableId;
        break;
    case Events::ERROREVENT:
        oss << " " << event.message;
        break;
    default:
        oss << " " << event.client;
        break;
    }

    return oss.str();
}

void ComputerClub::HandleErrorEvent(Event event) {
    std::cerr << EventToString(event) << std::endl;
}