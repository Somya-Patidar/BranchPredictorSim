#include "Metrics.h"

Metrics::Metrics(uint32_t mispredictionPenalty)
    : total(0),
      correct(0),
      incorrect(0),
      penalty(mispredictionPenalty) {}

void Metrics::recordPrediction(bool predicted, bool actual) {
    total++;

    if (predicted == actual)
        correct++;
    else
        incorrect++;
}

uint64_t Metrics::totalBranches() const {
    return total;
}

uint64_t Metrics::correctPredictions() const {
    return correct;
}

uint64_t Metrics::incorrectPredictions() const {
    return incorrect;
}

double Metrics::accuracy() const {
    if (total == 0)
        return 0.0;

    return static_cast<double>(correct) * 100.0 /
           static_cast<double>(total);
}

double Metrics::mpki() const {
    if (total == 0)
        return 0.0;

    return static_cast<double>(incorrect) * 1000.0 /
           static_cast<double>(total);
}

double Metrics::ipc() const {
    if (total == 0)
        return 0.0;

    double cycles =
        static_cast<double>(total) +
        static_cast<double>(incorrect * penalty);

    return static_cast<double>(total) / cycles;
}

void Metrics::reset() {
    total = 0;
    correct = 0;
    incorrect = 0;
}