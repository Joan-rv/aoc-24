#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
typedef unsigned long long ull;

void blink(std::unordered_map<ull, ull>& stones) {
    std::unordered_map<ull, ull> orig_stones(stones);
    for (auto& s : orig_stones) {
        ull d = (ull)log10(s.first) + 1;
        if (s.first == 0) {
            stones[1] += s.second;
        } else if (d % 2 == 0) {
            ull p = pow(10, (ull)(d / 2));
            stones[s.first % p] += s.second;
            stones[s.first / p] += s.second;
        } else {
            stones[s.first * 2024] += s.second;
        }
        stones[s.first] -= s.second;
    }
}

int main() {
    std::ifstream input("input");
    ull n;
    std::unordered_map<ull, ull> stones;
    while (input >> n) {
        stones[n]++;
    }

    for (int i = 0; i < 75; i++) {
        blink(stones);
        printf("i=%d\r", i);
        fflush(stdout);
    }

    ull sum = 0;
    for (const auto& s : stones) {
        sum += s.second;
    }

    printf("Number of stones: %llu\n", sum);
}
