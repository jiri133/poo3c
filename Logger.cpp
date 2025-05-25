//
// Created by MINALP1 on 5/26/2025.
//

#include "Logger.h"

// Logger - fara modificari necesare

    void Logger::logEvent(const std::string &msg)
    {
        std::cout << "[LOG] " << msg << std::endl;
    }
//nu mai pun static ca s-ar defini de 2 ori