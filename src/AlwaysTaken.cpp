#include "AlwaysTaken.h"

bool AlwaysTaken::predict(uint64_t) {
    return true;
}

void AlwaysTaken::update(uint64_t, bool) {
    // Stateless predictor
}

void AlwaysTaken::reset() {
    // Nothing to reset
}

std::string AlwaysTaken::name() const {
    return "Always Taken";
}