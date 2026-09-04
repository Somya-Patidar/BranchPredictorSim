#include "TraceReader.h"

#include <fstream>
#include <sstream>

bool TraceReader::load(const std::string& filename) {
    trace.clear();

    std::ifstream file(filename);

    if (!file)
        return false;

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string pcString;
        char outcome;

        ss >> pcString >> outcome;

        if (pcString.empty())
            continue;

        Branch branch;

        branch.pc = std::stoull(pcString, nullptr, 16);
        branch.taken = (outcome == 'T');

        trace.push_back(branch);
    }

    return true;
}

const std::vector<Branch>& TraceReader::branches() const {
    return trace;
}