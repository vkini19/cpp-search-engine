#include "inverted_index.hpp"

#include <algorithm>

using namespace std;

void InvertedIndex::add(const std::string& token, int documentId) {
    vector<int>& documents = index[token];

    if (find(documents.begin(), documents.end(), documentId)
        == documents.end()) {
        documents.push_back(documentId);
    }
}

vector<int> InvertedIndex::search(
    const string& token) const {

    auto it = index.find(token);

    if (it != index.end()) {
        return it->second;
    }

    return {};
}