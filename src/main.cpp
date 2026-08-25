#include <iostream>

#include "document_loader.hpp"
#include "tokenizer.hpp"

using namespace std;

int main() {
    cout << "C++ Search Engine" << endl;
    cout << "=================" << endl;

    vector<Document> documents = loadDocuments("data");

    cout << "Documents indexed: "
              << documents.size()
              << endl;

    for (const Document& document : documents) {
        cout << "[" << document.id << "] "
                  << document.filename
                  << endl;
    }

    string text = "Computer Science is FUN!";
    vector<string> tokens = tokenize(text);

    for (const string& token : tokens) {
        cout << token << endl;
    }

    return 0;
}