#ifndef ONE_BIT_H
#define ONE_BIT_H

#include "Predictor.h"
#include <vector>

class OneBit : public Predictor {

    std::vector<bool> table;
    size_t mask;

public:
    explicit OneBit(size_t entries = 4096);

    bool predict(uint64_t pc) override;
    void update(uint64_t pc, bool taken) override;
    void reset() override;
    std::string name() const override;
};

#endif