#include "document_loader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<Document> loadDocuments(const string& directory){
    vector<Document> files;

    int docID = 0;

    for(const auto& entry : filesystem::directory_iterator(directory)){
        if(!(entry.is_regular_file())){
            continue;
        }

        ifstream file(entry.path());

        if(!(file.is_open())){
            cerr << "Could not open: " << entry.path().filename().string() << endl;
            continue;
        }

        stringstream buffer;
        buffer << file.rdbuf();

        Document document;
        document.id = docID++;
        document.filename = entry.path().filename().string();
        document.content = buffer.str();

        files.push_back(document);
    }

    return files;
}