#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

pair<int, string> doi_tien_tham_lam(vector<int> mg, int S) {
    sort(mg.rbegin(), mg.rend());
    int con = S, so_to = 0;
    string cach = "";
    for (int m : mg) {
        if (con >= m) {
            int cnt = con / m;
            so_to += cnt;
            con %= m;
            cach += (cach.empty() ? "" : " + ") + to_string(cnt) + "x" + to_string(m);
        }
    }
    return {so_to, cach};
}

pair<int, string> doi_tien_qhd(const vector<int> &mg, int S) {
    vector<int> f(S + 1, 1e9), vet(S + 1, -1);
    f[0] = 0;
    for (int j = 1; j <= S; j++) {
        for (int m : mg) {
            if (m <= j && f[j - m] + 1 < f[j]) {
                f[j] = f[j - m] + 1;
                vet[j] = m;
            }
        }
    }
    map<int, int, greater<int>> dem;
    int cur = S;
    while (cur > 0) {
        dem[vet[cur]]++;
        cur -= vet[cur];
    }
    string cach = "";
    for (auto p : dem) {
        cach += (cach.empty() ? "" : " + ") + to_string(p.second) + "x" + to_string(p.first);
    }
    return {f[S], cach};
}

int main() {
    vector<pair<vector<int>, int>> ds = {
        {{1, 4, 6, 9}, 12},
        {{1, 5, 10, 20, 50}, 85},
        {{1, 3, 7, 12}, 20},
        {{1, 2, 5, 10}, 38},
        {{1, 6, 10}, 12},
        {{1, 4, 5, 15, 20}, 23}
    };
    for (size_t i = 0; i < ds.size(); i++) {
        auto tl = doi_tien_tham_lam(ds[i].first, ds[i].second);
        auto qh = doi_tien_qhd(ds[i].first, ds[i].second);
        string dung = (tl.first == qh.first) ? "Dung" : "Sai";
        cout << "Bo " << i + 1 << " (S=" << ds[i].second << "): Tham lam = " << tl.first 
             << " to (" << tl.second << ") | Toi uu = " << qh.first << " to (" << qh.second 
             << ") => " << dung << endl;
    }
    return 0;
}