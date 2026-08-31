#include "inverted_index.hpp"

using namespace std;

void InvertedIndex::add(
    const string& token,
    int documentId
) {
    index[token][documentId]++;
}

vector<int> InvertedIndex::search(
    const string& token
) const {
    vector<int> results;

    auto it = index.find(token);

    if (it != index.end()) {
        for (const auto& pair : it->second) {
            results.push_back(pair.first);
        }
    }

    return results;
}

int InvertedIndex::getTermFrequency(
    const string& token,
    int documentId
) const {
    auto tokenIt = index.find(token);

    if (tokenIt == index.end()) {
        return 0;
    }

    auto documentIt =
        tokenIt->second.find(documentId);

    if (documentIt == tokenIt->second.end()) {
        return 0;
    }

    return documentIt->second;
}

int InvertedIndex::getDocumentFrequency(
    const string& token
) const {
    auto it = index.find(token);

    if (it == index.end()) {
        return 0;
    }

    return it->second.size();
}

void InvertedIndex::merge(const InvertedIndex& other){
    for (const auto& tokenEntry : other.index) {
        const string& token = tokenEntry.first;

        for (const auto& documentEntry : tokenEntry.second) {
            int documentId = documentEntry.first;
            int frequency = documentEntry.second;

            index[token][documentId] += frequency;
        }
    }
}