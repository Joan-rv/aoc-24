#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct C {
    ll x, y;
};

int main() {
    vector<C> coords;
    string line;
    vector<string> grid;
    ll row = 0;
    ll m;
    while (getline(cin, line)) {
        ll col = 0;
        for (auto c : line) {
            if (c == '#')
                coords.push_back({col, row});
            col++;
        }
        grid.push_back(std::move(line));
        m = col;
        row++;
    }
    ll n = row;
    vector<bool> free_col(m);
    for (ll j = 0; j < m; j++) {
        bool is_free = true;
        for (ll i = 0; i < n && is_free; i++) {
            if (grid[i][j] == '#')
                is_free = false;
        }
        free_col[j] = is_free;
    }
    vector<bool> free_row(n);
    for (ll i = 0; i < n; i++) {
        bool is_free = true;
        for (ll j = 0; j < m && is_free; j++) {
            if (grid[i][j] == '#')
                is_free = false;
        }
        free_row[i] = is_free;
    }
    const ll size_delta = 999999;
    // const ll size_delta = 99;
    vector<ll> delta_col(m);
    delta_col[0] = free_col[0] ? size_delta : 0;
    for (ll j = 1; j < m; j++) {
        delta_col[j] = delta_col[j - 1] + (free_col[j] ? size_delta : 0);
    }
    vector<ll> delta_row(n);
    delta_row[0] = free_row[0] ? size_delta : 0;
    for (ll i = 1; i < n; i++) {
        delta_row[i] = delta_row[i - 1] + (free_row[i] ? size_delta : 0);
    }
    for (auto& c : coords) {
        c.x += delta_col[c.x];
        c.y += delta_row[c.y];
    }

    ll res = 0;
    for (ll i = 0; i < coords.size(); i++) {
        for (ll j = i + 1; j < coords.size(); j++) {
            auto& c1 = coords[i];
            auto& c2 = coords[j];
            res += abs(c1.x - c2.x) + abs(c1.y - c2.y);
        }
    }
    cout << res << endl;

    return 0;
}
