#include "Benchmark.h"
#include <filesystem>
#include "AlwaysNotTaken.h"
#include "AlwaysTaken.h"
#include "GShare.h"
#include "Metrics.h"
#include "OneBit.h"
#include "Simulator.h"
#include "Tournament.h"
#include "TraceReader.h"
#include "TwoBit.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

struct BenchmarkEntry {

    std::string trace;
    std::string predictor;

    uint64_t branches;
    double accuracy;
    double mpki;
    double ipc;
};

static std::unique_ptr<Predictor>
createPredictor(const std::string& name,
                const Config& config) {

    if (name == "always-taken")
        return std::make_unique<AlwaysTaken>();

    if (name == "always-not-taken")
        return std::make_unique<AlwaysNotTaken>();

    if (name == "one-bit")
        return std::make_unique<OneBit>(config.tableSize);

    if (name == "two-bit")
        return std::make_unique<TwoBit>(config.tableSize);

    if (name == "gshare")
        return std::make_unique<GShare>(
            config.tableSize,
            config.historyBits);

    if (name == "tournament")
        return std::make_unique<Tournament>(
            config.tableSize,
            config.historyBits);

    return nullptr;
}

bool Benchmark::run(const Config& config) {

    std::vector<std::string> traces = {

        "../traces/sample.trace",
        "../traces/loop.trace",
        "../traces/random.trace",
        "../traces/mixed.trace",

        "../traces/workloads/nested_loops.trace",
        "../traces/workloads/correlated.trace",
        "../traces/workloads/stress.trace"
    };

    std::vector<std::string> predictors = {

        "always-taken",
        "always-not-taken",
        "one-bit",
        "two-bit",
        "gshare",
        "tournament"
    };

    std::filesystem::path outputPath(config.outputCSV);

    // Create parent directories if they don't exist
    std::filesystem::create_directories(outputPath.parent_path());

    std::ofstream csv(outputPath);

    if (!csv) {
        std::cerr << "Failed to create CSV: "
                << outputPath << "\n";
        return false;
    }

    csv << "Trace,Predictor,Branches,"
           "Accuracy,MPKI,IPC\n";

    Simulator simulator(config.penalty);

    int current = 1;
    int total =
        traces.size() *
        predictors.size();

    for (const auto& traceFile : traces) {

        TraceReader reader;

        if (!reader.load(traceFile)) {

            std::cerr
                << "Skipping "
                << traceFile
                << "\n";

            continue;
        }

        for (const auto& predictorName :
             predictors) {

            std::cout
                << "["
                << current++
                << "/"
                << total
                << "] "
                << predictorName
                << "\n";

            auto predictor =
                createPredictor(
                    predictorName,
                    config);

            Metrics metrics =
                simulator.run(
                    *predictor,
                    reader);

            csv
                << traceFile << ","
                << predictor->name() << ","
                << metrics.totalBranches() << ","
                << metrics.accuracy() << ","
                << metrics.mpki() << ","
                << metrics.ipc()
                << "\n";
        }
    }

    std::cout
        << "\nResults written to:\n"
        << config.outputCSV
        << "\n";

    return true;
}