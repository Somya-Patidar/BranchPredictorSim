#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <string>
#include <cstdint>

class Predictor {

public:

    virtual bool predict(uint64_t pc)=0;
    virtual void update(uint64_t pc,bool taken)=0;
    virtual void reset()=0;
    virtual std::string name() const=0;
    virtual ~Predictor(){}

};

#endif