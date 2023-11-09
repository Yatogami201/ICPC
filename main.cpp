#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Azulejo {
    int P, S, I;
    bool operator<(const Azulejo& t) const { return S < t.S; }
};

int main() {
    int N;
    while (cin >> N) {
        vector<multiset<Azulejo>> v[2];
        for (int fila = 0; fila < 2; fila++) {
            vector<Azulejo> T(N);
            for (int i = 0; i < N; i++) cin >> T[i].P;
            for (int i = 0; i < N; i++) cin >> T[i].S;
            for (int i = 0; i < N; i++) T[i].I = i + 1;
            sort(T.begin(), T.end(), [](const Azulejo& a, const Azulejo& b) -> bool { return a.P < b.P; });
            for (int i = 0; i < N; i++) {
                if (i == 0 || T[i - 1].P != T[i].P)
                    v[fila].emplace_back();
                v[fila].back().insert(T[i]);
            }
        }

        vector<int> ret[2];
        for (int i0 = 0, i1 = 0; ret[0].size() < N;) {
            if (v[0][i0].size() < v[1][i1].size()) {
                for (const auto& t : v[0][i0]) {
                    auto it = v[1][i1].upper_bound(Azulejo{t.P, t.S - 1, t.I});
                    if (it == v[1][i1].begin()) goto fail;
                    --it;
                    ret[0].push_back(t.I);
                    ret[1].push_back(it->I);
                    v[1][i1].erase(it);
                }
                i0++;
            } else {
                for (const auto& t : v[1][i1]) {
                    auto it = v[0][i0].upper_bound(t);
                    if (it == v[0][i0].end()) goto fail;
                    ret[1].push_back(t.I);
                    ret[0].push_back(it->I);
                    v[0][i0].erase(it);
                }
                i1++;
                if (v[0][i0].empty()) i0++;
            }
        }

        for (int fila = 0; fila < 2; fila++) {
            for (int i = 0; i < ret[fila].size(); i++) {
                if (i) cout << ' ';
                cout << ret[fila][i];
            }
            cout << endl;
        }
        continue;
        fail:
        cout << "Imposible" << endl;
    }
}
