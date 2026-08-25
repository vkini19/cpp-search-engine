#include "tokenizer.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

vector<string> tokenize(const string& text) {
    vector<string> tokens;
    istringstream stream(text);
    string word;

    while (stream >> word) {
        // Convert each character to lowercase
        transform(
            word.begin(),
            word.end(),
            word.begin(),
            [](unsigned char c) {
                return tolower(c);
            }
        );

        // Remove punctuation
        word.erase(
            remove_if(
                word.begin(),
                word.end(),
                [](unsigned char c) {
                    return ispunct(c);
                }
            ),
            word.end()
        );

        // Don't add empty tokens
        if (!word.empty()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}