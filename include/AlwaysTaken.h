#ifndef ALWAYS_TAKEN_H
#define ALWAYS_TAKEN_H

#include "Predictor.h"

class AlwaysTaken:public Predictor{

public:

    bool predict(uint64_t) override;
    void update(uint64_t,bool) override;
    void reset() override;
    std::string name() const override;

};

#endif