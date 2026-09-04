#include "AlwaysNotTaken.h"
#include "AlwaysTaken.h"
#include "Simulator.h"
#include "TraceReader.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

static void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  ./BranchScope <trace> <predictor>\n\n";
    std::cout << "Predictors:\n";
    std::cout << "  always-taken\n";
    std::cout << "  always-not-taken\n";
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printUsage();
        return 1;
    }

    std::string traceFile = argv[1];
    std::string predictorName = argv[2];

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