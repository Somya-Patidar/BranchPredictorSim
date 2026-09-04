#include "TraceReader.h"

#include <iostream>

int main(int argc, char* argv[]) {

    std::cout << "BranchPredictorSim - Core Simulator\n";

    if (argc < 2) {
        std::cout << "Usage: ./BranchPredictorSim <trace>\n";
        return 0;
    }

    TraceReader reader;

    if (!reader.load(argv[1])) {
        std::cerr << "Failed to open trace.\n";
        return 1;
    }

    std::cout << "Trace loaded successfully.\n";
    std::cout << "Branches: "
              << reader.branches().size()
              << "\n";

    std::cout << "Simulator infrastructure ready.\n";

    return 0;
}