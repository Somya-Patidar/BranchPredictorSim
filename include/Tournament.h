#pragma once

#include "GShare.h"
#include "Predictor.h"
#include "TwoBit.h"

#include <vector>

class Tournament : public Predictor {
public:
    Tournament(uint32_t tableSize = 1024,
               uint32_t historyBits = 8);

    bool predict(uint64_t pc) override;
    void update(uint64_t pc, bool taken) override;
    void reset() override;
    std::string name() const override;

private:
    uint32_t chooserIndex(uint64_t pc) const;

    TwoBit localPredictor;
    GShare globalPredictor;

    uint32_t tableSize;

    // 0-1 prefer local
    // 2-3 prefer global
    std::vector<uint8_t> chooserTable;
};