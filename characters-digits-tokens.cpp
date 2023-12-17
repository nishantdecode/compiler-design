#include <iostream>

using namespace std;

bool isAlphabet(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

void identifyTokens(const string &inputString) {
    cout << "Tokens in the given string:" << endl;

    for (char ch : inputString) {
        if (isAlphabet(ch)) {
            cout << "Character: " << ch << endl;
        } else if (isDigit(ch)) {
            cout << "Digit: " << ch << endl;
        }
        // Ignore other characters
    }
}

int main() {
    cout << "Enter a string: ";
    string inputString;
    getline(cin, inputString);

    identifyTokens(inputString);

    return 0;
}