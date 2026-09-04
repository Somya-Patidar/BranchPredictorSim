#include "AlwaysTaken.h"

bool AlwaysTaken::predict(uint64_t){
    return true;
}

void AlwaysTaken::update(uint64_t,bool){}
void AlwaysTaken::reset(){}
std::string AlwaysTaken::name() const{
    return "Always Taken";

}