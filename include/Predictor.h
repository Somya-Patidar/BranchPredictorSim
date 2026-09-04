#pragma once

#include <cstdint>
#include <string>

class Predictor {
public:
    virtual ~Predictor() = default;

    virtual bool predict(uint64_t pc) = 0;

    virtual void update(uint64_t pc, bool taken) = 0;

    virtual void reset() = 0;

    virtual std::string name() const = 0;
};