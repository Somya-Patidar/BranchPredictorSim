#include "Metrics.h"

double Metrics::accuracy() const{

    if(branches==0) return 0;

    return 100.0*correct/branches;

}

double Metrics::mpki() const{

    if(branches==0) return 0;

    return 1000.0*incorrect/branches;

}

double Metrics::ipc(int penalty) const{

    if(branches==0) return 0;

    return branches/(double)(branches+incorrect*penalty);

}