#include "Tournament.h"

#include <algorithm>

Tournament::Tournament(uint32_t tableSize,
                       uint32_t historyBits)
    : localPredictor(tableSize),
      globalPredictor(tableSize, historyBits),
      tableSize(tableSize),
      chooserTable(tableSize, 1) {}

uint32_t Tournament::chooserIndex(uint64_t pc) const {
    return static_cast<uint32_t>(pc % tableSize);
}

bool Tournament::predict(uint64_t pc) {

    bool local = localPredictor.peekPredict(pc);
    bool global = globalPredictor.peekPredict(pc);

    uint8_t chooser = chooserTable[chooserIndex(pc)];

    if (chooser >= 2)
        return global;

    return local;
}

void Tournament::update(uint64_t pc, bool taken) {

    bool local = localPredictor.peekPredict(pc);
    bool global = globalPredictor.peekPredict(pc);

    localPredictor.update(pc, taken);
    globalPredictor.update(pc, taken);

    uint8_t& chooser = chooserTable[chooserIndex(pc)];

    if (local != global) {

        if (global == taken) {

            if (chooser < 3)
                chooser++;

        } else {

            if (chooser > 0)
                chooser--;
        }
    }
}

void Tournament::reset() {

    localPredictor.reset();
    globalPredictor.reset();

    std::fill(chooserTable.begin(),
              chooserTable.end(),
              1);
}

std::string Tournament::name() const {
    return "Tournament Predictor";
}