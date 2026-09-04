#include "Simulator.h"

Simulator::Simulator(uint32_t mispredictionPenalty)
    : penalty(mispredictionPenalty) {}

Metrics Simulator::run(Predictor& predictor,
                       const TraceReader& trace) {

    Metrics metrics(penalty);

    predictor.reset();

    for (const auto& branch : trace.branches()) {
        bool prediction = predictor.predict(branch.pc);
        metrics.recordPrediction(prediction, branch.taken);
        predictor.update(branch.pc, branch.taken);
    }

    return metrics;
}