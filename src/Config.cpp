#include "Config.h"

#include <iostream>

void printUsage() {

    std::cout
        << "BranchPredictorSim\n\n"

        << "Single simulation:\n"
        << "  ./BranchPredictorSim <trace> <predictor> [options]\n\n"

        << "Benchmark suite:\n"
        << "  ./BranchPredictorSim --benchmark\n\n"

        << "Predictors:\n"
        << "  always-taken\n"
        << "  always-not-taken\n"
        << "  one-bit\n"
        << "  two-bit\n"
        << "  gshare\n"
        << "  tournament\n\n"

        << "Options:\n"
        << "  --table-size N\n"
        << "  --history-bits N\n"
        << "  --penalty N\n";
}

bool parseArguments(int argc,
                    char* argv[],
                    Config& config) {

    if (argc == 2 &&
        std::string(argv[1]) == "--benchmark") {

        config.benchmark = true;
        return true;
    }

    if (argc < 3) {

        printUsage();
        return false;
    }

    config.traceFile = argv[1];
    config.predictor = argv[2];

    for (int i = 3; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "--table-size") {

            if (++i >= argc) {
                std::cerr << "Missing value after --table-size\n";
                return false;
            }

            config.tableSize =
                static_cast<uint32_t>(std::stoul(argv[i]));
        }

        else if (arg == "--history-bits") {

            if (++i >= argc) {
                std::cerr << "Missing value after --history-bits\n";
                return false;
            }

            config.historyBits =
                static_cast<uint32_t>(std::stoul(argv[i]));
        }

        else if (arg == "--penalty") {

            if (++i >= argc) {
                std::cerr << "Missing value after --penalty\n";
                return false;
            }

            config.penalty =
                static_cast<uint32_t>(std::stoul(argv[i]));
        }

        else {

            std::cerr
                << "Unknown option: "
                << arg
                << "\n";

            return false;
        }
    }

    if (config.tableSize == 0) {

        std::cerr << "Table size must be greater than zero.\n";
        return false;
    }

    if (config.historyBits == 0 ||
        config.historyBits > 20) {

        std::cerr
            << "History bits must be between 1 and 20.\n";

        return false;
    }

    if (config.penalty == 0) {

        std::cerr
            << "Penalty must be greater than zero.\n";

        return false;
    }

    return true;
}