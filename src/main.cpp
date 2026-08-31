#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <omp.h>

#include "document_loader.hpp"
#include "tokenizer.hpp"
#include "inverted_index.hpp"
#include "ranker.hpp"

using namespace std;

int main() {
    cout << "C++ Search Engine" << endl;
    cout << "=================" << endl;

    // Load documents
    auto loadStart = chrono::high_resolution_clock::now();

    vector<Document> documents = loadDocuments("data");

    auto loadEnd = chrono::high_resolution_clock::now();

    chrono::duration<double> loadTime =
        loadEnd - loadStart;

    cout << "Documents indexed: "
         << documents.size()
         << endl;

    cout << fixed << setprecision(6);
    cout << "Document loading time: "
         << loadTime.count() * 1000
         << "ms"
         << endl;

    // Calculate document lengths
    vector<int> documentLengths;

    for (const Document& document : documents) {
        vector<string> tokens =
            tokenize(document.content);

        documentLengths.push_back(tokens.size());
    }

    auto indexStart =
    chrono::high_resolution_clock::now();

    int threadCount = omp_get_max_threads();

    vector<InvertedIndex> localIndexes(threadCount);

    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();

        #pragma omp for
        for (int i = 0;
            i < static_cast<int>(documents.size());
            i++) {

            vector<string> tokens =
                tokenize(documents[i].content);

            for (const string& token : tokens) {
                localIndexes[threadId].add(
                    token,
                    documents[i].id
                );
            }
        }
    }

    InvertedIndex index;

    for (const InvertedIndex& localIndex : localIndexes) {
        index.merge(localIndex);
    }

    auto indexEnd =
        chrono::high_resolution_clock::now();

    chrono::duration<double> indexTime =
        indexEnd - indexStart;

    cout << "Indexing time: "
        << indexTime.count() * 1000
        << "ms"
        << endl;

    cout << "Threads used: "
        << threadCount
        << endl;

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

        auto queryStart =
            chrono::high_resolution_clock::now();

        vector<string> queryTokens =
            tokenize(query);

        if (queryTokens.empty()) {
            cout << "Please enter a valid search query."
                 << endl;
            continue;
        }

        vector<int> results =
            index.search(queryTokens[0]);

        // AND search
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

        sort(
            rankedResults.begin(),
            rankedResults.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            }
        );

        auto queryEnd =
            chrono::high_resolution_clock::now();

        chrono::duration<double> queryTime =
            queryEnd - queryStart;

        if (rankedResults.empty()) {
            cout << "No results found." << endl;
        } else {
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

        cout << "Query time: "
             << queryTime.count() * 1000
             << "ms"
             << endl;
    }

    cout << "\nGoodbye!" << endl;

    return 0;
}