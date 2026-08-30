#ifndef DOCUMENT_LOADER_HPP
#define DOCUMENT_LOADER_HPP

#include <string>
#include <vector>

using namespace std;

struct Document {
    int id;
    string filename;
    string content;
};

vector<Document> loadDocuments(const string& directory);

#endif