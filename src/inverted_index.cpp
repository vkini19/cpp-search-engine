#include "inverted_index.hpp"

void InvertedIndex::add(
    const std::string& token,
    int documentId
) {
    index[token][documentId]++;
}

std::vector<int> InvertedIndex::search(
    const std::string& token
) const {
    std::vector<int> results;

    auto it = index.find(token);

    if (it != index.end()) {
        for (const auto& pair : it->second) {
            results.push_back(pair.first);
        }
    }

    return results;
}

int InvertedIndex::getTermFrequency(
    const std::string& token,
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
    const std::string& token
) const {
    auto it = index.find(token);

    if (it == index.end()) {
        return 0;
    }

    return it->second.size();
}