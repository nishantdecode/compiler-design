#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> productions;

void leftFactor(char nonTerminal) {
    size_t nonTerminalIndex = nonTerminal - 'A';

    // Separate the productions into groups based on the common prefix
    vector<string> commonPrefixGroup;
    vector<string> remainingProductions;

    for (const string& production : productions[nonTerminalIndex]) {
        if (production[0] == productions[nonTerminalIndex][0][0]) {
            commonPrefixGroup.push_back(production.substr(1));
        } else {
            remainingProductions.push_back(production);
        }
    }

    // Display the left-factored productions
    cout << nonTerminal << " → " << productions[nonTerminalIndex][0][0] << "(";

    for (const string& production : commonPrefixGroup) {
        cout << production << " | ";
    }

    cout << "\b\b)" << endl;

    // Recursively apply left factoring for the remaining productions
    for (const string& remainingProduction : remainingProductions) {
        productions.push_back({remainingProduction});
        leftFactor(char(productions.size() - 1 + 'A'));
    }
}

int main() {
    // Initialize the original grammar productions
    productions = {{"abX", "acY"}};

    // Perform left factoring for each non-terminal
    for (char nonTerminal = 'A'; nonTerminal < 'A' + productions.size(); ++nonTerminal) {
        leftFactor(nonTerminal);
    }

    return 0;
}