#include "GShare.h"

#include <algorithm>

GShare::GShare(uint32_t tableSize,
               uint32_t historyBits)
    : tableSize(tableSize),
      historyBits(historyBits),
      historyMask((1u << historyBits) - 1),
      ghr(0),
      counterTable(tableSize, 3) {}

uint32_t GShare::index(uint64_t pc) const {

    uint32_t pcIndex =
        static_cast<uint32_t>(pc) % tableSize;

    return (pcIndex ^ ghr) % tableSize;
}

bool GShare::peekPredict(uint64_t pc) const {
    return counterTable[index(pc)] >= 2;
}

bool GShare::predict(uint64_t pc) {
    return peekPredict(pc);
}

void GShare::update(uint64_t pc, bool taken) {

    uint8_t& counter = counterTable[index(pc)];

    if (taken) {
        if (counter < 3)
            counter++;
    } else {
        if (counter > 0)
            counter--;
    }

    ghr <<= 1;

    if (taken)
        ghr |= 1;

    ghr &= historyMask;
}

void GShare::reset() {

    std::fill(counterTable.begin(),
              counterTable.end(),
              3);

    ghr = 0;
}

std::string GShare::name() const {

    return "GShare Predictor";
}