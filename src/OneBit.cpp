#include "OneBit.h"

OneBit::OneBit(size_t entries)
    : table(entries, true), mask(entries - 1) {}

bool OneBit::predict(uint64_t pc) {
    return table[(pc >> 2) & mask];
}

void OneBit::update(uint64_t pc, bool taken) {
    table[(pc >> 2) & mask] = taken;
}

void OneBit::reset() {
    std::fill(table.begin(), table.end(), true);
}

std::string OneBit::name() const {
    return "1-bit Predictor";
}