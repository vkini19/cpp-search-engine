#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class InvertedIndex {
private:
    unordered_map<std::string, std::vector<int>> index;

public:
    void add(const std::string& token, int documentId);

    vector<int> search(const std::string& token) const;
};

#endif