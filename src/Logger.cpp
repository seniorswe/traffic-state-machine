// src/Logger.cpp

#include "Logger.h"
#include <iostream>

void Logger::info(const std::string& message) const {
    std::cout << "Info | " << message << "\n";
}

void Logger::warning(const std::string& message) const {
    std::cout << "Warning | " << message << "\n";
}

void Logger::error(const std::string& message) const {
    std::cout << "Error | " << message << "\n";
}

