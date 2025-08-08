#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct MapRange {
    ll src_start, dst_start, length;
};

struct Range {
    ll start, length;
};

typedef vector<MapRange> Map;

vector<ll> read_seeds() {
    std::string line;
    getline(cin, line);
    istringstream iline(line);
    std::string key;
    iline >> key;
    vector<ll> seeds;
    ll seed;
    while (iline >> seed) {
        seeds.push_back(seed);
    }
    return seeds;
}

vector<Range> read_seeds_range() {
    std::string line;
    getline(cin, line);
    istringstream iline(line);
    std::string key;
    iline >> key;
    vector<Range> seeds;
    Range range;
    while (iline >> range.start >> range.length) {
        seeds.push_back(range);
    }
    return seeds;
}

Map read_map() {
    string line;
    getline(cin, line);
    Map map;
    while (getline(cin, line)) {
        if (line.empty())
            break;

        istringstream iline(line);
        MapRange entry;
        while (iline >> entry.dst_start >> entry.src_start >> entry.length) {
            map.push_back(entry);
        }
    }
    sort(map.begin(), map.end(),
         [](auto& e1, auto& e2) { return e1.src_start < e2.src_start; });
    return map;
}

vector<ll> through_map(vector<ll>&& nums, const Map& map) {
    vector<ll> through(std::move(nums));
    for (auto& num : through) {
        for (const auto& range : map) {
            ll delta = num - range.src_start;
            if (range.src_start <= num && delta < range.length) {
                num = range.dst_start + delta;
                break;
            }
        }
    }
    return through;
}

vector<Range> through_map(vector<Range>&& ranges, const Map& map) {
    vector<Range> ret;
    stack<Range, vector<Range>> todo(std::move(ranges));
    while (!todo.empty()) {
        auto curr = todo.top();
        todo.pop();
        bool found = false;
        for (auto& m : map) {
            if (m.src_start >= curr.start + curr.length) {
                ret.push_back(curr);
                found = true;
                break;
            }
            if (m.src_start + m.length <= curr.start) {
                continue;
            }
            found = true;
            // there is overlap
            // we overshot some
            if (curr.start < m.src_start) {
                ret.push_back(Range{curr.start, m.src_start - curr.start});
            }
            // we are missing some
            if (curr.start + curr.length > m.src_start + m.length) {
                todo.push(
                    Range{m.src_start + m.length,
                          curr.start + curr.length - (m.src_start + m.length)});
            }
            ll delta = max(curr.start - m.src_start, 0ll);
            ll start = m.dst_start + delta;
            ll length = min(m.length - delta, curr.length);
            ret.push_back(Range{start, length});
            break;
        }
        if (!found)
            ret.push_back(curr);
    }
    return ret;
}

int main() {
    // part 1
    // auto seeds = read_seeds();
    auto seeds = read_seeds_range();
    auto seed_to_soil = read_map();
    auto soil_to_fertilizer = read_map();
    auto fertilizer_to_water = read_map();
    auto water_to_light = read_map();
    auto light_to_temperature = read_map();
    auto temperature_to_humidity = read_map();
    auto humidity_to_location = read_map();
    auto soils = through_map(std::move(seeds), seed_to_soil);
    auto fertilizers = through_map(std::move(soils), soil_to_fertilizer);
    auto waters = through_map(std::move(fertilizers), fertilizer_to_water);
    auto lights = through_map(std::move(waters), water_to_light);
    auto temperatures = through_map(std::move(lights), light_to_temperature);
    auto humidities =
        through_map(std::move(temperatures), temperature_to_humidity);
    auto locations = through_map(std::move(humidities), humidity_to_location);
    // cout << *min_element(locations.begin(), locations.end()) << endl;
    cout << min_element(locations.begin(), locations.end(),
                        [](auto& r1, auto& r2) { return r1.start < r2.start; })
                ->start
         << endl;
}
