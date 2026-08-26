#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "document_loader.hpp"
#include "tokenizer.hpp"
#include "inverted_index.hpp"

using namespace std;

int main() {
    cout << "C++ Search Engine" << endl;
    cout << "=================" << endl;

    // Load all documents
    vector<Document> documents = loadDocuments("data");

    cout << "Documents indexed: "
         << documents.size()
         << endl;

    // Build the inverted index
    InvertedIndex index;

    for (const Document& document : documents) {
        vector<string> tokens = tokenize(document.content);

        for (const string& token : tokens) {
            index.add(token, document.id);
        }
    }

    // Interactive search loop
    while (true) {
        string query;

        cout << "\nEnter search query (or 'exit'): ";
        getline(cin, query);

        if (query == "exit") {
            break;
        }

        // Tokenize the user's query
        vector<string> queryTokens = tokenize(query);

        if (queryTokens.empty()) {
            cout << "Please enter a valid search query." << endl;
            continue;
        }

        // Start with results from the first word
        vector<int> results = index.search(queryTokens[0]);

        // For every additional word, keep only documents
        // that contain BOTH words
        for (size_t i = 1; i < queryTokens.size(); i++) {
            vector<int> nextResults = index.search(queryTokens[i]);
            vector<int> intersection;

            for (int documentId : results) {
                if (find(nextResults.begin(),
                         nextResults.end(),
                         documentId) != nextResults.end()) {
                    intersection.push_back(documentId);
                }
            }

            results = intersection;
        }

        // Display results
        if (results.empty()) {
            cout << "No results found." << endl;
        } else {
            cout << "\nResults:" << endl;

            for (int documentId : results) {
                cout << "- "
                     << documents[documentId].filename
                     << endl;
            }
        }
    }

    cout << "\nGoodbye!" << endl;

    return 0;
}