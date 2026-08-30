#ifndef RANKER_HPP
#define RANKER_HPP

#include <string>
#include <vector>

#include "inverted_index.hpp"

using namespace std;

class Ranker {
private:
    const InvertedIndex& index;
    int totalDocuments;

    vector<int> documentLengths;
    double averageDocumentLength;

public:
    Ranker(
        const InvertedIndex& index,
        int totalDocuments,
        const vector<int>& documentLengths
    );

    double calculateTFIDF(
        const string& token,
        int documentId
    ) const;

    double calculateBM25(
        const string& token,
        int documentId
    ) const;

    double scoreDocument(
        const vector<string>& queryTokens,
        int documentId
    ) const;
};

#endif