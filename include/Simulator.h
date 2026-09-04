#pragma once

#include "Metrics.h"
#include "Predictor.h"
#include "TraceReader.h"

class Simulator {
public:
    explicit Simulator(uint32_t mispredictionPenalty = 5);

    Metrics run(Predictor& predictor,
                const TraceReader& trace);

private:
    uint32_t penalty;
};