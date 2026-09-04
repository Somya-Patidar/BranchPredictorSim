#include "AlwaysNotTaken.h"

bool AlwaysNotTaken::predict(uint64_t) {
    return false;
}

void AlwaysNotTaken::update(uint64_t, bool) {
    // Stateless predictor
}

void AlwaysNotTaken::reset() {
    // Nothing to reset
}

std::string AlwaysNotTaken::name() const {
    return "Always Not Taken";
}