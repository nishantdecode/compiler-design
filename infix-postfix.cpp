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

string infixToPostfix(const string &infix) {
    string postfix;
    string stack;

    for (char ch : infix) {
        if (isOperand(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack += ch;
        } else if (ch == ')') {
            while (!stack.empty() && stack.back() != '(') {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.pop_back();  // Pop the corresponding '('
        } else if (isOperator(ch)) {
            while (!stack.empty() && getPrecedence(stack.back()) >= getPrecedence(ch)) {
                postfix += stack.back();
                stack.pop_back();
            }
            stack += ch;
        }
    }

    while (!stack.empty()) {
        postfix += stack.back();
        stack.pop_back();
    }

    return postfix;
}

int main() {
    cout << "Enter an infix expression: ";
    string infixExpression;
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "Postfix expression: " << postfixExpression << endl;

    return 0;
}