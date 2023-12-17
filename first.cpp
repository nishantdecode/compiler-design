#include <iostream>
#include <vector>

using namespace std;

const int MAX_NON_TERMINALS = 26;

vector<vector<string>> productions;
vector<vector<bool>> firstSets(MAX_NON_TERMINALS, vector<bool>(26, false));

void calculateFirst(char nonTerminal) {
    size_t nonTerminalIndex = nonTerminal - 'A';

    if (firstSets[nonTerminalIndex][nonTerminal - 'A']) {
        // If FIRST set for this non-terminal is already calculated, return
        return;
    }

    for (const string& production : productions[nonTerminalIndex]) {
        char firstSymbol = production[0];

        if (isupper(firstSymbol)) {
            // If the first symbol is a non-terminal, calculate FIRST for that non-terminal
            calculateFirst(firstSymbol);

            // Add FIRST(non-terminal) to FIRST(current non-terminal)
            for (int i = 0; i < 26; ++i) {
                if (firstSets[firstSymbol - 'A'][i]) {
                    firstSets[nonTerminalIndex][i] = true;
                }
            }

            // If epsilon is in FIRST(non-terminal), consider the next symbol
            if (firstSets[firstSymbol - 'A']['$' - 'A']) {
                size_t i = 1;
                while (i < production.size() && firstSets[firstSymbol - 'A'][production[i] - 'A']) {
                    firstSets[nonTerminalIndex][production[i] - 'A'] = true;
                    ++i;
                }
            }
        } else {
            // If the first symbol is a terminal, add it to FIRST(current non-terminal)
            firstSets[nonTerminalIndex][firstSymbol - 'A'] = true;
        }
    }
}

int main() {
    // Initialize the grammar productions
    productions = {{"Ba", "Cd", "ef"}, {"gh", "i"}};

    // Calculate FIRST for each non-terminal
    calculateFirst('A');
    calculateFirst('B');
    calculateFirst('C');

    // Display the calculated FIRST sets
    for (char nonTerminal = 'A'; nonTerminal <= 'C'; ++nonTerminal) {
        cout << "FIRST(" << nonTerminal << "): { ";
        for (char terminal = 'A'; terminal <= 'Z'; ++terminal) {
            if (firstSets[nonTerminal - 'A'][terminal - 'A']) {
                cout << terminal << ' ';
            }
        }
        cout << "}\n";
    }

    return 0;
}