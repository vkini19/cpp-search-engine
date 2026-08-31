#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class InvertedIndex {
private:
    // word -> (document ID -> frequency)
    unordered_map<string,
        unordered_map<int, int>> index;

public:
    void add(const string& token, int documentId);

    vector<int> search(const string& token) const;

    int getTermFrequency(
        const string& token,
        int documentId
    ) const;

    int getDocumentFrequency(
        const string& token
    ) const;

    void merge(const InvertedIndex& other);
};

#endif