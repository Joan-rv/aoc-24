#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> read_line() {
    string line;
    getline(cin, line);
    istringstream iline(line);
    string key;
    iline >> key;
    vector<ll> out;
    ll elem;
    while (iline >> elem)
        out.push_back(elem);
    return out;
}

ll num_of_ways_to_beat(ll race_time, ll race_dist) {
    ll beat = 0;
    for (ll hold = 0; hold < race_time; hold++) {
        ll time_run = race_time - hold;
        ll end_dist = time_run * hold;
        if (end_dist > race_dist)
            beat++;
    }
    return beat;
}

int main() {
    auto times = read_line();
    auto distances = read_line();
    ll res = 1;
    for (size_t i = 0; i < times.size(); i++) {
        res *= num_of_ways_to_beat(times[i], distances[i]);
    }
    cout << res << endl;
    return 0;
}
