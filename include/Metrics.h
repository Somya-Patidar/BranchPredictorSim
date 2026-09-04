#pragma once

#include <cstdint>

class Metrics {
public:
    Metrics(uint32_t mispredictionPenalty = 5);

    void recordPrediction(bool predicted, bool actual);

    uint64_t totalBranches() const;
    uint64_t correctPredictions() const;
    uint64_t incorrectPredictions() const;

    double accuracy() const;
    double mpki() const;
    double ipc() const;

    void reset();

private:
    uint64_t total;
    uint64_t correct;
    uint64_t incorrect;

    uint32_t penalty;
};