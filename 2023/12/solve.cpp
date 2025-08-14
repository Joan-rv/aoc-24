#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool is_valid(const string& springs, const vector<ll>& ranges) {
    vector<ll> found{0};
    for (char c : springs) {
        if (c == '#')
            found.back()++;
        else {
            if (found.back() != 0)
                found.push_back(0);
        }
    }
    if (found.back() == 0)
        found.pop_back();
    return ranges == found;
}

ll brute(string& springs, ll idx, const vector<ll>& ranges) {
    for (ll i = idx; i < springs.size(); i++) {
        if (springs[i] == '?') {
            springs[i] = '.';
            ll ret = brute(springs, i + 1, ranges);
            springs[i] = '#';
            ret += brute(springs, i + 1, ranges);
            springs[i] = '?';
            return ret;
        }
    }
    return is_valid(springs, ranges) ? 1 : 0;
}

map<pair<string, vector<ll>>, ll> memo;

ll fast(string springs, vector<ll> ranges, bool in_group) {
    if (memo.count({springs, ranges})) {
        return memo[{springs, ranges}];
    }
    if (springs.empty() &&
        (ranges.empty() || ranges.size() == 1 && ranges[0] == 0))
        return 1;
    if (springs[0] == '.') {
        if (in_group && (!ranges.empty() && ranges[0] != 0))
            return 0;
        if (!ranges.empty() && ranges[0] == 0) {
            vector<ll> after(ranges.begin() + 1, ranges.end());
            ll ret = fast(springs.substr(1), after, false);
            memo[{springs, ranges}] = ret;
            return ret;
        } else {
            ll ret = fast(springs.substr(1), ranges, false);
            memo[{springs, ranges}] = ret;
            return ret;
        }
    }
    if (springs[0] == '#') {
        if (ranges.empty())
            return 0;
        ranges[0]--;
        ll ret = fast(springs.substr(1), ranges, true);
        ranges[0]++;
        memo[{springs, ranges}] = ret;
        return ret;
    }
    if (springs[0] == '?') {
        if (in_group) {
            if (!ranges.empty() && ranges[0] == 0) {
                vector<ll> after(ranges.begin() + 1, ranges.end());
                ll ret = fast(springs.substr(1), after, false);
                memo[{springs, ranges}] = ret;
                return ret;
            } else {
                ranges[0]--;
                ll ret = fast(springs.substr(1), ranges, true);
                ranges[0]++;
                memo[{springs, ranges}] = ret;
                return ret;
            }
        } else {
            ll ret1 = fast(springs.substr(1), ranges, false);
            if (!ranges.empty()) {
                ranges[0]--;
                ll ret = ret1 + fast(springs.substr(1), ranges, true);
                ranges[0]++;
                memo[{springs, ranges}] = ret;
                return ret;
            }
            memo[{springs, ranges}] = ret1;
            return ret1;
        }
    }

    return 0;
}

ll num_of_aranges(const string& line) {
    ll space_pos = line.find(' ');
    string springs = line.substr(0, space_pos);
    string sranges = line.substr(space_pos + 1);
    vector<ll> ranges;
    istringstream iranges(sranges);
    ll range;
    while (iranges >> range) {
        ranges.push_back(range);
        iranges.ignore(1, ',');
    }

    // return fast(springs, ranges, false);
    auto osprings = springs;
    auto oranges = ranges;
    for (int i = 0; i < 4; i++) {
        springs += '?';
        springs += osprings;
        ranges.insert(ranges.end(), oranges.begin(), oranges.end());
    }
    memo.clear();
    return fast(springs, ranges, false);
}

int main() {
    string line;
    ll res = 0;
    ll line_idx = 0;
    while (getline(cin, line)) {
        res += num_of_aranges(line);
        cout << "line " << ++line_idx << '\r';
    }
    cout << res << endl;
    return 0;
}
