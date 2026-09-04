#include "TraceReader.h"
#include <fstream>
#include <sstream>

std::vector<Branch> TraceReader::read(const std::string& path){
    std::ifstream file(path);
    std::vector<Branch> branches;
    std::string pc;
    char outcome;

    while(file>>pc>>outcome){
        Branch b;
        b.pc=std::stoull(pc,nullptr,16);
        b.taken=(outcome=='T');
        branches.push_back(b);

    }

    return branches;

}