#pragma once

#include "Predictor.h"

#include <cstdint>
#include <vector>

class OneBit : public Predictor {
public:
    explicit OneBit(uint32_t tableSize = 1024);

    bool predict(uint64_t pc) override;
    void update(uint64_t pc, bool taken) override;
    void reset() override;
    std::string name() const override;

private:
    uint32_t index(uint64_t pc) const;

    uint32_t tableSize;
    std::vector<bool> predictionTable;
};