#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> read_seq() {
    string line;
    getline(cin, line);
    istringstream iline(line);
    ll x;
    vector<ll> seq;
    while (iline >> x)
        seq.push_back(x);
    return seq;
}

bool finished(const vector<ll>& seq) {
    return all_of(seq.begin(), seq.end(), [](auto& v) { return v == 0; });
}

ll extend_seq(vector<ll> seq) {
    reverse(seq.begin(), seq.end());
    vector<vector<ll>> seqs{std::move(seq)};
    while (!finished(seqs.back())) {
        seqs.push_back(vector<ll>(seqs.back().size() - 1));
        auto& prev = seqs[seqs.size() - 2];
        for (size_t i = 0; i < seqs.back().size(); i++) {
            seqs.back()[i] = prev[i + 1] - prev[i];
        }
    }
    seqs.back().push_back(0);
    for (size_t i = seqs.size() - 1; i-- > 0;) {
        seqs[i].push_back(seqs[i].back() + seqs[i + 1].back());
    }
    return seqs[0].back();
}

int main() {
    vector<ll> seq;
    ll sum = 0;
    while (!cin.eof()) {
        seq = read_seq();
        sum += extend_seq(std::move(seq));
    }
    cout << sum << endl;
    return 0;
}
