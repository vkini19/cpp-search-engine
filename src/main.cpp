#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "document_loader.hpp"
#include "tokenizer.hpp"
#include "inverted_index.hpp"
#include "ranker.hpp"

using namespace std;

int main() {
    cout << "C++ Search Engine" << endl;
    cout << "=================" << endl;

    // Load documents
    vector<Document> documents = loadDocuments("data");

    cout << "Documents indexed: "
         << documents.size()
         << endl;

    // Calculate document lengths
    vector<int> documentLengths;

    for (const Document& document : documents) {
        vector<string> tokens =
            tokenize(document.content);

        documentLengths.push_back(tokens.size());
    }

    // Build inverted index
    InvertedIndex index;

    for (const Document& document : documents) {
        vector<string> tokens =
            tokenize(document.content);

        for (const string& token : tokens) {
            index.add(token, document.id);
        }
    }

    // Create BM25 ranker
    Ranker ranker(
        index,
        documents.size(),
        documentLengths
    );

    // Interactive search
    while (true) {
        string query;

        cout << "\nEnter search query (or 'exit'): ";
        getline(cin, query);

        if (query == "exit") {
            break;
        }

        // Tokenize query
        vector<string> queryTokens =
            tokenize(query);

        if (queryTokens.empty()) {
            cout << "Please enter a valid search query."
                 << endl;
            continue;
        }

        // Find documents containing first term
        vector<int> results =
            index.search(queryTokens[0]);

        // AND search for additional terms
        for (size_t i = 1;
             i < queryTokens.size();
             i++) {

            vector<int> nextResults =
                index.search(queryTokens[i]);

            vector<int> intersection;

            for (int documentId : results) {
                if (find(
                        nextResults.begin(),
                        nextResults.end(),
                        documentId
                    ) != nextResults.end()) {

                    intersection.push_back(documentId);
                }
            }

            results = intersection;
        }

        if (results.empty()) {
            cout << "No results found." << endl;
            continue;
        }

        // Calculate BM25 scores
        vector<pair<int, double>> rankedResults;

        for (int documentId : results) {
            double score =
                ranker.scoreDocument(
                    queryTokens,
                    documentId
                );

            rankedResults.push_back(
                {documentId, score}
            );
        }

        // Sort highest score first
        sort(
            rankedResults.begin(),
            rankedResults.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            }
        );

        // Display results
        cout << "\nResults:" << endl;

        for (const auto& result : rankedResults) {
            int documentId = result.first;
            double score = result.second;

            cout << "- "
                 << documents[documentId].filename
                 << " | BM25 Score: "
                 << score
                 << endl;
        }
    }

    cout << "\nGoodbye!" << endl;

    return 0;
}