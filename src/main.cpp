#include "AlwaysNotTaken.h"
#include "AlwaysTaken.h"
#include "OneBit.h"
#include "Simulator.h"
#include "TraceReader.h"
#include "TwoBit.h"
#include "GShare.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

static void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  ./BranchPredictorSim <trace> <predictor>";
    std::cout << " [--table-size N]";
    std::cout << " [--history-bits N]\n\n";

    std::cout << "Predictors:\n";
    std::cout << "  always-taken\n";
    std::cout << "  always-not-taken\n";
    std::cout << "  one-bit\n";
    std::cout << "  two-bit\n";
    std::cout << "  gshare\n";
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printUsage();
        return 1;
    }

    std::string traceFile = argv[1];
    std::string predictorName = argv[2];

    uint32_t tableSize = 1024;
    uint32_t historyBits = 8;

    for (int i = 3; i < argc; ++i) {

        std::string arg = argv[i];

        if (arg == "--table-size") {

            if (i + 1 >= argc) {
                std::cerr << "Missing table size value.\n";
                return 1;
            }

            tableSize = static_cast<uint32_t>(
                std::stoul(argv[++i]));
        }
        else if (arg == "--history-bits") {
            if (i + 1 >= argc) {
                std::cerr << "Missing history length.\n";
                return 1;
            }
            historyBits =static_cast<uint32_t>(std::stoul(argv[++i]));
        }
        else {
            std::cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    TraceReader reader;

    if (!reader.load(traceFile)) {
        std::cerr << "Error: Failed to open trace file.\n";
        return 1;
    }

    std::unique_ptr<Predictor> predictor;

    if (predictorName == "always-taken") {
        predictor = std::make_unique<AlwaysTaken>();
    }
    else if (predictorName == "always-not-taken") {
        predictor = std::make_unique<AlwaysNotTaken>();
    }
    else if (predictorName == "one-bit") {
        predictor = std::make_unique<OneBit>(tableSize);
    }
    else if (predictorName == "two-bit") {
        predictor = std::make_unique<TwoBit>(tableSize);
    }
    else if (predictorName == "gshare") {
        predictor =
            std::make_unique<GShare>(tableSize,
                                    historyBits);
    }
    else {
        std::cerr << "Unknown predictor: "
                  << predictorName << "\n";
        printUsage();
        return 1;
    }

    Simulator simulator(5);

    Metrics metrics = simulator.run(*predictor, reader);

    std::cout << "\n========== BranchScope ==========\n";
    std::cout << "Predictor           : "
              << predictor->name() << "\n";

    if (predictorName == "one-bit" || predictorName == "two-bit" || predictorName == "gshare")
        std::cout << "Table Size          : "
                  << tableSize << "\n";

    if (predictorName == "gshare") {
        std::cout << "History Bits        : "
                << historyBits << "\n";
    }
    std::cout << "Branches            : "
              << metrics.totalBranches() << "\n";
    std::cout << "Correct             : "
              << metrics.correctPredictions() << "\n";
    std::cout << "Incorrect           : "
              << metrics.incorrectPredictions() << "\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Accuracy            : "
              << metrics.accuracy() << "%\n";
    std::cout << "Conditional MPKI    : "
              << metrics.mpki() << "\n";
    std::cout << "IPC                 : "
              << metrics.ipc() << "\n";

    std::cout << "=================================\n";

    return 0;
}