#include "OneBit.h"

OneBit::OneBit(uint32_t tableSize)
    : tableSize(tableSize),
      predictionTable(tableSize, true) {}

uint32_t OneBit::index(uint64_t pc) const {
    return static_cast<uint32_t>(pc % tableSize);
}

bool OneBit::predict(uint64_t pc) {
    return predictionTable[index(pc)];
}

void OneBit::update(uint64_t pc, bool taken) {
    predictionTable[index(pc)] = taken;
}

void OneBit::reset() {
    std::fill(predictionTable.begin(),
              predictionTable.end(),
              true);
}

std::string OneBit::name() const {
    return "One-Bit Predictor";
}