#ifndef METRICS_H
#define METRICS_H

#include <cstdint>

struct Metrics{

    uint64_t branches=0;

    uint64_t correct=0;

    uint64_t incorrect=0;

    double accuracy() const;

    double mpki() const;

    double ipc(int penalty=5) const;

};

#endif