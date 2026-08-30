#include "ranker.hpp"

#include <cmath>

Ranker::Ranker(
    const InvertedIndex& index,
    int totalDocuments,
    const vector<int>& documentLengths
)
    : index(index),
      totalDocuments(totalDocuments),
      documentLengths(documentLengths),
      averageDocumentLength(0.0) {

    for (int length : documentLengths) {
        averageDocumentLength += length;
    }

    if (!documentLengths.empty()) {
        averageDocumentLength /=
            documentLengths.size();
    }
}

double Ranker::calculateTFIDF(
    const string& token,
    int documentId
) const {
    int termFrequency =
        index.getTermFrequency(token, documentId);

    int documentFrequency =
        index.getDocumentFrequency(token);

    if (termFrequency == 0 ||
        documentFrequency == 0) {
        return 0.0;
    }

    double idf = log(
        static_cast<double>(totalDocuments)
        / documentFrequency
    );

    return termFrequency * idf;
}

double Ranker::calculateBM25(
    const string& token,
    int documentId
) const {
    const double k1 = 1.2;
    const double b = 0.75;

    int termFrequency =
        index.getTermFrequency(token, documentId);

    int documentFrequency =
        index.getDocumentFrequency(token);

    if (termFrequency == 0 ||
        documentFrequency == 0 ||
        averageDocumentLength == 0.0) {
        return 0.0;
    }

    double documentLength =
        documentLengths[documentId];

    double idf = log(
        (totalDocuments - documentFrequency + 0.5)
        / (documentFrequency + 0.5)
        + 1.0
    );

    double numerator =
        termFrequency * (k1 + 1.0);

    double denominator =
        termFrequency
        + k1 * (
            1.0
            - b
            + b * (
                documentLength
                / averageDocumentLength
            )
        );

    return idf * (numerator / denominator);
}

double Ranker::scoreDocument(
    const vector<string>& queryTokens,
    int documentId
) const {
    double score = 0.0;

    for (const string& token : queryTokens) {
        score += calculateBM25(
            token,
            documentId
        );
    }

    return score;
}