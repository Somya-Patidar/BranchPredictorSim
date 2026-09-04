#include "AlwaysNotTaken.h"
#include "AlwaysTaken.h"
#include "Config.h"
#include "GShare.h"
#include "OneBit.h"
#include "Simulator.h"
#include "Tournament.h"
#include "TraceReader.h"
#include "TwoBit.h"

#include <iomanip>
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    Config config;

    if (!parseArguments(argc, argv, config))
        return 1;

    TraceReader reader;

    if (!reader.load(config.traceFile)) {
        std::cerr << "Error: Failed to open trace file.\n";
        return 1;
    }

    std::unique_ptr<Predictor> predictor;

    if (config.predictor == "always-taken") {

        predictor = std::make_unique<AlwaysTaken>();

    } else if (config.predictor == "always-not-taken") {

        predictor = std::make_unique<AlwaysNotTaken>();

    } else if (config.predictor == "one-bit") {

        predictor = std::make_unique<OneBit>(config.tableSize);

    } else if (config.predictor == "two-bit") {

        predictor = std::make_unique<TwoBit>(config.tableSize);

    } else if (config.predictor == "gshare") {

        predictor = std::make_unique<GShare>(
            config.tableSize,
            config.historyBits);

    } else if (config.predictor == "tournament") {

        predictor = std::make_unique<Tournament>(
            config.tableSize,
            config.historyBits);

    } else {

        std::cerr << "Unknown predictor: "
                  << config.predictor << "\n";

        printUsage();
        return 1;
    }

    Simulator simulator(config.penalty);

    Metrics metrics = simulator.run(*predictor, reader);

    std::cout << "\n========== BranchPredictorSim ==========\n";

    std::cout << "Predictor           : "
              << predictor->name() << "\n";

    std::cout << "Trace               : "
              << config.traceFile << "\n";

    std::cout << "Table Size          : "
              << config.tableSize << "\n";

    if (config.predictor == "gshare" ||
        config.predictor == "tournament") {

        std::cout << "History Bits        : "
                  << config.historyBits << "\n";
    }

    std::cout << "Penalty             : "
              << config.penalty
              << " cycles\n";

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

    std::cout << "========================================\n";

    return 0;
}