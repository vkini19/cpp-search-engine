#ifndef DOCUMENT_LOADER_HPP
#define DOCUMENT_LOADER_HPP

#include <string>
#include <vector>

struct Document {
    int id;
    std::string filename;
    std::string content;
};

std::vector<Document> loadDocuments(const std::string& directory);

#endif