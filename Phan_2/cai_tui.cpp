#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void cai_tui(const vector<string> &items, const vector<int> &w, const vector<int> &v, int W) {
    int n = w.size();
    vector<vector<int>> f(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            f[i][j] = f[i - 1][j]; 
            if (w[i - 1] <= j) {    
                f[i][j] = max(f[i][j], f[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    cout << "=== BANG f ===" << endl;
    cout << "f[i][j]\t";
    for (int j = 0; j <= W; j++) cout << j << "\t";
    cout << endl;

    for (int i = 0; i <= n; i++) {
        if (i == 0) cout << "i=0\t";
        else cout << "i=" << i << " (" << items[i - 1] << ")\t";
        for (int j = 0; j <= W; j++) {
            cout << f[i][j] << "\t";
        }
        cout << endl;
    }

    vector<string> chon;
    int j = W;
    for (int i = n; i > 0; i--) {
        if (f[i][j] != f[i - 1][j]) { 
            chon.push_back(items[i - 1]);
            j -= w[i - 1];
        }
    }
    reverse(chon.begin(), chon.end());

    cout << "\nGia tri lon nhat: " << f[n][W] << endl;
    cout << "Tap do vat duoc chon: [ ";
    for (const auto &s : chon) cout << s << " ";
    cout << "]" << endl;
}

int main() {
    vector<string> items = {"A", "B", "C", "D", "E"};
    vector<int> w = {2, 3, 4, 5, 7};
    vector<int> v = {3, 7, 9, 12, 16};
    int W = 11;

    cai_tui(items, w, v, W);
    return 0;
}