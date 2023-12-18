#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void calculateFirstSet(int x, int y, int N, vector<char> &first, vector<vector<char> > &firstMatrix, const vector<string> &productions) {
    if (y < N && productions[x][y] != '|' && !(productions[x][y] >= 'A' && productions[x][y] <= 'Z')) {
        first.push_back(productions[x][y]);
    }

    if (y < N && (productions[x][y] >= 'A' && productions[x][y] <= 'Z')) {
        int n = firstMatrix.size();
        for (int i = 0; i < n; i++) {
            if (firstMatrix[i][0] == productions[x][y]) {
                int m = firstMatrix[i].size();
                for (int j = 1; j < m; j++) {
                    if (firstMatrix[i][j] == '^') {
                        if (y < N - 1 && productions[x][y + 1] != '|') {
                            calculateFirstSet(x, y + 1, N, first, firstMatrix, productions);
                        } else {
                            first.push_back('^');
                        }
                    } else {
                        first.push_back(firstMatrix[i][j]);
                    }
                }
            }
        }
    }
}

void removeDuplicates(int n, vector<vector<char> > &firstMatrix) {
    for (int i = 0; i < n; i++) {
        sort(firstMatrix[i].begin() + 1, firstMatrix[i].end());
        cout << "\nFirst(" << firstMatrix[i][0] << ") = {";
        int m = firstMatrix[i].size();
        for (int j = 1; j < m; j++) {
            if (firstMatrix[i][j] != firstMatrix[i][j - 1]) {
                cout << firstMatrix[i][j] << ",";
            }
        }
        if (m > 1) {
            cout << "\b}";
        } else {
            cout << "}";
        }
    }
    return;
}

int main() {
    vector<string> productions;
    string s;

    cout << "Enter the grammar (use ^ as null character)\nType 'end' to stop entering productions\n\n";

    while (true) {
        cin >> s;
        if (s == "end") {
            break;
        }
        if (s[0] < 'A' || s[0] > 'Z' || s[1] != '-' || s[2] != '>') {
            cout << "Invalid grammar";
            break;
        }
        productions.push_back(s);
    }

    int n = productions.size();
    vector<vector<char> > firstMatrix;
    vector<char> first;

    for (int i = n - 1; i > -1; i--) {
        first.push_back(productions[i][0]);
        int m = productions[i].size();
        for (int j = 1; j < m; j++) {
            if (productions[i][j] == '>' || productions[i][j] == '|') {
                calculateFirstSet(i, j + 1, m, first, firstMatrix, productions);
            }
        }
        firstMatrix.push_back(first);
        first.clear();
    }

    removeDuplicates(n, firstMatrix);

    return 0;
}