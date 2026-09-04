#pragma once

#include "Predictor.h"

#include <cstdint>
#include <vector>

class TwoBit : public Predictor {
public:
    explicit TwoBit(uint32_t tableSize = 1024);
    bool peekPredict(uint64_t pc) const;
    bool predict(uint64_t pc) override;
    void update(uint64_t pc, bool taken) override;
    void reset() override;
    std::string name() const override;

private:
    uint32_t index(uint64_t pc) const;

    uint32_t tableSize;
    std::vector<uint8_t> counterTable;
};