#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void remove_lf(int x, vector<string> &productions, int &comma) {
    int m = productions[x].size();
    vector<string> prod_rule;

    for (int j = 0; j < m; j++) {
        if (productions[x][j] == '>' || productions[x][j] == '|') {
            j++;
            int k = j;
            while (productions[x][k] != '|' && k < m) {
                k++;
            }
            if (k - j > 0) {
                prod_rule.push_back(productions[x].substr(j, k - j));
            }
        }
    }

    sort(prod_rule.begin(), prod_rule.end());

    int k = 0;
    while (productions[x][k] != '-') {
        k++;
    }

    string s1 = productions[x].substr(0, k) + "->";

    int n = prod_rule.size();

    if (n == 1) {
        s1 += prod_rule[0];
    } else {
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && prod_rule[i][0] != prod_rule[i + 1][0]) {
                s1 += prod_rule[i] + "|";
            } else {
                if (i == n - 1) {
                    if (prod_rule[i][0] != prod_rule[i - 1][0]) {
                        s1 += prod_rule[i];
                    }
                    break;
                }

                s1 += prod_rule[i][0] + productions[x].substr(0, k) + "'";
                string s2 = productions[x].substr(0, k) + "'";
                s1 += "|";
                s2 += "->";

                char c = prod_rule[i][0];

                while (i < n && prod_rule[i][0] == c) {
                    if (prod_rule[i].size() > 1) {
                        s2 += prod_rule[i].substr(1);
                    } else {
                        s2 += "^";
                    }

                    s2 += "|";
                    i++;
                }

                productions.insert(productions.begin() + x + 1, s2);
                comma++;
                i--;
            }
        }
    }

    if (!s1.empty() && s1.back() == '|') {
        s1.pop_back();
    }

    if (!s1.empty() && s1 != productions[x]) {
        productions.insert(productions.begin() + x + 1, s1);
        productions.erase(productions.begin() + x);
    }
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
            return 0;
        }

        productions.push_back(s);
    }

    int comma = 1;

    for (int i = 0; i < productions.size(); i++) {
        remove_lf(i, productions, comma);
    }

    cout << "\nGrammar after left factoring:\n";

    for (int i = 0; i < productions.size(); i++) {
        cout << productions[i] << "\n";
    }

    return 0;
}