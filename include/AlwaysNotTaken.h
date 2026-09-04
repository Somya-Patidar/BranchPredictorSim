#pragma once

#include "Predictor.h"

class AlwaysNotTaken : public Predictor {
public:
    bool predict(uint64_t pc) override;
    void update(uint64_t pc, bool taken) override;
    void reset() override;
    std::string name() const override;
};