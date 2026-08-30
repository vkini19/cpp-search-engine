#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <string>
#include <unordered_map>
#include <vector>

class InvertedIndex {
private:
    // word -> (document ID -> frequency)
    std::unordered_map<std::string,
        std::unordered_map<int, int>> index;

public:
    void add(const std::string& token, int documentId);

    std::vector<int> search(const std::string& token) const;

    int getTermFrequency(
        const std::string& token,
        int documentId
    ) const;

    int getDocumentFrequency(
        const std::string& token
    ) const;
};

#endif