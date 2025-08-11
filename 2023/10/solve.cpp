#include <bits/stdc++.h>
#include <vector>

using namespace std;

typedef long long ll;

struct C {
    ll x, y;
};

bool operator==(const C& a, const C& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(const C& a, const C& b) { return !(a == b); }
bool operator<(const C& a, const C& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

vector<vector<bool>> vis;
vector<string> cmap;
ll n, m;
bool first = true;
vector<C> dfs(C ini, C curr) {
    if (curr == ini && !first)
        return {ini};
    first = false;
    if (curr.x < 0 || curr.y < 0 || curr.x >= m || curr.y >= n ||
        cmap[curr.y][curr.x] == '.' || vis[curr.y][curr.x])
        return {};
    vis[curr.y][curr.x] = true;
    vector<C> longest;
    auto visit = [&](C n_curr) {
        auto p = dfs(ini, n_curr);
        if (p.size() > longest.size())
            longest = std::move(p);
    };
    switch (cmap[curr.y][curr.x]) {
    case '|':
        visit({curr.x, curr.y + 1});
        visit({curr.x, curr.y - 1});
        break;
    case '-':
        visit({curr.x + 1, curr.y});
        visit({curr.x - 1, curr.y});
        break;
    case 'L':
        visit({curr.x, curr.y - 1});
        visit({curr.x + 1, curr.y});
        break;
    case 'J':
        visit({curr.x, curr.y - 1});
        visit({curr.x - 1, curr.y});
        break;
    case '7':
        visit({curr.x, curr.y + 1});
        visit({curr.x - 1, curr.y});
        break;
    case 'F':
        visit({curr.x, curr.y + 1});
        visit({curr.x + 1, curr.y});
        break;
    case 'S':
        visit({curr.x + 1, curr.y});
        visit({curr.x - 1, curr.y});
        visit({curr.x, curr.y + 1});
        visit({curr.x, curr.y - 1});
        break;
    default:
        break;
    }

    vis[curr.y][curr.x] = false;

    longest.push_back(curr);
    return longest;
}

vector<vector<ll>> bfs(C ini, const set<C>& path) {
    vector<vector<ll>> dist(n, vector<ll>(m, -1));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<pair<C, C>> to_vis{deque<pair<C, C>>{{ini, ini}}};
    while (!to_vis.empty()) {
        auto [coord, from] = to_vis.front();
        to_vis.pop();
        if (coord.x < 0 || coord.y < 0 || coord.x >= m || coord.y >= n ||
            cmap[coord.y][coord.x] == '.' || !path.count(coord))
            continue;
        if (vis[coord.y][coord.x])
            continue;
        ll d = dist[from.y][from.x];
        dist[coord.y][coord.x] = d + 1;
        vis[coord.y][coord.x] = true;
        switch (cmap[coord.y][coord.x]) {
        case '|':
            to_vis.push({{coord.x, coord.y + 1}, coord});
            to_vis.push({{coord.x, coord.y - 1}, coord});
            break;
        case '-':
            to_vis.push({{coord.x + 1, coord.y}, coord});
            to_vis.push({{coord.x - 1, coord.y}, coord});
            break;
        case 'L':
            to_vis.push({{coord.x, coord.y - 1}, coord});
            to_vis.push({{coord.x + 1, coord.y}, coord});
            break;
        case 'J':
            to_vis.push({{coord.x, coord.y - 1}, coord});
            to_vis.push({{coord.x - 1, coord.y}, coord});
            break;
        case '7':
            to_vis.push({{coord.x, coord.y + 1}, coord});
            to_vis.push({{coord.x - 1, coord.y}, coord});
            break;
        case 'F':
            to_vis.push({{coord.x, coord.y + 1}, coord});
            to_vis.push({{coord.x + 1, coord.y}, coord});
            break;
        case 'S':
            to_vis.push({{coord.x + 1, coord.y}, coord});
            to_vis.push({{coord.x - 1, coord.y}, coord});
            to_vis.push({{coord.x, coord.y + 1}, coord});
            to_vis.push({{coord.x, coord.y - 1}, coord});
            break;
        default:
            cout << "what" << endl;
            break;
        }
    }
    return dist;
}

void print(const set<C>& path) {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (path.count({j, i})) {
                cout << cmap[i][j];
            } else {
                cout << (cmap[i][j] == 'I' ? 'I' : '.');
            }
        }
        cout << '\n';
    }
    cout << endl;
}

bool is_inside(const set<C>& path, C tile) {
    ll arity = 0;
    char last{};
    while (tile.x < m) {
        tile.x++;
        char t = cmap[tile.y][tile.x];
        if (t == 'F' || t == 'L')
            last = t;
        if (path.count(tile)) {
            if (t == '|' || last == 'F' && t == 'J' || last == 'L' && t == '7')
                arity++;
        }
    }
    return arity % 2 == 1;
}

void fix_start(const set<C>& path, C ini) {
    bool left = path.count({ini.x - 1, ini.y});
    bool right = path.count({ini.x + 1, ini.y});
    bool top = path.count({ini.x, ini.y - 1});
    bool bottom = path.count({ini.x, ini.y + 1});
    if (left) {
        char cl = cmap[ini.y][ini.x - 1];
        left = cl == '-' || cl == 'F' || cl == 'L';
    }
    if (right) {
        char c = cmap[ini.y][ini.x - 1];
        right = c == '-' || c == 'J' || c == '7';
    }
    if (top) {
        char c = cmap[ini.y][ini.x - 1];
        top = c == '|' || c == 'F' || c == '7';
    }
    if (bottom) {
        char c = cmap[ini.y][ini.x - 1];
        bottom = c == '|' || c == 'J' || c == 'L';
    }
    char t;
    if (left && right)
        t = '-';
    else if (top && bottom)
        t = '|';
    else if (top && left)
        t = 'J';
    else if (top && right)
        t = 'L';
    else if (bottom && right)
        t = 'F';
    else if (bottom && left)
        t = '7';
    else
        t = 'S';
    cmap[ini.y][ini.x] = t;
}

int main() {
    string line;
    while (getline(cin, line)) {
        cmap.push_back(line);
    }
    n = cmap.size();
    m = cmap[0].size();
    C s{};
    for (ll i = 0; i < cmap.size(); i++) {
        for (ll j = 0; j < cmap[0].size(); j++) {
            if (cmap[i][j] == 'S') {
                s = {j, i};
                goto found;
            }
        }
    }
found:
    vis.clear();
    vis.assign(n, vector<bool>(m, false));
    auto vpath = dfs(s, s);
    auto path = set<C>(vpath.begin(), vpath.end());
    fix_start(path, s);
    cout << vpath.size() / 2 << endl;
    ll tiles_in = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (!path.count({j, i}) && is_inside(path, {j, i})) {
                tiles_in++;
                cmap[i][j] = 'I';
            }
        }
    }
    print(path);
    cout << tiles_in << endl;
    return 0;
}
