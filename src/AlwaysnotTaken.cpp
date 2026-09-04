#include "AlwaysNotTaken.h"

bool AlwaysNotTaken::predict(uint64_t){
    return false;
}

void AlwaysNotTaken::update(uint64_t,bool){}
void AlwaysNotTaken::reset(){}
std::string AlwaysNotTaken::name() const{
    return "Always Not Taken";

}