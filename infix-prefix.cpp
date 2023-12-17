#include <iostream>

using namespace std;

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int getPrecedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

bool isOperand(char ch) {
    return (isalpha(ch) || isdigit(ch));
}

string infixToPrefix(const string &infix) {
    string prefix;
    string reversedInfix = string(infix.rbegin(), infix.rend());

    for (char ch : reversedInfix) {
        if (isOperand(ch)) {
            prefix = ch + prefix;
        } else if (ch == ')') {
            int count = 1;
            while (count > 0) {
                char currentChar = reversedInfix[0];
                reversedInfix = reversedInfix.substr(1);
                if (currentChar == ')') {
                    count++;
                } else if (currentChar == '(') {
                    count--;
                }
                if (count > 0) {
                    prefix = currentChar + prefix;
                }
            }
        } else if (ch == '(') {
            int count = 1;
            while (count > 0) {
                char currentChar = reversedInfix[0];
                reversedInfix = reversedInfix.substr(1);
                if (currentChar == '(') {
                    count++;
                } else if (currentChar == ')') {
                    count--;
                }
                if (count > 0) {
                    prefix = currentChar + prefix;
                }
            }
        } else if (isOperator(ch)) {
            while (!reversedInfix.empty() && getPrecedence(reversedInfix[0]) > getPrecedence(ch)) {
                prefix = reversedInfix[0] + prefix;
                reversedInfix = reversedInfix.substr(1);
            }
            prefix = ch + prefix;
        }
    }

    return prefix;
}

int main() {
    cout << "Enter an infix expression: ";
    string infixExpression;
    getline(cin, infixExpression);

    string prefixExpression = infixToPrefix(infixExpression);

    cout << "Prefix expression: " << prefixExpression << endl;

    return 0;
}