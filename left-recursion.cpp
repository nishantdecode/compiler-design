#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> productions;

void eliminateLeftRecursion(char nonTerminal) {
    size_t nonTerminalIndex = nonTerminal - 'A';

    // Separate the productions into groups: those with left recursion and those without
    vector<string> leftRecursiveProductions;
    vector<string> nonLeftRecursiveProductions;

    for (const string& production : productions[nonTerminalIndex]) {
        if (production[0] == nonTerminal) {
            leftRecursiveProductions.push_back(production.substr(1));
        } else {
            nonLeftRecursiveProductions.push_back(production);
        }
    }

    // Display the non-left-recursive productions
    cout << nonTerminal << " → ";

    for (const string& production : nonLeftRecursiveProductions) {
        cout << production << " | ";
    }

    cout << nonTerminal << "'" << endl;

    // Display the left-recursion elimination for this non-terminal
    cout << nonTerminal << "' → ";

    for (const string& production : leftRecursiveProductions) {
        cout << production << nonTerminal << "' | ";
    }

    cout << "ε" << endl;
}

int main() {
    // Initialize the original grammar productions
    productions = {{"Aa", "b"}};

    // Perform left recursion elimination for each non-terminal
    for (char nonTerminal = 'A'; nonTerminal < 'A' + productions.size(); ++nonTerminal) {
        eliminateLeftRecursion(nonTerminal);
    }

    return 0;
}