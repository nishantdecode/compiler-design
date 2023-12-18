#include <iostream>
#include <stack>

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
    stack<char> operators;

    for (char ch : infix) {
        if (isOperand(ch)) {
            prefix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop(); // Discard the '('
        } else if (isOperator(ch)) {
            while (!operators.empty() && getPrecedence(operators.top()) > getPrecedence(ch)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    // Reverse the prefix expression
    return string(prefix.rbegin(), prefix.rend());
}

int main() {
    cout << "Enter an infix expression: ";
    string infixExpression;
    getline(cin, infixExpression);

    string prefixExpression = infixToPrefix(infixExpression);

    cout << "Prefix expression: " << prefixExpression << endl;

    return 0;
}