// src/Logger.h

#pragma once
#include <string>

class Logger {
    public:
        void info(const std::string& message) const;
        void warning(const std::string& message) const;
        void error(const std::string& message) const;
};