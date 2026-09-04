#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Branch {
    uint64_t pc;
    bool taken;
};

class TraceReader {
public:
    bool load(const std::string& filename);

    const std::vector<Branch>& branches() const;

private:
    std::vector<Branch> trace;
};