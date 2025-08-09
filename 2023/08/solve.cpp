#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool is_finished(const vector<string>& v) {
    return all_of(v.begin(), v.end(),
                  [](const auto& s) { return s[2] == 'Z'; });
}

int n_to_idx(const string& s) {
    return s[0] - 'A' + 26 * (s[1] - 'A') + 26 * 26 * (s[2] - 'A');
}

ll find_steps(string c, const string& instruct,
              const vector<pair<string, string>>& nodes) {
    ll steps = 0;
    while (c[2] != 'Z') {
        for (char ins : instruct) {
            if (ins == 'L') {
                c = nodes[n_to_idx(c)].first;
            } else {
                c = nodes[n_to_idx(c)].second;
            }
            steps++;
            if (c[2] == 'Z')
                break;
        }
    }
    return steps;
}

int main() {
    std::string instructions;
    getline(cin, instructions);
    vector<pair<string, string>> nodes(26 * 26 * 26);
    string node, left, right;
    char tmp;
    vector<string> curr;
    while (cin >> node >> tmp >> tmp >> left >> right) {
        nodes[n_to_idx(node)] = {left.substr(0, 3), right.substr(0, 3)};
        if (node[2] == 'A')
            curr.push_back(node);
    }

    ll steps = 1;
    for (auto& c : curr) {
        steps = lcm(steps, find_steps(c, instructions, nodes));
    }
    cout << steps << endl;
}
