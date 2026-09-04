#pragma once

#include <cstdint>
#include <string>

struct Config {

    std::string traceFile;
    std::string predictor;

    uint32_t tableSize = 1024;
    uint32_t historyBits = 8;
    uint32_t penalty = 5;
};

bool parseArguments(int argc,
                    char* argv[],
                    Config& config);

void printUsage();