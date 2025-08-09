#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

enum class HandType {
    Five = 7,
    Four = 6,
    Full = 5,
    Three = 4,
    TwoTwo = 3,
    Two = 2,
    One = 1,
};

int strength(char c) {
    switch (c) {
    case 'A':
        return 12;
    case 'K':
        return 11;
    case 'Q':
        return 10;
    case 'T':
        return 8 + 1;
    case 'J':
        return 0;
    default:
        return c - '2' + 1;
    }
}

HandType hand_type(const string& hand) {
    int fqs[13] = {0};
    for (char c : hand) {
        fqs[strength(c)]++;
    }
    int j_fq = fqs[0];
    sort(fqs + 1, fqs + 13);
    int big = fqs[12], big2 = fqs[11];
    big += j_fq;
    if (big == 5) {
        return HandType::Five;
    } else if (big == 4) {
        return HandType::Four;
    } else if (big == 3 and big2 == 2) {
        return HandType::Full;
    } else if (big == 3) {
        return HandType::Three;
    } else if (big == 2 and big2 == 2) {
        return HandType::TwoTwo;
    } else if (big == 2) {
        return HandType::Two;
    } else {
        return HandType::One;
    }
}

int main() {
    vector<pair<string, ll>> hands;
    pair<string, ll> hand;
    while (cin >> hand.first >> hand.second)
        hands.push_back(hand);
    sort(hands.begin(), hands.end(), [](auto& h1, auto& h2) {
        auto t1 = hand_type(h1.first);
        auto t2 = hand_type(h2.first);
        if (t1 != t2) {
            return t1 < t2;
        } else {
            for (int i = 0; i < h1.first.size(); i++) {
                auto s1 = strength(h1.first[i]);
                auto s2 = strength(h2.first[i]);
                if (s1 != s2)
                    return s1 < s2;
            }
            return false;
        }
    });
    int winnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        cout << hands[i].first << endl;
        winnings += hands[i].second * (i + 1);
    }
    cout << winnings << endl;
    return 0;
}
