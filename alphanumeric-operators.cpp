#include <iostream>

using namespace std;

bool isAlphanumeric(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=');
}

void identifyTokens(const string &inputString) {
    cout << "Tokens in the given string:" << endl;

    for (char ch : inputString) {
        if (isAlphanumeric(ch)) {
            cout << "Alphanumeric: " << ch << endl;
        } else if (isOperator(ch)) {
            cout << "Operator: " << ch << endl;
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