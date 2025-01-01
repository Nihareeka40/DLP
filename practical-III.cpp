#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set>
#include <vector>
using namespace std;

const unordered_set<string> keywords = {
    "int", "char", "return", "if", "else", "while", "for", "float", "double", "void", "main"
};

void analyze(const string &code) {
    regex keyword_regex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b");
    regex punctuation_regex("[{}();=,]|'.'");
    regex error_regex("\\b[a-zA-Z_][a-zA-Z0-9_]*[0-9]+\\b|\\b[0-9]+[a-zA-Z_]+\\b|[^\\s]+@");

    int keyword_count = 0, punctuation_count = 0;
    vector<string> keywords_found, punctuations_found, errors_found;

    for (sregex_iterator it(code.begin(), code.end(), keyword_regex), end; it != end; ++it) {
        string token = (*it).str();
        if (keywords.count(token)) {
            keyword_count++;
            keywords_found.push_back(token);
        }
    }

    for (sregex_iterator it(code.begin(), code.end(), punctuation_regex), end; it != end; ++it) {
        punctuation_count++;
        punctuations_found.push_back((*it).str());
    }

    for (sregex_iterator it(code.begin(), code.end(), error_regex), end; it != end; ++it) {
        errors_found.push_back((*it).str());
    }

    cout << "Keywords found (" << keyword_count << "): ";
    for (const auto &kw : keywords_found) cout << kw << " ";
    cout << "\nPunctuation marks found (" << punctuation_count << "): ";
    for (const auto &p : punctuations_found) cout << p << " ";
    cout << "\nErrors found (" << errors_found.size() << "): ";
    for (const auto &e : errors_found) cout << e << " ";
    cout << endl;
}

int main() {
    ifstream input("input.c");
    if (!input) { cerr << "Error: Cannot open file." << endl; return 1; }

    string code((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    analyze(code);
    return 0;
}
