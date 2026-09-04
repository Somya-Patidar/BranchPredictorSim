#ifndef TRACE_READER_H
#define TRACE_READER_H

#include <vector>
#include <string>
#include <cstdint>

struct Branch{
    uint64_t pc;
    bool taken;
};

class TraceReader{
public:
    static std::vector<Branch> read(const std::string& path);
};

#endif