#include "TwoBit.h"

#include <algorithm>

TwoBit::TwoBit(uint32_t tableSize)
    : tableSize(tableSize),
      counterTable(tableSize, 3) {}

uint32_t TwoBit::index(uint64_t pc) const {
    return static_cast<uint32_t>(pc % tableSize);
}

bool TwoBit::predict(uint64_t pc) {
    return counterTable[index(pc)] >= 2;
}

void TwoBit::update(uint64_t pc, bool taken) {

    uint8_t& counter = counterTable[index(pc)];

    if (taken) {
        if (counter < 3)
            counter++;
    }
    else {
        if (counter > 0)
            counter--;
    }
}

void TwoBit::reset() {
    std::fill(counterTable.begin(),
              counterTable.end(),
              3);
}

std::string TwoBit::name() const {
    return "Two-Bit Saturating Predictor";
}