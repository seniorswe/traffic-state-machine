// src/Logger.cpp

#include "Logger.h"
#include <iostream>

std::mutex Logger::consoleLogMutex;

void Logger::info(const std::string& message) const {
    std::lock_guard<std::mutex> lock(consoleLogMutex);
    std::cout << "Info | " << message << "\n";
}

void Logger::warning(const std::string& message) const {
    std::lock_guard<std::mutex> lock(consoleLogMutex);
    std::cout << "Warning | " << message << "\n";
}

void Logger::error(const std::string& message) const {
    std::lock_guard<std::mutex> lock(consoleLogMutex);
    std::cout << "Error | " << message << "\n";
}

