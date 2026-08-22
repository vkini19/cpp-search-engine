#include <iostream>

#include "document_loader.hpp"

int main() {
    std::cout << "C++ Search Engine" << std::endl;
    std::cout << "=================" << std::endl;

    std::vector<Document> documents = loadDocuments("data");

    std::cout << "Documents indexed: "
              << documents.size()
              << std::endl;

    for (const Document& document : documents) {
        std::cout << "[" << document.id << "] "
                  << document.filename
                  << std::endl;
    }

    return 0;
}